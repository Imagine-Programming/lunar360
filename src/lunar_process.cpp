#include "lunar_process.hpp"
#include "lunar_helpers.hpp"

#include <string>

#include <windows.h>

#define BUFSIZE 4096

static std::string last_error_message() {
	auto error_code = GetLastError();
	if (error_code == 0)
		return "Unknown error";
	
	LPSTR message_buffer = nullptr;
	auto size = FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr,
		error_code,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPSTR)&message_buffer,
		0,
		nullptr 
	);

	if (size == 0 || message_buffer == nullptr)
		return "Unknown error";
	
	std::string message(message_buffer, static_cast<std::size_t>(size));
	LocalFree(message_buffer); 
	return message;
}

static void push_last_error_message(lua_State* L) {
	auto message = last_error_message();
	lua_pushlstring(L, message.c_str(), message.size());
}

int lunar_process::register_class(lua_State* L) {
	lunar_helpers::preload_module(L, "lunar360.process", loader);
	return 0;
}

#define lunar_process_register_const(_L_, _N_) \
	lua_pushstring(_L_, #_N_);\
	lua_pushinteger(_L_, _N_);\
	lua_rawset(L, -3);

int lunar_process::loader(lua_State* L) {

	lua_newtable(L);
	
	lunar_process_register_const(L, SW_HIDE); 
	lunar_process_register_const(L, SW_SHOWNORMAL);
	lunar_process_register_const(L, SW_NORMAL); 
	lunar_process_register_const(L, SW_SHOWMINIMIZED); 
	lunar_process_register_const(L, SW_SHOWMAXIMIZED); 
	lunar_process_register_const(L, SW_MAXIMIZE); 
	lunar_process_register_const(L, SW_SHOWNOACTIVATE);
	lunar_process_register_const(L, SW_SHOW);
	lunar_process_register_const(L, SW_MINIMIZE);
	lunar_process_register_const(L, SW_SHOWMINNOACTIVE);
	lunar_process_register_const(L, SW_SHOWNA);
	lunar_process_register_const(L, SW_RESTORE);
	lunar_process_register_const(L, SW_SHOWDEFAULT);
	lunar_process_register_const(L, SW_FORCEMINIMIZE);
	lunar_process_register_const(L, SW_MAX);

	lua_pushcfunction(L, start_nowait);
	lua_setfield(L, -2, "start_nowait");

	lua_pushcfunction(L, start_wait); 
	lua_setfield(L, -2, "start_wait"); 

	lua_pushcfunction(L, start_stdout); 
	lua_setfield(L, -2, "start_stdout"); 
	
	return 1;
}

int lunar_process::start_nowait(lua_State* L) {
	const auto* cmdl = luaL_checkstring(L, 1);
    const auto* args = luaL_optstring(L, 2, nullptr);
	const auto* wdir = luaL_optstring(L, 3, nullptr);
	const auto  show = luaL_optinteger(L, 4, SW_SHOWNORMAL); 
	
	SHELLEXECUTEINFOA sei = { 0 };

    sei.cbSize = sizeof(SHELLEXECUTEINFOA);
    sei.fMask = 0;
    sei.hwnd = nullptr;
    sei.lpVerb = "open";
    sei.lpFile = cmdl;
    sei.lpParameters = args;
    sei.lpDirectory = wdir;
	sei.nShow = static_cast<int>(show);
    sei.hInstApp = nullptr;

    auto result = ShellExecuteExA(&sei);
    lua_pushboolean(L, result);
    
	if (!result) {
		push_last_error_message(L);
		return 2;
	} else {
		return 1;
	}
}

int lunar_process::start_wait(lua_State* L) {
    const auto* cmdl = luaL_checkstring(L, 1);
    const auto* args = luaL_optstring(L, 2, nullptr);
    const auto* wdir = luaL_optstring(L, 3, nullptr);
	const auto  show = luaL_optinteger(L, 4, SW_SHOWNORMAL);
	
    SHELLEXECUTEINFOA sei = { 0 };

	sei.cbSize = sizeof(SHELLEXECUTEINFOA); 
    sei.fMask = SEE_MASK_NOCLOSEPROCESS; 
	sei.hwnd = nullptr;
	sei.lpVerb = "open";  
	sei.lpFile = cmdl; 
	sei.lpParameters = args; 
	sei.lpDirectory = wdir; 
	sei.nShow = static_cast<int>(show);
	sei.hInstApp = nullptr;
    
	auto result = ShellExecuteExA(&sei); 
	
	if (!result || sei.hProcess == nullptr) {
		lua_pushboolean(L, false);
		push_last_error_message(L);
		return 2;
	}

	WaitForSingleObject(sei.hProcess, INFINITE); 
	
	DWORD exit_code;
	GetExitCodeProcess(sei.hProcess, &exit_code); 
	
	lua_pushboolean(L, true); 
	lua_pushinteger(L, exit_code); 
	
	return 2;
}

int lunar_process::start_stdout(lua_State* L) {
	const auto* cmdl = luaL_checkstring(L, 1); 
	const auto* args = luaL_optstring(L, 2, nullptr); 
	const auto* wdir = luaL_optstring(L, 3, nullptr); 
	const auto  show = luaL_optinteger(L, 4, SW_SHOWNORMAL); 
	
	// ensure that args includes the cmdl in the beginning and cmdl is enquoted
	std::string cmdl_args;
	cmdl_args.reserve(strlen(cmdl) + (args ? strlen(args) : 0) + 3); 
	cmdl_args += "\"";
	cmdl_args += cmdl; 
	cmdl_args += "\""; 
	if (args) {
		cmdl_args += " ";
		cmdl_args += args;
	} 

	// resolve cmdl like ShellExecuteEx does 
	char resolved_cmdl[MAX_PATH]; 
	auto result = SearchPathA(nullptr, cmdl, ".exe", MAX_PATH, resolved_cmdl, nullptr); 
	if (result == 0) { 
		lua_pushboolean(L, false); 
		push_last_error_message(L); 
		return 2; 
	} 
	
	STARTUPINFOA si;
	PROCESS_INFORMATION pi;
	SECURITY_ATTRIBUTES sa; 
	ZeroMemory(&si, sizeof(STARTUPINFOA));
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
	ZeroMemory(&sa, sizeof(SECURITY_ATTRIBUTES)); 

	// capture stdout so that we can pass it as a string to Lua later
	HANDLE read_pipe_handle  = nullptr;
	HANDLE write_pipe_handle = nullptr;
	
	// set the bInheritHandle flag so pipe handles are inherited
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);  
	sa.bInheritHandle = TRUE; 
	sa.lpSecurityDescriptor = nullptr; 
	
	// create a pipe for the child process's STDOUT
	if (!CreatePipe(&read_pipe_handle, &write_pipe_handle, &sa, 0)) { 
		lua_pushboolean(L, false);
		push_last_error_message(L); 

		return 2;
	}
	
	// ensure the read handle to the pipe for STDOUT is not inherited
	if (!SetHandleInformation(read_pipe_handle, HANDLE_FLAG_INHERIT, 0)) {
		lua_pushboolean(L, false);
		push_last_error_message(L); 

		return 2;
	}
	
	si.cb = sizeof(si); 
	si.wShowWindow = static_cast<WORD>(show);
	si.hStdError = write_pipe_handle;
	si.hStdOutput = write_pipe_handle;
	si.dwFlags |= STARTF_USESTDHANDLES; 
	si.dwFlags |= STARTF_USESHOWWINDOW; 
	
	// create the child process
	if (!CreateProcessA(resolved_cmdl, (LPSTR)cmdl_args.c_str(), NULL, NULL, TRUE, 0, NULL, wdir, &si, &pi)) {
		lua_pushboolean(L, false);
		push_last_error_message(L); 

		if (pi.hProcess) CloseHandle(pi.hProcess);
		if (pi.hThread)  CloseHandle(pi.hThread);

		return 2;
	}
	
	// close the write end of the pipe before reading from the read end of the pipe
	if (!CloseHandle(write_pipe_handle)) {
		lua_pushboolean(L, false);
		push_last_error_message(L); 

		if (pi.hProcess) CloseHandle(pi.hProcess);
		if (pi.hThread)  CloseHandle(pi.hThread);

		return 2;
	}

	// read output from the child process's pipe for STDOUT
	DWORD read_bytes;
	CHAR stdout_buffer[BUFSIZE] = { '\0' };
	BOOL read_success = FALSE; 
	std::string output;
	
	for (;;) {
		read_success = ReadFile(read_pipe_handle, stdout_buffer, BUFSIZE, &read_bytes, NULL);

		if (!read_success || read_bytes == 0) break;

		output.append(stdout_buffer, read_bytes);
	}

	// get process exit code
	DWORD exit_code;
	GetExitCodeProcess(pi.hProcess, &exit_code);
	
	// close process and thread handles
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	
	// push output and exit code
	lua_pushboolean(L, true);
	lua_pushinteger(L, static_cast<lua_Integer>(exit_code)); 
	lua_pushstring(L, output.c_str());
	
	return 3;
}