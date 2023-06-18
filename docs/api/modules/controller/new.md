# controller.new

Instantiate a new controller object from the given index.

## Usage

```lua
local controller = require "lunar360.controller";
local player1 = controller.new(0);
```

## Parameters

| Parameter               | Type    | Description                                                  |
| ----------------------- | ------- | ------------------------------------------------------------ |
| 1. Index                | integer | The controller index as known to the system.                 |

## Return Value

`controller.new` returns a `userdata:lunar_controller` representing the controller.