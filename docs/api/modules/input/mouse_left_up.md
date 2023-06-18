# input_object:mouse_left_up

Adds a mouse left button up input to the queue in the input object.

## Usage

```lua
input_object:mouse_left_up();
```

## Parameters

`input_object:mouse_left_up` takes no parameters.

## Return Value

`input_object:mouse_left_up` returns `userdata:lunar_input` to allow for method chaining.

## Example

```lua
local input = require "lunar360.input";
local input_object = input.new();

input_object:mouse_left_down();
input_object:mouse_left_up();
-- simulate a mouse click

input_object:send();
```
