# controller_object:get_capabilities

Get the capabilities of the controller, a translation of XINPUT_CAPABILITIES.

## Usage

```lua
local caps = controller_object:get_capabilities()
```

## Parameters

`controller_object:get_capabilities` takes no parameters.

## Return Value

`controller_object:get_capabilities` returns a `table` in the form of [xinput_capabilities][1].

## Example

```lua
local controller = require "lunar360.controller";
local player1 = controller.new(0);

local caps = player1:get_capabilities();
-- do something with caps
```

[1]: /api/modules/controller/data-structures.md#xinput_capabilities