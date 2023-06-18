#include "lunar_input.hpp"
#include "lunar_helpers.hpp"

#include <string>
#include <unordered_map>


static const std::unordered_map<std::string, int> string_to_vkey = {
	{ "backspace", VK_BACK },
	{ "tab", VK_TAB },
	{ "enter", VK_RETURN },
	{ "shift", VK_SHIFT },
	{ "ctrl", VK_CONTROL },
	{ "alt", VK_MENU },
	{ "pause", VK_PAUSE },
	{ "capslock", VK_CAPITAL },
	{ "esc", VK_ESCAPE },
	{ "space", VK_SPACE },
	{ "pageup", VK_PRIOR },
	{ "pagedown", VK_NEXT },
	{ "end", VK_END },
	{ "home", VK_HOME },
	{ "left", VK_LEFT },
	{ "up", VK_UP },
	{ "right", VK_RIGHT },
	{ "down", VK_DOWN },
	{ "printscreen", VK_SNAPSHOT },
	{ "insert", VK_INSERT },
	{ "delete", VK_DELETE },
	{ "lwin", VK_LWIN },
	{ "rwin", VK_RWIN },
	{ "apps", VK_APPS },
	{ "numlock", VK_NUMLOCK },
	{ "scrolllock", VK_SCROLL },
	{ "numpad0", VK_NUMPAD0 },
	{ "numpad1", VK_NUMPAD1 },
	{ "numpad2", VK_NUMPAD2 },
	{ "numpad3", VK_NUMPAD3 },
	{ "numpad4", VK_NUMPAD4 },
	{ "numpad5", VK_NUMPAD5 },
	{ "numpad6", VK_NUMPAD6 },
	{ "numpad7", VK_NUMPAD7 },
	{ "numpad8", VK_NUMPAD8 },
	{ "numpad9", VK_NUMPAD9 },
	{ "numpad*", VK_MULTIPLY },
	{ "numpad+", VK_ADD },
	{ "numpad-", VK_SUBTRACT },
	{ "numpad.", VK_DECIMAL },
	{ "numpad/", VK_DIVIDE },
	{ "f1", VK_F1 },
	{ "f2", VK_F2 },
	{ "f3", VK_F3 },
	{ "f4", VK_F4 },
	{ "f5", VK_F5 },
	{ "f6", VK_F6 },
	{ "f7", VK_F7 },
	{ "f8", VK_F8 },
	{ "f9", VK_F9 },
	{ "f10", VK_F10 },
	{ "f11", VK_F11 },
	{ "f12", VK_F12 },
	{ "f13", VK_F13 },
	{ "f14", VK_F14 },
	{ "f15", VK_F15 },
	{ "f16", VK_F16 },
	{ "f17", VK_F17 },
	{ "f18", VK_F18 },
	{ "f19", VK_F19 },
	{ "f20", VK_F20 },
	{ "f21", VK_F21 },
	{ "f22", VK_F22 },
	{ "f23", VK_F23 },
	{ "f24", VK_F24 },
	{ "numlock", VK_NUMLOCK },
	{ "scrolllock", VK_SCROLL },
	{ "lshift", VK_LSHIFT },
	{ "rshift", VK_RSHIFT },
	{ "lctrl", VK_LCONTROL },
	{ "rctrl", VK_RCONTROL },
	{ "lalt", VK_LMENU },
	{ "ralt", VK_RMENU },
	{ "browser_back", VK_BROWSER_BACK },
	{ "browser_forward", VK_BROWSER_FORWARD },
	{ "browser_refresh", VK_BROWSER_REFRESH },
	{ "browser_stop", VK_BROWSER_STOP },
	{ "browser_search", VK_BROWSER_SEARCH },
	{ "browser_favorites", VK_BROWSER_FAVORITES },
	{ "browser_home", VK_BROWSER_HOME },
	{ "volume_mute", VK_VOLUME_MUTE },
	{ "volume_down", VK_VOLUME_DOWN },
	{ "volume_up", VK_VOLUME_UP },
	{ "next_track", VK_MEDIA_NEXT_TRACK },
	{ "prev_track", VK_MEDIA_PREV_TRACK },
	{ "stop", VK_MEDIA_STOP },
	{ "play_pause", VK_MEDIA_PLAY_PAUSE },
	{ "launch_mail", VK_LAUNCH_MAIL },
	{ "launch_media_select", VK_LAUNCH_MEDIA_SELECT },
	{ "launch_app1", VK_LAUNCH_APP1 },
	{ "launch_app2", VK_LAUNCH_APP2 },
	{ "oem_1", VK_OEM_1 },
	{ "oem_plus", VK_OEM_PLUS },
	{ "oem_comma", VK_OEM_COMMA },
	{ "oem_minus", VK_OEM_MINUS },
	{ "oem_period", VK_OEM_PERIOD },
	{ "oem_2", VK_OEM_2 },
	{ "oem_3", VK_OEM_3 },
	{ "oem_4", VK_OEM_4 },
	{ "oem_5", VK_OEM_5 },
	{ "oem_6", VK_OEM_6 },
	{ "oem_7", VK_OEM_7 },
	{ "oem_8", VK_OEM_8 },
	{ "oem_102", VK_OEM_102 },
	{ "processkey", VK_PROCESSKEY },
	{ "packet", VK_PACKET },
	{ "attn", VK_ATTN },
	{ "crsel", VK_CRSEL },
	{ "exsel", VK_EXSEL },
	{ "ereof", VK_EREOF },
	{ "play", VK_PLAY },
	{ "zoom", VK_ZOOM },
	{ "noname", VK_NONAME },
	{ "pa1", VK_PA1 },
	{ "oem_clear", VK_OEM_CLEAR }
};

