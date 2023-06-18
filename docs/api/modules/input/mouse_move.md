# input_object:mouse_move

Adds a mouse move input to the queue in the input object.

## Usage

```lua
input_object:mouse_move(x, y);
```

## Parameters

| Parameter               | Type    | Description                                                           |
| ----------------------- | ------- | --------------------------------------------------------------------- |
| 1. X                    | integer | The X coordinate to move the mouse to.                                |
| 2. Y                    | integer | The Y coordinate to move the mouse to.                                |
| 3. Absolute             | boolean | Whether the coordinates are absolute or relative, `false` by default. |

## Return Value

`input_object:mouse_move` returns `userdata:lunar_input` to allow for method chaining.

## Example

```lua
local input = require "lunar360.input";
local input_object = input.new();

input_object:mouse_move(100, 100, true);
input_object:mouse_move(25, 0);
-- move the mouse to (100, 100) and then move it 25 pixels to the right

input_object:send();
```