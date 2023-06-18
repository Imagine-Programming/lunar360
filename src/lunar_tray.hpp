#pragma once 

#include "resource.h"
#include <windows.h>

#include <string>

#define	WM_USER_LUNARTRAY WM_USER + 1
#define WM_USER_LUNARERROR WM_USER + 2

class lunar_tray {
public:
	/// <summary>
	/// Register the window class used for the invisible window that serves as the 
	/// host for the tray icon. This is a static function, so it is only called once.
	/// </summary>
	/// <param name="instance">The application instance.</param>
	/// <returns>true when successful</returns>
	static bool register_class(HINSTANCE instance);
	
	/// <summary>
	/// Construct a new lunartray, which creates an invisible window that will 
	/// host a system tray icon through Shell_NotifyIcon. 
	/// </summary>
	/// <param name="instance">The application instance.</param>
	/// <param name="cmd">The show command.</param>
	lunar_tray(HINSTANCE instance, int cmd);

	/// <summary>
	/// Destroy the tray icon and the window.
	/// </summary>
	~lunar_tray();

	/// <summary>
	/// Handle the window messages for the tray icon.
	/// </summary>
	/// <returns>The last wParam which can be used as exit status.</returns>
	int event_loop();

	/// <summary>
	/// Obtain the window handle of this tray.
	/// </summary>
	/// <returns>A window handle.</returns>
	HWND get_hwnd() const noexcept;

	/// <summary>
	/// Send an error message to the event handler to be displayed as MessageBox and post a quit message.
	/// </summary>
	/// <param name="message">The error message.</param>
	void send_error(const std::wstring& message) const noexcept;

	/// <summary>
	/// Send an error message to the event handler to be displayed as MessageBox and post a quit message.
	/// </summary>
	/// <param name="message">The error message.</param>
	void send_error(const std::string& message) const noexcept;
private:
	HWND hWnd_;          // the window handle of the host window
	NOTIFYICONDATA nid_; // the tray icon data
	HICON icon_;         // the icon handle
	
	/// <summary>
	/// Load the IDC_LUNARMENU menu and display it.
	/// </summary>
	/// <param name="hWnd">The parent window handle.</param>
	static void context_menu(HWND hWnd);

	/// <summary>
	/// Handle all messages on the lunartray window.
	/// </summary>
	/// <param name="hWnd">The window handle of the window the event occurred on.</param>
	/// <param name="message">The event message.</param>
	/// <param name="wParam">The event wParam.</param>
	/// <param name="lParam">The event lParam.</param>
	/// <returns>LRESULT based on event handling.</returns>
	static LRESULT CALLBACK winproc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	/// <summary>
	/// Load the pointer to a string resource.
	/// </summary>
	/// <param name="instance">The application instance.</param>
	/// <param name="id">The resource ID.</param>
	/// <returns>A pointer to the resource or nullptr if it could not be loaded.</returns>
	static LPCWCHAR load_string_pointer(HINSTANCE instance, UINT id);

	/// <summary>
	/// Load a string resource as std::wstring.
	/// </summary>
	/// <param name="instance">The application instance.</param>
	/// <param name="id">The resource ID.</param>
	/// <returns>A std::wstring on success or an empty string on failure.</returns>
	static std::wstring load_string(HINSTANCE instance, UINT id);
};