static int translate_string_to_vkey(const std::string& name) {
	if (name.size() == 1)
		return static_cast<int>(name[0]);
	if (string_to_vkey.contains(name))
		return string_to_vkey.at(name);
	return 0;
}

lunar_input::lunar_input() 
	: inputs_() {}

int lunar_input::register_class(lua_State* L) {
	lunar_helpers::preload_module(L, "lunar360.input", loader);
	return 0;
}

int lunar_input::loader(lua_State* L) {
	luaL_newmetatable(L, class_name_);
	
	lua_pushstring(L, class_name_);
	lua_setfield(L, -2, "__name");

	lua_pushcfunction(L, gc);
	lua_setfield(L, -2, "__gc");

	lua_pushcfunction(L, close);
	lua_setfield(L, -2, "__close");

	lua_newtable(L);

	lua_pushcfunction(L, send);
	lua_setfield(L, -2, "send");

	lua_pushcfunction(L, mouse_left_down);
	lua_setfield(L, -2, "mouse_left_down");
	
	lua_pushcfunction(L, mouse_left_up);
	lua_setfield(L, -2, "mouse_left_up");
	
	lua_pushcfunction(L, mouse_right_down);
	lua_setfield(L, -2, "mouse_right_down");
	
	lua_pushcfunction(L, mouse_right_up);
	lua_setfield(L, -2, "mouse_right_up");
	
	lua_pushcfunction(L, mouse_middle_down);
	lua_setfield(L, -2, "mouse_middle_down");

	lua_pushcfunction(L, mouse_middle_up);
	lua_setfield(L, -2, "mouse_middle_up");

	lua_pushcfunction(L, mouse_move);
	lua_setfield(L, -2, "mouse_move");

	lua_pushcfunction(L, mouse_vertical_scroll);
	lua_setfield(L, -2, "mouse_vertical_scroll");

	lua_pushcfunction(L, mouse_horizontal_scroll);
	lua_setfield(L, -2, "mouse_horizontal_scroll");

	lua_pushcfunction(L, key_down);
	lua_setfield(L, -2, "key_down");

	lua_pushcfunction(L, key_up);
	lua_setfield(L, -2, "key_up");
	
	lua_pushcfunction(L, key_press);
	lua_setfield(L, -2, "key_press");

	lua_setfield(L, -2, "__index");

	lua_pop(L, 1);

	lua_newtable(L);
	lua_pushcfunction(L, new_instance);
	lua_setfield(L, -2, "new");

	lua_pushcfunction(L, quick_key_press);
	lua_setfield(L, -2, "key_press");
	
	lua_pushcfunction(L, quick_left_click);
	lua_setfield(L, -2, "left_click");

	lua_pushcfunction(L, quick_right_click);
	lua_setfield(L, -2, "right_click");

	lua_pushcfunction(L, quick_middle_click);
	lua_setfield(L, -2, "middle_click");

	lua_pushcfunction(L, quick_mouse_move);
	lua_setfield(L, -2, "mouse_move");

	lua_pushcfunction(L, quick_mouse_vertical_scroll);
	lua_setfield(L, -2, "mouse_vertical_scroll");
	
	lua_pushcfunction(L, quick_mouse_horizontal_scroll);
	lua_setfield(L, -2, "mouse_horizontal_scroll");

	return 1;
}

