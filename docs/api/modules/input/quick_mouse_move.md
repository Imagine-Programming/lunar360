# input.mouse_move

A one-shot function to simulate a mouse move.

## Usage

```lua
input.mouse_move(100, 100);
```

## Parameters

| Parameter               | Type    | Description                                                           |
| ----------------------- | ------- | --------------------------------------------------------------------- |
| 1. X                    | integer | The X coordinate to move the mouse to.                                |
| 2. Y                    | integer | The Y coordinate to move the mouse to.                                |
| 3. Absolute             | boolean | Whether the coordinates are absolute or relative, `false` by default. |

## Return Value

`input.mouse_move` returns an `integer` representing the number of inputs sent to the system, which in this case should be 1 (mouse move).

## Example

```lua
local input = require "lunar360.input";
input.mouse_move(100, 100);
```
