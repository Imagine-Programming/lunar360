# controller_object:get_right_thumb_delta

Get the right thumb delta of the controller.

## Usage

```lua
local delta = controller_object:get_right_thumb_delta();
```

## Parameters

`controller_object:get_right_thumb_delta` takes no parameters.

## Return Value

`controller_object:get_right_thumb_delta` returns a `table` in the form of [xbox_thumb_delta][1].

## Example

```lua
local controller = require "lunar360.controller";
local player1 = controller.new(0);

local delta = player1:get_right_thumb_delta();
```

[1]: /api/modules/controller/data-structures.md#xbox_thumb_delta
