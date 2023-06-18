#pragma once 

#include <lua.hpp>

class lunar_debug {
public:
	static int register_class(lua_State* L);
	static int loader(lua_State* L);
	static int get_instance(lua_State* L);
	static int gc(lua_State* L);
	
	static int print(lua_State* L);

private:
	lunar_debug();

	static inline const char class_name_[] = "lunar_debug";
	static inline int instance_ref_ = LUA_NOREF; 
};