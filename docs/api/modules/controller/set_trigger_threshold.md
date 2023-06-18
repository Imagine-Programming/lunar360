# controller_object:set_trigger_threshold

Set the trigger threshold of the controller, the default value is GAMEPAD_TRIGGER_THRESHOLD which is equal to 30.

## Usage

```lua
controller_object:set_trigger_threshold(threshold);
```

> *Note*: Each controller has a different threshold, try to find the one that works best for you.

## Parameters

| Parameter               | Type     | Description                                                  |
| ----------------------- | -------- | ------------------------------------------------------------ |
| 1. Threshold            | integer  | The threshold for the triggers                               |

## Return Value

`controller_object:set_trigger_threshold` returns `controller_object` to allow for method chaining.

## Example

```lua
local controller = require "lunar360.controller";
local player1 = controller.new(0);

player1:set_trigger_threshold(100);
```