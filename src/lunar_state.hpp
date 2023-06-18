#pragma once

#include <lua.hpp>

#include <filesystem>
#include <optional>
#include <atomic>
#include <format>
#include <thread>

#include "lunar_tray.hpp"

namespace fs = std::filesystem;

class lunar_state {
public:
	lunar_state(const lunar_tray& tray, const fs::path& script);
	~lunar_state();
	
	void run() noexcept;
	bool can_join() const noexcept;
	void join() noexcept;
	int status() const noexcept;
private: 
	/// <summary>
	/// lunar_state::error_handler is the error function used in lua_pcall calls to 
	/// provide a full stack traceback to the user when an error occurs in Lua 
	/// during that pcall. It uses the built in debug.traceback, so that the 
	/// original error message is still prepended to the stack trace.
	/// </summary>
	/// <param name="L">The Lua state as provided by Lua internally</param>
	/// <returns>The number of results on the stack.</returns>
	static int error_handler(lua_State* L);
	
	/// <summary>
	/// Format and display an error through a MessageBox using the error (ICONSTOP) icon.
	/// </summary>
	/// <typeparam name="..._Types">The types to be provided to the formatter.</typeparam>
	/// <param name="_Fmt">The format string.</param>
	/// <param name="..._Args">The arguments to the format string.</param>
	template <typename... _Types>
	void error(const std::wformat_string<_Types...> _Fmt, _Types&&... _Args) {
		auto message = std::format(_Fmt, std::forward<_Types>(_Args)...);
		tray_.send_error(message); 
	}

	/// <summary>
	/// Format and display an error through a MessageBox using the error (ICONSTOP) icon.
	/// </summary>
	/// <typeparam name="..._Types">The types to be provided to the formatter.</typeparam>
	/// <param name="_Fmt">The format string.</param>
	/// <param name="..._Args">The arguments to the format string.</param>
	template <typename... _Types>
	void error(const std::format_string<_Types...> _Fmt, _Types&&... _Args) {
		auto message = std::format(_Fmt, std::forward<_Types>(_Args)...);
		tray_.send_error(message);
	}

	int execute(lua_State* L);


	const lunar_tray& tray_;
	const fs::path script_;
	
	std::atomic_bool stop_ = false;
	std::atomic_int status_ = EXIT_SUCCESS;
	lua_State* L = nullptr;

	std::optional<std::thread> thread_;
};