# input_object:mouse_middle_up

Adds a mouse middle button up input to the queue in the input object.

## Usage

```lua
input_object:mouse_middle_up();
```

## Parameters

`input_object:mouse_middle_up` takes no parameters.

## Return Value

`input_object:mouse_middle_up` returns `userdata:lunar_input` to allow for method chaining.

## Example

```lua
local input = require "lunar360.input";
local input_object = input.new();

input_object:mouse_middle_down();
input_object:mouse_middle_up();
-- simulate a middle mouse click

input_object:send();
```