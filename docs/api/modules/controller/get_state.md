# controller_object:get_state

Get the current state of the controller, a translation of XINPUT_STATE.

## Usage

```lua
local state = controller_object:get_state()
```

## Parameters

`controller_object:get_state` takes no parameters.

## Return Value

`controller_object:get_state` returns a `table` in the form of [xinput_state][1].

## Example

```lua
local controller = require "lunar360.controller";
local player1 = controller.new(0);

local state = player1:get_state();
```

[1]: /api/modules/controller/data-structures.md#xinput_state