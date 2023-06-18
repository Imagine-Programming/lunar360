#pragma once

#include <lua.hpp>

class lunar_easing {
public:
	static int register_class(lua_State* L);
	static int loader(lua_State* L);
private: 
	static int ease_in_linear(lua_State* L);
	static int ease_in_sine(lua_State* L);
	static int ease_in_quadratic(lua_State* L);
	static int ease_in_cubic(lua_State* L);
	static int ease_in_quartic(lua_State* L);
	static int ease_in_quintic(lua_State* L);
	static int ease_in_exponential(lua_State* L);
	static int ease_in_circular(lua_State* L);
};