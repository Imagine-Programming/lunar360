#include "lunar_helpers.hpp"

void lunar_helpers::preload_module(lua_State* L, const char* name, lua_CFunction loader) {
	luaL_getsubtable(L, LUA_REGISTRYINDEX, LUA_PRELOAD_TABLE); 
	lua_pushcfunction(L, loader);
	lua_setfield(L, -2, name);
	lua_pop(L, 1);
}