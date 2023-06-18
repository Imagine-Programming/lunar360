# lunar360.input 

The input module contains all the functionality for sending input to the system, such as keyboard and mouse inputs.

It can be loaded with the following code:

```lua
local input = require "lunar360.input";
```

## Instantiating an Input Object

To instantiate an input object, you can use the `input.new` function. This function takes no arguments.

```lua
local input = require "lunar360.input";
local input_object = input.new();
```

## Add inputs to the instance

To add inputs to the instance, one can add them using the different methods. 

- [input_object:mouse_left_down](/api/modules/input/mouse_left_down.md)
- [input_object:mouse_left_up](/api/modules/input/mouse_left_up.md)
- [input_object:mouse_right_down](/api/modules/input/mouse_right_down.md)
- [input_object:mouse_right_up](/api/modules/input/mouse_right_up.md)
- [input_object:mouse_middle_down](/api/modules/input/mouse_middle_down.md)
- [input_object:mouse_middle_up](/api/modules/input/mouse_middle_up.md)
- [input_object:mouse_move](/api/modules/input/mouse_move.md)
- [input_object:mouse_vertical_scroll](/api/modules/input/mouse_vertical_scroll.md)
- [input_object:mouse_horizontal_scroll](/api/modules/input/mouse_horizontal_scroll.md)
- [input_object:key_down](/api/modules/input/key_down.md)
- [input_object:key_up](/api/modules/input/key_up.md)
- [input_object:key_press](/api/modules/input/key_press.md)

```lua
local input = require "lunar360.input";
local input_object = input.new();

input_object:mouse_left_down();
input_object:mouse_left_up();
-- simulate a mouse click

input_object:mouse_move(100, 100);
-- move the mouse to current position + 100 pixels to the right and 100 pixels down

input_object:key_down("a"); -- press the "a" key down
input_object:key_up("a");   -- release the "a" key

input_object:send();
-- send all the inputs to the system
```

## Use the Lua 5.4 to-be-closed feature

The input object can be used with the Lua 5.4 to-be-closed feature. This means that the input object will be automatically sent to the system when the object is leaving the scope (closed).

```lua 
local input = require "lunar360.input";
local input_object <close> = input.new();

input_object:mouse_left_down();
input_object:mouse_left_up();
-- end of scope reached, input_object:send will be called implicitly
```

## Send inputs using the one-shot functions

There are several static functions that can be used to send inputs to the system immediately. These functions are:

- [input.key_press](/api/modules/input/quick_key_press.md)
- [input.left_click](/api/modules/input/quick_left_click.md)
- [input.right_click](/api/modules/input/quick_right_click.md)
- [input.middle_click](/api/modules/input/quick_middle_click.md)
- [input.mouse_move](/api/modules/input/quick_mouse_move.md)
- [input.mouse_vertical_scroll](/api/modules/input/quick_mouse_vertical_scroll.md)
- [input.mouse_horizontal_scroll](/api/modules/input/quick_mouse_horizontal_scroll.md)

```lua
local input = require "lunar360.input";

input.key_press("a"); -- press the "a" key down and release it
```

This is useful in combination with [function binding](/api/bind.md) to create a bound function with a parameter. 
This can in turn be used in an event handler to easily translate an event to an input.

```lua
local input = require "lunar360.input";
local controller = require "lunar360.controller";

local controller_object = controller.new_first_available();

controller_object:on(GAMEPAD_A, "single-press", input.key_press:bind("a"));
-- when the "a_pressed" event is fired, the "a" key will be pressed and released
```