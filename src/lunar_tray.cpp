#include "lunar_tray.hpp"

#include <vector>
#include <stdexcept>

/// <summary>
/// Register the window class used for the invisible window that serves as the 
/// host for the tray icon. This is a static function, so it is only called once.
/// </summary>
/// <param name="instance">The application instance.</param>
/// <returns>true when successful</returns>
bool lunar_tray::register_class(HINSTANCE instance) {
	WNDCLASSEX window_class;
	
	auto class_name = load_string(instance, IDS_LUNAR_CLASS);

	// first check if the class exists
	if (GetClassInfoEx(instance, class_name.c_str(), &window_class)) 
		return true;

	window_class.cbSize = sizeof(WNDCLASSEX);
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpfnWndProc = winproc;
	window_class.cbClsExtra = 0;
	window_class.cbWndExtra = 0;
	window_class.hInstance = instance;
	window_class.hIcon = LoadIcon(instance, MAKEINTRESOURCE(IDI_CONTROLLER_NOFACE));
	window_class.hCursor = LoadCursor(NULL, IDC_ARROW);
	window_class.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	window_class.lpszMenuName = MAKEINTRESOURCE(IDC_LUNARMENU);
	window_class.lpszClassName = class_name.c_str();
	window_class.hIconSm = LoadIcon(window_class.hInstance, MAKEINTRESOURCE(IDI_CONTROLLER_NOFACE));

	return RegisterClassEx(&window_class) != 0;
}

/// <summary>
/// Construct a new lunartray, which creates an invisible window that will 
/// host a system tray icon through Shell_NotifyIcon. 
/// </summary>
/// <param name="instance">The application instance.</param>
/// <param name="cmd">The show command.</param>
lunar_tray::lunar_tray(HINSTANCE instance, int cmd) 
	: hWnd_(0), nid_({}), icon_(0) 
{
	auto class_name = load_string(instance, IDS_LUNAR_CLASS); 
	auto window_title = load_string(instance, IDS_LUNAR_TITLE);

	hWnd_ = CreateWindow(class_name.c_str(), window_title.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, instance, NULL);
	if (!hWnd_) 
		throw std::runtime_error("Failed to create window.");

	icon_ = LoadIcon(instance, MAKEINTRESOURCE(IDI_CONTROLLER_NOFACE));

	nid_.cbSize = sizeof(NOTIFYICONDATA);
	nid_.hWnd = hWnd_;
	nid_.uID = IDI_CONTROLLER_NOFACE;
	nid_.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid_.hIcon = icon_;
	nid_.uCallbackMessage = WM_USER_LUNARTRAY;
	
	LoadString(instance, IDS_LUNAR_TOOLTIP, nid_.szTip, sizeof(nid_.szTip) / sizeof(nid_.szTip[0]));
	
	if (!Shell_NotifyIcon(NIM_ADD, &nid_))
		throw std::runtime_error("Failed to add icon to tray.");
}

/// <summary>
/// Destroy the tray icon and the window.
/// </summary>
lunar_tray::~lunar_tray() {
	// remove shell icon 
	Shell_NotifyIcon(NIM_DELETE, &nid_);
	
	// destroy window
	if (hWnd_)
		DestroyWindow(hWnd_);
	
	// destroy icon
	if (icon_)
		DestroyIcon(icon_);
}

