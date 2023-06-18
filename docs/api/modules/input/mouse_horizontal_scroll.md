# input_object:mouse_horizontal_scroll

Adds a mouse horizontal scroll input to the queue in the input object.

## Usage

```lua
input_object:mouse_horizontal_scroll(WHEEL_DELTA * 5);
```

## Parameters

| Parameter               | Type    | Description                                                           |
| ----------------------- | ------- | --------------------------------------------------------------------- |
| 1. Horizontal Scroll    | integer | The amount to scroll horizontally.                                    |

## Return Value

`input_object:mouse_horizontal_scroll` returns `userdata:lunar_input` to allow for method chaining.

## Example

```lua
local input = require "lunar360.input";
local input_object = input.new();

input_object:mouse_horizontal_scroll(WHEEL_DELTA * 5);
input_object:send();
```