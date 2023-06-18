# controller_object:set_left_thumb_deadzone

Set the left thumb deadzone of the controller, the default value is GAMEPAD_LEFT_THUMB_DEADZONE which is equal to 7849.

## Usage

```lua
controller_object:set_left_thumb_deadzone(deadzone);
```

> *Note*: Each controller has a different deadzone, try to find the one that works best for you.

## Parameters

| Parameter               | Type     | Description                                                  |
| ----------------------- | -------- | ------------------------------------------------------------ |
| 1. Deadzone             | integer  | The deadzone for the left thumbstick                         |

## Return Value

`controller_object:set_left_thumb_deadzone` returns `controller_object` to allow for method chaining.

## Example

```lua
local controller = require "lunar360.controller";
local player1 = controller.new(0);

player1:set_left_thumb_deadzone(10000);
```