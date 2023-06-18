#pragma once 

#include <lua.hpp>
#include <windows.h>

#include <vector>

class lunar_input {
public:
	lunar_input();
	
	static int register_class(lua_State* L);
	static int loader(lua_State* L);
	static int new_instance(lua_State* L);
	
	static int quick_key_press(lua_State* L);
	static int quick_left_click(lua_State* L);
	static int quick_right_click(lua_State* L);
	static int quick_middle_click(lua_State* L);
	static int quick_mouse_move(lua_State* L);
	static int quick_mouse_vertical_scroll(lua_State* L);
	static int quick_mouse_horizontal_scroll(lua_State* L);

	static int gc(lua_State* L);
	static int close(lua_State* L); 
	static int send(lua_State* L);

	static int mouse_left_down(lua_State* L);
	static int mouse_left_up(lua_State* L);
	static int mouse_right_down(lua_State* L);
	static int mouse_right_up(lua_State* L);
	static int mouse_middle_down(lua_State* L);
	static int mouse_middle_up(lua_State* L);
	static int mouse_move(lua_State* L); 
	static int mouse_vertical_scroll(lua_State* L);
	static int mouse_horizontal_scroll(lua_State* L);

	static int key_down(lua_State* L);
	static int key_up(lua_State* L);
	static int key_press(lua_State* L);
private:
	void push_mouse(DWORD flags, DWORD data = 0, LONG dx = 0, LONG dy = 0); 
	void push_keyboard(int key, bool down);
	INPUT& emplace_cleared();

	std::vector<INPUT> inputs_;

	static inline const char class_name_[] = "lunar_input";
};