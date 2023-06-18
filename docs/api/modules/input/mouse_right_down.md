# input_object:mouse_right_down

Adds a mouse right button down input to the queue in the input object.

## Usage

```lua
input_object:mouse_right_down();
```

## Parameters

`input_object:mouse_right_down` takes no parameters.

## Return Value

`input_object:mouse_right_down` returns `userdata:lunar_input` to allow for method chaining.

## Example

```lua
local input = require "lunar360.input";
local input_object = input.new();

input_object:mouse_right_down();
input_object:mouse_right_up();
-- simulate a right mouse click

input_object:send();
```