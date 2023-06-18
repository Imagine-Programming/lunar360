# controller_object:get_left_trigger_toggled

Get the left trigger toggled state of the controller.

## Usage

```lua
local toggled = controller_object:get_left_trigger_toggled();
```

## Parameters

`controller_object:get_left_trigger_toggled` takes no parameters.

## Return Value

`controller_object:get_left_trigger_toggled` returns a `boolean` representing the toggled state of the left trigger since the previous poll.

## Example

```lua
local controller = require "lunar360.controller";
local player1 = controller.new(0);

local toggled = player1:get_left_trigger_toggled();
```
