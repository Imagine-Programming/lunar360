#include <windows.h>
#include <lua.hpp>

#include <string>
#include <format>
#include <iostream>
#include <filesystem>

#include "lunar_tray.hpp"
#include "lunar_state.hpp"

namespace fs = std::filesystem;

/// <summary>
/// Get the directory where the lunar360.exe file resides.
/// </summary>
/// <returns>The path to the application directory.</returns>
static fs::path lunar360_get_application_directory() {
	wchar_t buffer[MAX_PATH];
	GetModuleFileNameW(NULL, buffer, MAX_PATH);
	return fs::path(buffer).parent_path();
}

/// <summary>
/// Get the path to the default lunar360.lua file.
/// </summary>
/// <returns>The path to the lunar360.lua file.</returns>
static fs::path lunar360_get_default_script() {
	auto path = lunar360_get_application_directory();
	path /= "lunar360.lua";
	return path;
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
    lunar_tray::register_class(hInstance);
    lunar_tray tray(hInstance, nShowCmd);
    lunar_state state(tray, lunar360_get_default_script());
    
    state.run(); 
    tray.event_loop();
    state.join(); 
    
    return state.status();
}