# controller_object:get_right_thumb_deadzone

Get the right thumb deadzone of the controller, the default value is GAMEPAD_RIGHT_THUMB_DEADZONE which is equal to 8689.

## Usage

```lua
local deadzone = controller_object:get_right_thumb_deadzone();
```

## Parameters

`controller_object:get_right_thumb_deadzone` takes no parameters.

## Return Value

`controller_object:get_right_thumb_deadzone` returns an `integer` representing the deadzone for the right thumbstick.

## Example

```lua
local controller = require "lunar360.controller";
local player1 = controller.new(0);

local deadzone = player1:get_right_thumb_deadzone();
```