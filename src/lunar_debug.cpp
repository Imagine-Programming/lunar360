#include "lunar_debug.hpp"
#include "lunar_helpers.hpp"

#include <cstdlib>
#include <cstdint>

#include <windows.h>

int lunar_debug::register_class(lua_State* L) {
	lunar_helpers::preload_module(L, "lunar360.debug", loader);
	return 0;
}

int lunar_debug::loader(lua_State* L) {
	luaL_newmetatable(L, class_name_);
	
	lua_pushstring(L, class_name_);
	lua_setfield(L, -2, "__name");

	lua_pushcfunction(L, gc);
	lua_setfield(L, -2, "__gc");

	lua_newtable(L);

	lua_pushcfunction(L, print);
	lua_setfield(L, -2, "print");

	lua_setfield(L, -2, "__index");
	
	lua_pop(L, 1);
	
	lua_newtable(L);
	
	lua_pushcfunction(L, get_instance);
	lua_setfield(L, -2, "get_instance");

	return 1;
}

int lunar_debug::get_instance(lua_State* L) {
	if (instance_ref_ != LUA_NOREF) {
		lua_rawgeti(L, LUA_REGISTRYINDEX, instance_ref_);
		return 1;
	}

	auto udata = static_cast<lunar_debug**>(lua_newuserdata(L, sizeof(lunar_debug*)));
	*udata = new lunar_debug();
	luaL_setmetatable(L, class_name_);
	
	lua_pushvalue(L, -1);
	instance_ref_ = luaL_ref(L, LUA_REGISTRYINDEX);
	
	return 1;
}

int lunar_debug::gc(lua_State* L) {
	return 0;
}

int lunar_debug::print(lua_State* L) {
	auto n = lua_gettop(L);
	for (auto i = 2; i <= n; ++i) {
		std::size_t l;
		const auto* s = luaL_tolstring(L, i, &l);
		if (i > 2) lua_writestring("\t", 1);
		lua_writestring(s, l);
		lua_pop(L, 1);
	}
	lua_writeline();
	return 0;
}

lunar_debug::lunar_debug() {
	// prepare a console and tie to stdout, stderr 
	AllocConsole();

	FILE* fDummy; 
	freopen_s(&fDummy, "CONIN$", "r", stdin); 
	freopen_s(&fDummy, "CONOUT$", "w", stderr); 
	freopen_s(&fDummy, "CONOUT$", "w", stdout); 
}