int lunar_input::new_instance(lua_State* L) {
	auto udata = static_cast<lunar_input**>(lua_newuserdata(L, sizeof(lunar_input*))); 
	*udata = new lunar_input(); 
	luaL_setmetatable(L, class_name_); 
	return 1; 
}

int lunar_input::quick_key_press(lua_State* L) {
	lunar_input input;
	
	auto key = translate_string_to_vkey(luaL_checkstring(L, 1));
	if (!key)
		luaL_argerror(L, 1, "invalid key name");
	
	input.push_keyboard(key, true);
	input.push_keyboard(key, false);
	
	lua_pushinteger(L, static_cast<lua_Integer>(SendInput(static_cast<UINT>(input.inputs_.size()), input.inputs_.data(), sizeof(INPUT))));
	return 1;
}

int lunar_input::quick_left_click(lua_State* L) {
	lunar_input input;

	input.push_mouse(MOUSEEVENTF_LEFTDOWN);
	input.push_mouse(MOUSEEVENTF_LEFTUP);
	
	lua_pushinteger(L, static_cast<lua_Integer>(SendInput(static_cast<UINT>(input.inputs_.size()), input.inputs_.data(), sizeof(INPUT))));
	return 1;
}

int lunar_input::quick_right_click(lua_State* L) {
	lunar_input input;

	input.push_mouse(MOUSEEVENTF_RIGHTDOWN);
	input.push_mouse(MOUSEEVENTF_RIGHTUP);

	lua_pushinteger(L, static_cast<lua_Integer>(SendInput(static_cast<UINT>(input.inputs_.size()), input.inputs_.data(), sizeof(INPUT))));
	return 1;
}

int lunar_input::quick_middle_click(lua_State* L) {
	lunar_input input;

	input.push_mouse(MOUSEEVENTF_MIDDLEDOWN);
	input.push_mouse(MOUSEEVENTF_MIDDLEUP);

	lua_pushinteger(L, static_cast<lua_Integer>(SendInput(static_cast<UINT>(input.inputs_.size()), input.inputs_.data(), sizeof(INPUT))));
	return 1;
}

int lunar_input::quick_mouse_move(lua_State* L) {
	lunar_input input;

	auto displacementX = luaL_checknumber(L, 1);
	auto displacementY = luaL_checknumber(L, 2);

	auto absolute = false;
	if (lua_gettop(L) >= 3) {
		luaL_checktype(L, 3, LUA_TBOOLEAN);
		absolute = lua_toboolean(L, 3) != 0;
	}
	
	auto flags = MOUSEEVENTF_MOVE;
	if (absolute)
		flags |= MOUSEEVENTF_ABSOLUTE;

	input.push_mouse(flags, 0,
		static_cast<LONG>(displacementX), 
		static_cast<LONG>(displacementY)); 

	lua_pushinteger(L, static_cast<lua_Integer>(SendInput(static_cast<UINT>(input.inputs_.size()), input.inputs_.data(), sizeof(INPUT))));
	return 1;
}

