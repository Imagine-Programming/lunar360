#pragma once 

#include <lua.hpp>

class lunar_process {
public:
	static int register_class(lua_State* L);
	static int loader(lua_State* L);

	static int start_nowait(lua_State* L);
	static int start_wait(lua_State* L);
	static int start_stdout(lua_State* L);
	
};