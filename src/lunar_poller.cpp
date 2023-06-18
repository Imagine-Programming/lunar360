#include "lunar_poller.hpp"

int lunar_poller::register_class(lua_State* L) {
	luaL_newmetatable(L, class_name_);

	lua_pushstring(L, class_name_);
	lua_setfield(L, -2, "__name");

	lua_pushcfunction(L, gc);
	lua_setfield(L, -2, "__gc");

	lua_newtable(L);

	lua_pushcfunction(L, set_interval);
	lua_setfield(L, -2, "set_interval");
	lua_pushcfunction(L, get_interval);
	lua_setfield(L, -2, "get_interval");
	lua_pushcfunction(L, loop);
	lua_setfield(L, -2, "loop");

	lua_setfield(L, -2, "__index");

	lua_pop(L, 1);

	return 0;
}

int lunar_poller::new_instance(lua_State* L, std::atomic_bool& stopflag) {
	auto udata = static_cast<lunar_poller**>(lua_newuserdata(L, sizeof(lunar_poller*)));
	*udata = new lunar_poller(stopflag);
	luaL_setmetatable(L, class_name_);
	return 1;
}

int lunar_poller::gc(lua_State* L) {
	auto poller = *static_cast<lunar_poller**>(luaL_checkudata(L, 1, class_name_));
	delete poller;
	return 0;
}

int lunar_poller::set_interval(lua_State* L) {
	auto poller = *static_cast<lunar_poller**>(luaL_checkudata(L, 1, class_name_));
	auto interval = luaL_checkinteger(L, 2);
	poller->interval_ = static_cast<std::uint32_t>(interval);
	return 0;
}

int lunar_poller::get_interval(lua_State* L) {
	auto poller = *static_cast<lunar_poller**>(luaL_checkudata(L, 1, class_name_));
	lua_pushinteger(L, static_cast<lua_Integer>(poller->interval_));
	return 1;
}

int lunar_poller::loop(lua_State* L) {
	auto poller = *static_cast<lunar_poller**>(luaL_checkudata(L, 1, class_name_));
	luaL_checktype(L, 2, LUA_TFUNCTION);

	auto interval = 1000 / poller->interval_;
	while (!poller->stop_) {
		// track start time 
		auto start = std::chrono::high_resolution_clock::now();

		// invoke the user function
		lua_pushvalue(L, 2);
		lua_call(L, 0, 0);

		// collect garbage at a fixed interval
		lua_gc(L, LUA_GCCOLLECT);

		// track end time
		auto end = std::chrono::high_resolution_clock::now();

		// calculate the time it took to invoke the user function
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

		// sleep for the remaining time
		auto remaining = interval - elapsed.count();

		if (remaining > 0)
			std::this_thread::sleep_for(std::chrono::milliseconds(remaining));
	}

	return 0;
}

lunar_poller::lunar_poller(std::atomic_bool& stopflag)
	: stop_(stopflag) {}