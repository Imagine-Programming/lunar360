# controller_object:get_trigger_threshold

Get the trigger threshold of the controller, the default value is GAMEPAD_TRIGGER_THRESHOLD which is equal to 30.

## Usage

```lua
local threshold = controller_object:get_trigger_threshold();
```

## Parameters

`controller_object:get_trigger_threshold` takes no parameters.

## Return Value

`controller_object:get_trigger_threshold` returns an `integer` representing the threshold for the triggers.

## Example

```lua
local controller = require "lunar360.controller";
local player1 = controller.new(0);

local threshold = player1:get_trigger_threshold();
```