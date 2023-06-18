#pragma once 

#include <lua.hpp>

class lunar_helpers { 
public:
	static void preload_module(lua_State* L, const char* name, lua_CFunction loader);
};