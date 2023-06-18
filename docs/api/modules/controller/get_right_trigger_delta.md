# controller_object:get_right_trigger_delta

Get the right trigger delta of the controller.

## Usage

```lua
local delta = controller_object:get_right_trigger_delta();
```

## Parameters

`controller_object:get_right_trigger_delta` takes no parameters.

## Return Value

`controller_object:get_right_trigger_delta` returns a `number` representing the delta of the right trigger.

## Example

```lua
local controller = require "lunar360.controller";
local player1 = controller.new(0);

local delta = player1:get_right_trigger_delta();
```