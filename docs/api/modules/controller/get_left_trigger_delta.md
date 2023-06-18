# controller_object:get_left_trigger_delta

Get the left trigger delta of the controller.

## Usage

```lua
local delta = controller_object:get_left_trigger_delta();
```

## Parameters

`controller_object:get_left_trigger_delta` takes no parameters.

## Return Value

`controller_object:get_left_trigger_delta` returns a `number` representing the delta of the left trigger.

## Example

```lua
local controller = require "lunar360.controller";
local player1 = controller.new(0);

local delta = player1:get_left_trigger_delta();
```