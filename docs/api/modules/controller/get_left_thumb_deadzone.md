# controller_object:get_left_thumb_deadzone

Get the left thumb deadzone of the controller, the default value is GAMEPAD_LEFT_THUMB_DEADZONE which is equal to 7849.

## Usage

```lua
local deadzone = controller_object:get_left_thumb_deadzone();
```

## Parameters

`controller_object:get_left_thumb_deadzone` takes no parameters.

## Return Value

`controller_object:get_left_thumb_deadzone` returns an `integer` representing the deadzone for the left thumbstick.

## Example

```lua
local controller = require "lunar360.controller";
local player1 = controller.new(0);

local deadzone = player1:get_left_thumb_deadzone();
```