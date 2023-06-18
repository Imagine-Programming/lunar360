#include "lunar_controller.hpp"
#include "lunar_helpers.hpp"

struct lunar_controller_button {
	lua_State* L;
	int functionRef;
};

#define __push_global(_L_, _N_) \
    lua_pushinteger(L, static_cast<lua_Integer>(_N_)); \
    lua_setglobal(L, #_N_);

#define __push_global_xinput(_L_, _N_) \
	lua_pushinteger(L, static_cast<lua_Integer>(XINPUT_##_N_)); \
	lua_setglobal(L, #_N_);

static void push_globals(lua_State* L) {
	__push_global(L, WHEEL_DELTA);

	__push_global_xinput(L, GAMEPAD_DPAD_UP); 
	__push_global_xinput(L, GAMEPAD_DPAD_DOWN); 
	__push_global_xinput(L, GAMEPAD_DPAD_LEFT); 
	__push_global_xinput(L, GAMEPAD_DPAD_RIGHT); 

	__push_global_xinput(L, GAMEPAD_START); 
	__push_global_xinput(L, GAMEPAD_BACK); 

	__push_global_xinput(L, GAMEPAD_LEFT_THUMB); 
	__push_global_xinput(L, GAMEPAD_RIGHT_THUMB); 
	__push_global_xinput(L, GAMEPAD_LEFT_SHOULDER); 
	__push_global_xinput(L, GAMEPAD_RIGHT_SHOULDER); 

	__push_global_xinput(L, GAMEPAD_A); 
	__push_global_xinput(L, GAMEPAD_B); 
	__push_global_xinput(L, GAMEPAD_X); 
	__push_global_xinput(L, GAMEPAD_Y); 

	__push_global_xinput(L, GAMEPAD_LEFT_THUMB_DEADZONE); 
	__push_global_xinput(L, GAMEPAD_RIGHT_THUMB_DEADZONE); 
	__push_global_xinput(L, GAMEPAD_TRIGGER_THRESHOLD); 
}

static void push_xbox_thumb_delta(lua_State* L, const xbox_thumb_delta& delta) noexcept {
	lua_newtable(L);
	
	lua_pushnumber(L, delta.x); 
	lua_setfield(L, -2, "x"); 
	lua_pushnumber(L, delta.y);
	lua_setfield(L, -2, "y"); 
	lua_pushnumber(L, delta.m); 
	lua_setfield(L, -2, "m");
	lua_pushnumber(L, delta.n);
	lua_setfield(L, -2, "n");
}

static void push_xinput_gamepad(lua_State* L, const XINPUT_GAMEPAD& gamepad, bool translate_keys = false) noexcept {
	lua_newtable(L);

	if (translate_keys) {
		
	}

	lua_pushinteger(L, static_cast<lua_Integer>(gamepad.wButtons));
	lua_setfield(L, -2, "wButtons");

	lua_pushinteger(L, static_cast<lua_Integer>(gamepad.bLeftTrigger));
	lua_setfield(L, -2, "bLeftTrigger");

	lua_pushinteger(L, static_cast<lua_Integer>(gamepad.bRightTrigger));
	lua_setfield(L, -2, "bRightTrigger");

	lua_pushinteger(L, static_cast<lua_Integer>(gamepad.sThumbLX));
	lua_setfield(L, -2, "sThumbLX");

	lua_pushinteger(L, static_cast<lua_Integer>(gamepad.sThumbLY));
	lua_setfield(L, -2, "sThumbLY");

	lua_pushinteger(L, static_cast<lua_Integer>(gamepad.sThumbRX));
	lua_setfield(L, -2, "sThumbRX");

	lua_pushinteger(L, static_cast<lua_Integer>(gamepad.sThumbRY));
	lua_setfield(L, -2, "sThumbRY");
}

static void push_xinput_state(lua_State* L, const XINPUT_STATE& state) noexcept {
	lua_newtable(L);
	
	lua_pushinteger(L, static_cast<lua_Integer>(state.dwPacketNumber));
	lua_setfield(L, -2, "dwPacketNumber");
	
	push_xinput_gamepad(L, state.Gamepad);
	lua_setfield(L, -2, "Gamepad");
}

static void push_xinput_vibrations(lua_State* L, const XINPUT_VIBRATION& vibr) noexcept {
	lua_newtable(L);
	
	lua_pushinteger(L, static_cast<lua_Integer>(vibr.wLeftMotorSpeed));
	lua_setfield(L, -2, "wLeftMotorSpeed");

	lua_pushinteger(L, static_cast<lua_Integer>(vibr.wRightMotorSpeed));
	lua_setfield(L, -2, "wRightMotorSpeed");
}

static void push_xinput_capabilities(lua_State* L, const XINPUT_CAPABILITIES& caps) noexcept {
	lua_newtable(L);

	lua_pushinteger(L, static_cast<lua_Integer>(caps.Type));
	lua_setfield(L, -2, "Type");

	lua_pushinteger(L, static_cast<lua_Integer>(caps.SubType));
	lua_setfield(L, -2, "SubType");

	lua_pushinteger(L, static_cast<lua_Integer>(caps.Flags));
	lua_setfield(L, -2, "Flags");

	push_xinput_gamepad(L, caps.Gamepad);
	lua_setfield(L, -2, "Gamepad");

	push_xinput_vibrations(L, caps.Vibration);
	lua_setfield(L, -2, "Vibration");
}

int lunar_controller::register_class(lua_State* L) {
	lunar_helpers::preload_module(L, "lunar360.controller", loader);
	return 0;
}

int lunar_controller::loader(lua_State* L) {
	push_globals(L); 

	luaL_newmetatable(L, class_name_);

	lua_pushstring(L, class_name_);
	lua_setfield(L, -2, "__name");

	lua_pushcfunction(L, gc);
	lua_setfield(L, -2, "__gc");

	lua_newtable(L);

	lua_pushcfunction(L, poll);
	lua_setfield(L, -2, "poll");

	lua_pushcfunction(L, connected); 
	lua_setfield(L, -2, "connected");
	
	lua_pushcfunction(L, changed); 
	lua_setfield(L, -2, "changed"); 
	
	lua_pushcfunction(L, get_state);
	lua_setfield(L, -2, "get_state");

	lua_pushcfunction(L, get_previous_state);
	lua_setfield(L, -2, "get_previous_state");

	lua_pushcfunction(L, get_capabilities);
	lua_setfield(L, -2, "get_capabilities");

	lua_pushcfunction(L, set_left_thumb_deadzone);
	lua_setfield(L, -2, "set_left_thumb_deadzone");
	
	lua_pushcfunction(L, get_left_thumb_deadzone);
	lua_setfield(L, -2, "get_left_thumb_deadzone");

	lua_pushcfunction(L, set_right_thumb_deadzone);
	lua_setfield(L, -2, "set_right_thumb_deadzone");
	
	lua_pushcfunction(L, get_right_thumb_deadzone);
	lua_setfield(L, -2, "get_right_thumb_deadzone");

	lua_pushcfunction(L, set_trigger_threshold);
	lua_setfield(L, -2, "set_trigger_threshold");

	lua_pushcfunction(L, get_left_thumb_delta); 
	lua_setfield(L, -2, "get_left_thumb_delta");
	
	lua_pushcfunction(L, get_right_thumb_delta); 
	lua_setfield(L, -2, "get_right_thumb_delta");

	lua_pushcfunction(L, get_left_trigger_toggled);
	lua_setfield(L, -2, "get_left_trigger_toggled");
	
	lua_pushcfunction(L, get_right_trigger_toggled);
	lua_setfield(L, -2, "get_right_trigger_toggled");

	lua_pushcfunction(L, get_left_trigger_delta);
	lua_setfield(L, -2, "get_left_trigger_delta");

	lua_pushcfunction(L, get_right_trigger_delta);
	lua_setfield(L, -2, "get_right_trigger_delta");

	lua_pushcfunction(L, on);
	lua_setfield(L, -2, "on"); 

	lua_setfield(L, -2, "__index");

	lua_pop(L, 1);

	lua_newtable(L);
	
	lua_pushcfunction(L, new_instance);
	lua_setfield(L, -2, "new");
	
	lua_pushcfunction(L, new_first_available);
	lua_setfield(L, -2, "new_first_available");

	return 1;
}

int lunar_controller::new_instance(lua_State* L) {
	auto udata = static_cast<xbox_controller**>(lua_newuserdata(L, sizeof(xbox_controller*))); 
	*udata = new xbox_controller(static_cast<DWORD>(luaL_checkinteger(L, 1)));
	luaL_setmetatable(L, class_name_); 
	return 1;
}

int lunar_controller::new_first_available(lua_State* L) {
	auto index = xbox_controller::get_first_active_controller_index();
	if (!index)
		return 0;

	auto udata = static_cast<xbox_controller**>(lua_newuserdata(L, sizeof(xbox_controller*))); 
	*udata = new xbox_controller(index.value()); 
	luaL_setmetatable(L, class_name_);
	return 1;
}

int lunar_controller::gc(lua_State* L) {
	auto controller = *static_cast<xbox_controller**>(luaL_checkudata(L, 1, class_name_));

	auto deleter = [](void* ptr) {
		if (ptr == nullptr) return;
		auto button = static_cast<lunar_controller_button*>(ptr);
		luaL_unref(button->L, LUA_REGISTRYINDEX, button->functionRef);
		delete button;
	};

	controller->visit_button_userdata([&](WORD button, void* down, void* up, void* single, void* db) {
		(void)button;
		deleter(down);
		deleter(up);
		deleter(single); 
		deleter(db); 
	});
	
	delete controller;
	return 0;
}

int lunar_controller::poll(lua_State* L) {
	auto controller = *static_cast<xbox_controller**>(luaL_checkudata(L, 1, class_name_));
	controller->poll();
	return 0;
}

int lunar_controller::connected(lua_State* L) {
	auto controller = *static_cast<xbox_controller**>(luaL_checkudata(L, 1, class_name_));
	lua_pushboolean(L, controller->connected()); 
	return 1; 
}

int lunar_controller::changed(lua_State* L) {
	auto controller = *static_cast<xbox_controller**>(luaL_checkudata(L, 1, class_name_));
	lua_pushboolean(L, controller->changed()); 
	return 1;
}

int lunar_controller::get_state(lua_State* L) {
	auto controller = *static_cast<xbox_controller**>(luaL_checkudata(L, 1, class_name_)); 
	push_xinput_state(L, controller->state());
	return 1;
}

int lunar_controller::get_previous_state(lua_State* L) {
	auto controller = *static_cast<xbox_controller**>(luaL_checkudata(L, 1, class_name_)); 
	push_xinput_state(L, controller->previous_state());
	return 1;
}

int lunar_controller::get_capabilities(lua_State* L) {
	auto controller = *static_cast<xbox_controller**>(luaL_checkudata(L, 1, class_name_)); 
	auto caps = controller->capabilities(); 
	if (!caps)
		return 0; 

	push_xinput_capabilities(L, *caps); 
	return 1;
}

int lunar_controller::set_left_thumb_deadzone(lua_State* L) {
	auto controller = *static_cast<xbox_controller**>(luaL_checkudata(L, 1, class_name_));
	controller->set_left_thumb_deadzone(static_cast<SHORT>(luaL_checkinteger(L, 2)));
	lua_pushvalue(L, 1);
	return 1;
}

int lunar_controller::get_left_thumb_deadzone(lua_State* L) {
	auto controller = *static_cast<xbox_controller**>(luaL_checkudata(L, 1, class_name_));
	lua_pushinteger(L, static_cast<lua_Integer>(controller->left_thumb_deadzone()));
	return 1;
}

int lunar_controller::set_right_thumb_deadzone(lua_State* L) {
	auto controller = *static_cast<xbox_controller**>(luaL_checkudata(L, 1, class_name_));
	controller->set_right_thumb_deadzone(static_cast<SHORT>(luaL_checkinteger(L, 2)));
	lua_pushvalue(L, 1);
	return 1;
}

int lunar_controller::get_right_thumb_deadzone(lua_State* L) {
	auto controller = *static_cast<xbox_controller**>(luaL_checkudata(L, 1, class_name_));
	lua_pushinteger(L, static_cast<lua_Integer>(controller->right_thumb_deadzone())); 
	return 1;
}

int lunar_controller::set_trigger_threshold(lua_State* L) {
	auto controller = *static_cast<xbox_controller**>(luaL_checkudata(L, 1, class_name_));
	controller->set_trigger_threshold(static_cast<BYTE>(luaL_checkinteger(L, 2))); 
	lua_pushvalue(L, 1);
	return 1; 
}

int lunar_controller::get_trigger_threshold(lua_State* L) {
	auto controller = *static_cast<xbox_controller**>(luaL_checkudata(L, 1, class_name_));
	lua_pushinteger(L, static_cast<lua_Integer>(controller->trigger_threshold())); 
	return 1;
}

int lunar_controller::get_left_thumb_delta(lua_State* L) {
	auto controller = *static_cast<xbox_controller**>(luaL_checkudata(L, 1, class_name_));
	auto delta = controller->left_thumb_delta();
	push_xbox_thumb_delta(L, delta);
	return 1;
}

int lunar_controller::get_right_thumb_delta(lua_State* L) {
	auto controller = *static_cast<xbox_controller**>(luaL_checkudata(L, 1, class_name_)); 
	auto delta = controller->right_thumb_delta();
	push_xbox_thumb_delta(L, delta);
	return 1;
}

int lunar_controller::get_left_trigger_toggled(lua_State* L) {
	auto controller = *static_cast<xbox_controller**>(luaL_checkudata(L, 1, class_name_)); 
	lua_pushboolean(L, controller->left_trigger_toggled());
	return 1; 
}

int lunar_controller::get_right_trigger_toggled(lua_State* L) {
	auto controller = *static_cast<xbox_controller**>(luaL_checkudata(L, 1, class_name_));
	lua_pushboolean(L, controller->right_trigger_toggled());
	return 1;
}

int lunar_controller::get_left_trigger_delta(lua_State* L) {
	auto controller = *static_cast<xbox_controller**>(luaL_checkudata(L, 1, class_name_));
	lua_pushnumber(L, controller->left_trigger_delta());
	return 1;
}

int lunar_controller::get_right_trigger_delta(lua_State* L) {
	auto controller = *static_cast<xbox_controller**>(luaL_checkudata(L, 1, class_name_));
	lua_pushnumber(L, controller->right_trigger_delta());
	return 1;
}

int lunar_controller::on(lua_State* L) {
	auto controller = *static_cast<xbox_controller**>(luaL_checkudata(L, 1, class_name_));
	auto button = static_cast<WORD>(luaL_checkinteger(L, 2));
	auto event = std::string(luaL_checkstring(L, 3));
	luaL_checktype(L, 4, LUA_TFUNCTION);

	if (event != "down-press" && event != "up-press" && event != "single-press" && event != "double-press") {
		luaL_argerror(L, 3, "invalid event: down-press, up-press, single-press and double-press are allowed");
	}
	
	lunar_controller_button* current = nullptr;
	
	if (event == "down-press") {
		current = static_cast<lunar_controller_button*>(controller->get_button_down_userdata(button));
	} else if (event == "up-press") {
		current = static_cast<lunar_controller_button*>(controller->get_button_up_userdata(button));
	} else if (event == "single-press") {
		current = static_cast<lunar_controller_button*>(controller->get_button_single_userdata(button));
	} else if (event == "double-press") {
		current = static_cast<lunar_controller_button*>(controller->get_button_double_userdata(button)); 
	}

	if (current != nullptr) {
		luaL_unref(L, LUA_REGISTRYINDEX, current->functionRef);
		delete current; 
	}

	lua_pushvalue(L, 4);
	auto reference = luaL_ref(L, LUA_REGISTRYINDEX);
	auto udata = new lunar_controller_button{ L, reference }; // destroyed on next call or in __gc
	auto proc = [](void* udata) {
		auto button = static_cast<lunar_controller_button*>(udata);
		lua_rawgeti(button->L, LUA_REGISTRYINDEX, button->functionRef);
		lua_call(button->L, 0, 0);
	};
	
	if (event == "down-press") {
		controller->on_button_down(button, proc, static_cast<void*>(udata));
	} else if (event == "up-press") {
		controller->on_button_up(button, proc, static_cast<void*>(udata));
	} else if (event == "single-press") {
		controller->on_button_single(button, proc, static_cast<void*>(udata));
	} else if (event == "double-press") {
		controller->on_button_double(button, proc, static_cast<void*>(udata));
	}

	lua_pushvalue(L, 1);
	return 1;
}