int lunar_input::quick_mouse_vertical_scroll(lua_State* L) {
	lunar_input input; 
	auto displacement = luaL_checknumber(L, 1);
	
	input.push_mouse(MOUSEEVENTF_WHEEL, static_cast<DWORD>(displacement));

	lua_pushinteger(L, static_cast<lua_Integer>(SendInput(static_cast<UINT>(input.inputs_.size()), input.inputs_.data(), sizeof(INPUT))));
	return 1;
}

int lunar_input::quick_mouse_horizontal_scroll(lua_State* L) {
	lunar_input input;
	auto displacement = luaL_checknumber(L, 1);

	input.push_mouse(MOUSEEVENTF_HWHEEL, static_cast<DWORD>(displacement));

	lua_pushinteger(L, static_cast<lua_Integer>(SendInput(static_cast<UINT>(input.inputs_.size()), input.inputs_.data(), sizeof(INPUT))));
	return 1;
}

int lunar_input::gc(lua_State* L) {
	auto input = *static_cast<lunar_input**>(luaL_checkudata(L, 1, class_name_)); 
	delete input;
	return 0;
}

int lunar_input::close(lua_State* L) {
	auto input = *static_cast<lunar_input**>(luaL_checkudata(L, 1, class_name_)); 
	if (input->inputs_.empty())
		return 0;

	SendInput(static_cast<UINT>(input->inputs_.size()), input->inputs_.data(), sizeof(INPUT));

	return 0; 
}

int lunar_input::send(lua_State* L) {
	auto input = *static_cast<lunar_input**>(luaL_checkudata(L, 1, class_name_));
	if (input->inputs_.empty()) {
		lua_pushinteger(L, 0);
		return 1;
	}

	auto result = SendInput(static_cast<UINT>(input->inputs_.size()), input->inputs_.data(), sizeof(INPUT)); 
	input->inputs_.clear(); 
	lua_pushinteger(L, static_cast<lua_Integer>(result));
	return 1;
}

int lunar_input::mouse_left_down(lua_State* L) {
	auto input = *static_cast<lunar_input**>(luaL_checkudata(L, 1, class_name_)); 
	input->push_mouse(MOUSEEVENTF_LEFTDOWN); 
	lua_pushvalue(L, 1);
	return 1;
}

int lunar_input::mouse_left_up(lua_State* L) {
	auto input = *static_cast<lunar_input**>(luaL_checkudata(L, 1, class_name_));
	input->push_mouse(MOUSEEVENTF_LEFTUP); 
	lua_pushvalue(L, 1);
	return 1; 
}

int lunar_input::mouse_right_down(lua_State* L) {
	auto input = *static_cast<lunar_input**>(luaL_checkudata(L, 1, class_name_));
	input->push_mouse(MOUSEEVENTF_RIGHTDOWN);
	lua_pushvalue(L, 1);
	return 1;
}

int lunar_input::mouse_right_up(lua_State* L) {
	auto input = *static_cast<lunar_input**>(luaL_checkudata(L, 1, class_name_)); 
	input->push_mouse(MOUSEEVENTF_RIGHTUP);
	lua_pushvalue(L, 1); 
	return 1;
}

int lunar_input::mouse_middle_down(lua_State* L) {
	auto input = *static_cast<lunar_input**>(luaL_checkudata(L, 1, class_name_)); 
	input->push_mouse(MOUSEEVENTF_MIDDLEDOWN); 
	lua_pushvalue(L, 1); 
	return 1;
}

