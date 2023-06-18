#pragma once

#include <lua.hpp>

#include <cstdint>
#include <cstdlib>
#include <atomic>
#include <chrono>
#include <thread>

class lunar_poller {
public:
	static int register_class(lua_State* L);
	static int new_instance(lua_State* L, std::atomic_bool& stopflag);
	static int gc(lua_State* L);
	static int set_interval(lua_State* L);
	static int get_interval(lua_State* L);
	static int loop(lua_State* L);
	
private:
	lunar_poller(std::atomic_bool& stopflag);
	
	// interval in Hz
	std::uint32_t interval_ = 120; // default to 120Hz
	std::atomic_bool& stop_;
	
	static inline const char class_name_[] = "lunar_poller";
};