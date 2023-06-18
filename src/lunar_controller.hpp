#pragma once 

#include <lua.hpp>

#include "xbox_controller.hpp"

class lunar_controller {
public:
	static int register_class(lua_State* L);
	static int loader(lua_State* L);
	static int new_instance(lua_State* L);
	static int new_first_available(lua_State* L);
	static int gc(lua_State* L);
	static int poll(lua_State* L);

	static int connected(lua_State* L);
	static int changed(lua_State* L);

	static int get_state(lua_State* L);
	static int get_previous_state(lua_State* L);
	static int get_capabilities(lua_State* L);

	static int set_left_thumb_deadzone(lua_State* L);
	static int get_left_thumb_deadzone(lua_State* L);
	static int set_right_thumb_deadzone(lua_State* L);
	static int get_right_thumb_deadzone(lua_State* L); 
	static int set_trigger_threshold(lua_State* L);
	static int get_trigger_threshold(lua_State* L); 

	static int get_left_thumb_delta(lua_State* L);
	static int get_right_thumb_delta(lua_State* L);
	
	static int get_left_trigger_toggled(lua_State* L);
	static int get_right_trigger_toggled(lua_State* L);
	static int get_left_trigger_delta(lua_State* L);
	static int get_right_trigger_delta(lua_State* L); 

	static int on(lua_State* L);
private:
	static inline const char class_name_[] = "lunar_controller";
};