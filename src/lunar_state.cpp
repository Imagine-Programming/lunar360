#include "lunar_state.hpp"
#include "lunar_poller.hpp"
#include "lunar_easing.hpp"
#include "lunar_input.hpp"
#include "lunar_controller.hpp"
#include "lunar_process.hpp"
#include "lunar_debug.hpp"

static int lunar_bind_invoke(lua_State* L) {
    auto original_top = lua_gettop(L);
    auto parameters = lua_tointeger(L, lua_upvalueindex(2));

    // push the function
    lua_pushvalue(L, lua_upvalueindex(1));

    // push each bound parameter
    for (int i = 1; i <= parameters; i += 1)
        lua_pushvalue(L, lua_upvalueindex(2 + i));

    // push each new parameter
    for (int i = 1; i <= original_top; i += 1)
        lua_pushvalue(L, i);

    // call the function
    lua_call(L, static_cast<int>(parameters) + original_top, LUA_MULTRET);

    // return what is left on the stack by the call
    return lua_gettop(L) - original_top;
}

static int lunar_bind_self_invoke(lua_State* L) {
    // fetch method and object (this)
    lua_pushvalue(L, lua_upvalueindex(1));
    lua_insert(L, 1);
    lua_pushvalue(L, lua_upvalueindex(2));
    lua_insert(L, 2);

    // call the method 
    lua_call(L, lua_gettop(L) - 1, LUA_MULTRET);

    // return what is left on the stack by the call
    return lua_gettop(L);
}

static int lunar_bind(lua_State* L) {
    luaL_checktype(L, 1, LUA_TFUNCTION);

    if (lua_gettop(L) == 1)
        luaL_error(L, "There are no values to bind to this function");

    lua_pushinteger(L, ((lua_Integer)lua_gettop(L) - 1));
    lua_insert(L, 2);
    lua_pushcclosure(L, lunar_bind_invoke, lua_gettop(L));
    return 1;
}

static int lunar_bind_self(lua_State* L) {
    if (lua_gettop(L) != 2)
        luaL_error(L, "bind_self only allows for 2 parameters; the function to be bound to and the object to bind to it");
     
    luaL_checktype(L, 1, LUA_TFUNCTION); 
    luaL_checkany(L, 2); 
    lua_pushcclosure(L, lunar_bind_self_invoke, 2);
    return 1;
}

static void lunar_bind_register(lua_State* L) {
    lua_newtable(L);
    lua_pushstring(L, "__index");
    lua_newtable(L);
    
    lua_pushstring(L, "bind");
    lua_pushcfunction(L, lunar_bind);
    lua_rawset(L, -3); // bind

	lua_pushstring(L, "bind_self"); 
	lua_pushcfunction(L, lunar_bind_self); 
	lua_rawset(L, -3); // bind_self

	lua_rawset(L, -3); // __index

	// dirty trick to change the function metatable
    lua_pushcclosure(L, lunar_bind, 0);
    lua_insert(L, -2);
    lua_setmetatable(L, -2);
    lua_pop(L, 1);
}

lunar_state::lunar_state(const lunar_tray& tray, const fs::path& script) 
	: tray_(tray), script_(script) 
{
	L = luaL_newstate();
	luaL_openlibs(L);

    // register the bind and bind_this implementations
    lunar_bind_register(L);

    // register all modules that are global or in a preloader
    lua_CFunction modules[] = {
        lunar_poller::register_class,
        lunar_easing::register_class,
        lunar_input::register_class,
        lunar_controller::register_class,
        lunar_process::register_class,
        lunar_debug::register_class,
		nullptr
	};

	for (auto i = 0; modules[i] != nullptr; ++i)
		modules[i](L); 
    
	// the poller is a singleton, constructor is not exposed
	lunar_poller::new_instance(L, stop_);
	lua_setglobal(L, "poller");
}

lunar_state::~lunar_state() {
	if (L) {
		lua_gc(L, LUA_GCCOLLECT);
		lua_gc(L, LUA_GCCOLLECT);
		lua_close(L);
		L = nullptr;
	}
}

void lunar_state::run() noexcept {
    // create the thread of runner 
    thread_ = std::thread([this] { status_ = execute(L); });
}

bool lunar_state::can_join() const noexcept {
    if (!thread_.has_value())
        return false;
    
    return thread_->joinable(); 
}

void lunar_state::join() noexcept {
    if (!can_join())
        return;
    
    stop_ = true;
    thread_->join();
}

int lunar_state::status() const noexcept {
    return status_;
}

/// <summary>
/// lunar_state::error_handler is the error function used in lua_pcall calls to 
/// provide a full stack traceback to the user when an error occurs in Lua 
/// during that pcall. It uses the built in debug.traceback, so that the 
/// original error message is still prepended to the stack trace.
/// </summary>
/// <param name="L">The Lua state as provided by Lua internally</param>
/// <returns>The number of results on the stack.</returns>
int lunar_state::error_handler(lua_State* L) {
    if (lua_type(L, 1) != LUA_TSTRING)
        return 1; // leave anything that is not a string as is.

    // get debug table 
    lua_getglobal(L, "debug");
    if (!lua_istable(L, -1)) {
        lua_pop(L, 1);
        return 1; // debug table missing, return as is.
    }

    // get traceback function from debug table 
    lua_pushstring(L, "traceback");
    lua_rawget(L, -2);
    if (!lua_isfunction(L, -1)) {
        lua_pop(L, 2);
        return 1; // debug.traceback missing, return as is.
    }

    lua_remove(L, -2); // remove debug table from stack
    lua_insert(L, 1); // insert traceback function to before the original error message
    lua_pushinteger(L, 2); // start at stkidx 2
    lua_call(L, 2, 1); // call debug.traceback
    
    return 1; // return its result
}

int lunar_state::execute(lua_State* L) {
    if (!fs::is_regular_file(script_)) {
        error("Default script is not a regular file: '{}'", script_.string());
        return EXIT_FAILURE;
    }

    const auto script_path = script_.string();

    // push error handler
    lua_pushcfunction(L, error_handler); 
    auto error_handler_idx = lua_gettop(L);

    if (luaL_loadfile(L, script_path.c_str()) != LUA_OK) {
        if (lua_isstring(L, -1)) {
            error("Failed to load script: '{}': {}", script_.string(), lua_tostring(L, -1)); 
        }
        else {
            error("Failed to load script: '{}'", script_.string()); 
        }

        lua_pop(L, 1);
        return EXIT_FAILURE;
    }

    // call function on top of stack
    auto call_result = lua_pcall(L, 0, 0, error_handler_idx);
    lua_remove(L, error_handler_idx);

    if (call_result != LUA_OK) {
        if (lua_isstring(L, -1)) {
            error("Failed to execute script: '{}': {}", script_.string(), lua_tostring(L, -1)); 
        }
        else {
            error("Failed to execute script: '{}'", script_.string()); 
        }

        lua_pop(L, 1);
        return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}