/// <summary>
/// Handle the window messages for the tray icon.
/// </summary>
/// <returns>The last wParam which can be used as exit status.</returns>
int lunar_tray::event_loop() {
	MSG  msg;
	BOOL ret; 

	while ((ret = GetMessage(&msg, NULL, 0, 0)) != 0) {
		if (ret == -1) {
			throw std::runtime_error("error encountered in event handling.");
		} else {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return static_cast<int>(msg.wParam);
}

/// <summary>
/// Obtain the window handle of this tray.
/// </summary>
/// <returns>A window handle.</returns>
HWND lunar_tray::get_hwnd() const noexcept {
	return hWnd_;
}

/// <summary>
/// Send an error message to the event handler to be displayed as MessageBox and post a quit message.
/// </summary>
/// <param name="message">The error message.</param>
void lunar_tray::send_error(const std::wstring& message) const noexcept {
	SendMessage(hWnd_, WM_USER_LUNARERROR, TRUE, reinterpret_cast<LPARAM>(message.c_str())); 
}

/// <summary>
/// Send an error message to the event handler to be displayed as MessageBox and post a quit message.
/// </summary>
/// <param name="message">The error message.</param>
void lunar_tray::send_error(const std::string& message) const noexcept {
	SendMessage(hWnd_, WM_USER_LUNARERROR, FALSE, reinterpret_cast<LPARAM>(message.c_str()));
}

/// <summary>
/// Load the IDC_LUNARMENU menu and display it.
/// </summary>
/// <param name="hWnd">The parent window handle.</param>
void lunar_tray::context_menu(HWND hWnd) {
	POINT mouse_position;
	GetCursorPos(&mouse_position);

	auto menu = LoadMenu(NULL, MAKEINTRESOURCE(IDC_LUNARMENU));
	if (!menu) 
		return;

	auto sub_menu = GetSubMenu(menu, 0);
	if (!sub_menu)
		return;

	SetForegroundWindow(hWnd); 

	TrackPopupMenu(sub_menu, TPM_BOTTOMALIGN | TPM_LEFTALIGN, mouse_position.x, mouse_position.y, 0, hWnd, NULL);
}

/// <summary>
/// Handle all messages on the lunartray window.
/// </summary>
/// <param name="hWnd">The window handle of the window the event occurred on.</param>
/// <param name="message">The event message.</param>
/// <param name="wParam">The event wParam.</param>
/// <param name="lParam">The event lParam.</param>
/// <returns>LRESULT based on event handling.</returns>
LRESULT CALLBACK lunar_tray::winproc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	int menu_id, menu_event;
	
	switch (message) {
		case WM_USER_LUNARTRAY:
			// handle tray icon events
			switch (LOWORD(lParam)) {
				case WM_RBUTTONDOWN:
					context_menu(hWnd);
					return TRUE;
			}
			break;
		case WM_USER_LUNARERROR:
			if (wParam) {
				MessageBoxW(hWnd, reinterpret_cast<LPCWSTR>(lParam), TEXT("Error"), MB_OK | MB_ICONERROR); 
			} else {
				MessageBoxA(hWnd, reinterpret_cast<LPSTR>(lParam), "Error", MB_OK | MB_ICONERROR);
			}

			PostQuitMessage(0); 
			break;
		case WM_COMMAND:
			// handle menu events
			menu_id    = LOWORD(wParam);
			menu_event = HIWORD(wParam);

			switch (menu_id) {
			case ID_SYSTEMTRAYMENU_CLOSE: 
				PostQuitMessage(0);
				return TRUE;
			}
			
			break;
		case WM_DESTROY:
			// handle window destruction
			PostQuitMessage(0);
			return TRUE;
	}

	// in all other cases let's use the default window procedure
	return DefWindowProc(hWnd, message, wParam, lParam);
}

/// <summary>
/// Load the pointer to a string resource.
/// </summary>
/// <param name="instance">The application instance.</param>
/// <param name="id">The resource ID.</param>
/// <returns>A pointer to the resource or nullptr if it could not be loaded.</returns>
LPCWCHAR lunar_tray::load_string_pointer(HINSTANCE instance, UINT id) {
	WCHAR** buffer = nullptr;
	
	auto length = LoadString(instance, id, reinterpret_cast<WCHAR*>(&buffer), 0);
	if (length == 0) 
		return nullptr;
	
	return *buffer;
}

/// <summary>
/// Load a string resource as std::wstring.
/// </summary>
/// <param name="instance">The application instance.</param>
/// <param name="id">The resource ID.</param>
/// <returns>A std::wstring on success or an empty string on failure.</returns>
std::wstring lunar_tray::load_string(HINSTANCE instance, UINT id) {
	WCHAR** buffer = nullptr;
	auto required = LoadString(instance, id, reinterpret_cast<WCHAR*>(&buffer), 0);
	if (required == 0)
		return L"";

	std::vector<WCHAR> string_buffer(required + 1);
	string_buffer[required] = L'\0';
	
	LoadString(instance, id, string_buffer.data(), required + 1);

	return std::wstring(string_buffer.data());
}