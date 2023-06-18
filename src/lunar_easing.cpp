#include "lunar_easing.hpp"
#include "lunar_helpers.hpp"

#include <cmath>
#include <numbers>

int lunar_easing::register_class(lua_State* L) {
	lunar_helpers::preload_module(L, "lunar360.easing", loader); 
	return 0;
}

int lunar_easing::loader(lua_State* L) {
	static luaL_Reg functions[] = {
		{ "ease_in_linear",      lunar_easing::ease_in_linear },
		{ "ease_in_sine",        lunar_easing::ease_in_sine },
		{ "ease_in_quadratic",   lunar_easing::ease_in_quadratic },
		{ "ease_in_cubic",       lunar_easing::ease_in_cubic },
		{ "ease_in_quartic",     lunar_easing::ease_in_quartic },
		{ "ease_in_quintic",     lunar_easing::ease_in_quintic },
		{ "ease_in_exponential", lunar_easing::ease_in_exponential },
		{ "ease_in_circular",    lunar_easing::ease_in_circular },
		{ nullptr,       nullptr }
	};

	luaL_newlib(L, functions);
	return 1;
}

int lunar_easing::ease_in_linear(lua_State* L) {
	lua_pushvalue(L, 1);
	return 1; 
}

int lunar_easing::ease_in_sine(lua_State* L) {
	lua_pushnumber(L, 1.0 - std::cos((luaL_checknumber(L, 1) * std::numbers::pi) / 2.0));
	return 1;
}

int lunar_easing::ease_in_quadratic(lua_State* L) {
	auto x = luaL_checknumber(L, 1);
	lua_pushnumber(L, x * x); 
	return 1;
}

int lunar_easing::ease_in_cubic(lua_State* L) {
	auto x = luaL_checknumber(L, 1); 
	lua_pushnumber(L, x * x * x); 
	return 1; 
}

int lunar_easing::ease_in_quartic(lua_State* L) {
	auto x = luaL_checknumber(L, 1); 
	lua_pushnumber(L, x * x * x * x); 
	return 1;
}

int lunar_easing::ease_in_quintic(lua_State* L) {
	auto x = luaL_checknumber(L, 1); 
	lua_pushnumber(L, x * x * x * x * x);
	return 1;
}

int lunar_easing::ease_in_exponential(lua_State* L) {
	auto x = luaL_checknumber(L, 1);
	lua_pushnumber(L, x == 0.0 ? 0.0 : std::pow(2.0, 10.0 * x - 10.0));
	return 1;
}

int lunar_easing::ease_in_circular(lua_State* L) {
	auto x = luaL_checknumber(L, 1);
	lua_pushnumber(L, 1.0 - std::sqrt(1.0 - x * x));
	return 1;
}