int lunar_input::mouse_middle_up(lua_State* L) {
	auto input = *static_cast<lunar_input**>(luaL_checkudata(L, 1, class_name_)); 
	input->push_mouse(MOUSEEVENTF_MIDDLEUP); 
	lua_pushvalue(L, 1); 
	return 1;
}

int lunar_input::mouse_move(lua_State* L) {
	auto input = *static_cast<lunar_input**>(luaL_checkudata(L, 1, class_name_)); 
	auto displacementX = luaL_checknumber(L, 2);
	auto displacementY = luaL_checknumber(L, 3);
	auto absolute = false;

	if (lua_gettop(L) >= 4) {
		luaL_checktype(L, 4, LUA_TBOOLEAN);
		absolute = lua_toboolean(L, 4) != 0;
	}

	auto flags = MOUSEEVENTF_MOVE;
	if (absolute)
		flags |= MOUSEEVENTF_ABSOLUTE;

	input->push_mouse(flags, 0,
		static_cast<LONG>(displacementX),
		static_cast<LONG>(displacementY));
	lua_pushvalue(L, 1);
	return 1;
}

int lunar_input::mouse_vertical_scroll(lua_State* L) {
	auto input = *static_cast<lunar_input**>(luaL_checkudata(L, 1, class_name_));
	auto displacement = luaL_checknumber(L, 2); 
	input->push_mouse(MOUSEEVENTF_WHEEL, static_cast<DWORD>(displacement)); 
	lua_pushvalue(L, 1); 
	return 1; 
}

int lunar_input::mouse_horizontal_scroll(lua_State* L) {
	auto input = *static_cast<lunar_input**>(luaL_checkudata(L, 1, class_name_)); 
	auto displacement = luaL_checknumber(L, 2); 
	input->push_mouse(MOUSEEVENTF_HWHEEL, static_cast<DWORD>(displacement));
	lua_pushvalue(L, 1); 
	return 1;
}

int lunar_input::key_down(lua_State* L) {
	auto input = *static_cast<lunar_input**>(luaL_checkudata(L, 1, class_name_)); 
	auto key = translate_string_to_vkey(luaL_checkstring(L, 2)); 
	if (!key)
		luaL_argerror(L, 2, "invalid key name");
	input->push_keyboard(key, true);
	lua_pushvalue(L, 1);
	return 1;
}

int lunar_input::key_up(lua_State* L) {
	auto input = *static_cast<lunar_input**>(luaL_checkudata(L, 1, class_name_));
	auto key = translate_string_to_vkey(luaL_checkstring(L, 2));
	if (!key)
		luaL_argerror(L, 2, "invalid key name");
	input->push_keyboard(key, false);
	lua_pushvalue(L, 1);
	return 1;
}

int lunar_input::key_press(lua_State* L) {
	auto input = *static_cast<lunar_input**>(luaL_checkudata(L, 1, class_name_));
	auto key = translate_string_to_vkey(luaL_checkstring(L, 2));
	if (!key)
		luaL_argerror(L, 2, "invalid key name");
	input->push_keyboard(key, true);
	input->push_keyboard(key, false);
	lua_pushvalue(L, 1);
	return 1;
}

void lunar_input::push_mouse(DWORD flags, DWORD data, LONG dx, LONG dy) {
	auto& input = emplace_cleared();

	input.type = INPUT_MOUSE;
	input.mi.dwFlags = flags;
	input.mi.mouseData = data;
	input.mi.dx = dx;
	input.mi.dy = dy;
}

void lunar_input::push_keyboard(int key, bool down) {
	auto& input = emplace_cleared();

	input.type = INPUT_KEYBOARD;
	input.ki.wVk = key; 
	input.ki.dwFlags = down ? 0 : KEYEVENTF_KEYUP;
}

INPUT& lunar_input::emplace_cleared() {
	auto& v = inputs_.emplace_back();
	ZeroMemory(&v, sizeof(INPUT));
	return v;
} 