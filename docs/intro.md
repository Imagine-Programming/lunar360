# Lunar 360

> Lunar 360 is a simple binding between Microsoft's XInput and Lua 5.4. Lunar 360 allows you to write a simple script listening for XInput Controller changes and do with them whatever you want. Below you will find an impression of a complete script that translates the input from an XBox controller to HID inputs (mouse and keyboard).

### Tiny impression
```lua
local controller = require "lunar360.controller";
local easing     = require "lunar360.easing";
local input      = require "lunar360.input";
local process    = require "lunar360.process";

local CONTROLLER_INDEX        <const> = 0;
local POLLING_RATE            <const> = 120; -- 120Hz 
local UNIFORM_DEADZONE        <const> = 2000; 
local MOUSE_MOVE_DISPLACEMENT <const> = 30.0;
local MOUSE_SCROLL_START_ZONE <const> = 0.15;

local easing_function <const> = easing.ease_in_circular;
local abs <const> = math.abs; 

-- assume controller 0 (player 1) and only act if connected
local c1 = controller.new(CONTROLLER_INDEX);

-- set a custom deadzone and override the Windows XInput defaults.
c1:set_left_thumb_deadzone(UNIFORM_DEADZONE)
  :set_right_thumb_deadzone(UNIFORM_DEADZONE);

-- open OSK on right thumb double press
c1:on(GAMEPAD_RIGHT_THUMB, "double-press", process.start_nowait:bind("osk.exe"));

-- use the dpad keys as up/down/left/right keys. 
c1:on(GAMEPAD_DPAD_UP,    "down-press", input.key_press:bind("up"));
c1:on(GAMEPAD_DPAD_DOWN,  "down-press", input.key_press:bind("down"));
c1:on(GAMEPAD_DPAD_LEFT,  "down-press", input.key_press:bind("left"));
c1:on(GAMEPAD_DPAD_RIGHT, "down-press", input.key_press:bind("right"));

-- set the polling rate in Hertz
poller:set_interval(POLLING_RATE);

-- enter the polling loop
poller:loop(function()
	c1:poll(); -- update controller state and trigger events, such as double-press

	if (not c1:connected()) then 
		return; -- nothing to do here.
	end

	-- when a new input is created with a to-be-closed annotation, it will be applied without having to invoke inp:send().
	-- we batch them now, because it is more efficient to send multiple events in one go rather than invoking SendInput for 
	-- each thing we want to do. 
	local inp <close> = input.new(); 

	-- moving the mouse using the right thumb
	local rd = c1:get_right_thumb_delta(); 
	if (rd.n > 0) then
		inp:mouse_move(
			(MOUSE_MOVE_DISPLACEMENT * rd.x) * easing_function(rd.n),
			(MOUSE_MOVE_DISPLACEMENT * rd.y) * easing_function(rd.n)
		);
	end 

	-- scrolling using the left thumb 
	local ld = c1:get_left_thumb_delta();
	if (ld.n > 0) then 
		if (abs(ld.y) > MOUSE_SCROLL_START_ZONE) then 
			inp:mouse_vertical_scroll((-1.0 * ld.y * WHEEL_DELTA) * easing_function(ld.n));
		end 

		if (abs(ld.x) > MOUSE_SCROLL_START_ZONE) then 
			inp:mouse_horizontal_scroll((ld.x * WHEEL_DELTA) * easing_function(ld.n));
		end 
	end

	-- left mouse button 
	if (c1:get_right_trigger_toggled()) then 
		-- trigger delta: double (0.0 through 1.0)
		if (c1:get_right_trigger_delta() > 0.0) then 
			inp:mouse_left_down();
		else 
			inp:mouse_left_up();
		end 
	end

	-- right mouse button 
	if (c1:get_left_trigger_toggled()) then 
		-- trigger delta: double (0.0 through 1.0)
		if (c1:get_left_trigger_delta() > 0.0) then 
			inp:mouse_right_down();
		else 
			inp:mouse_right_up();
		end 
	end
end);
```