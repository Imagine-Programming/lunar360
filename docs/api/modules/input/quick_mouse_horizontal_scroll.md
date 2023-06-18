# input.mouse_horizontal_scroll

A one-shot function to simulate a horizontal mouse scroll.

## Usage

```lua
input.mouse_horizontal_scroll(WHEEL_DELTA * 5);
```

## Parameters

| Parameter               | Type    | Description                                                           |
| ----------------------- | ------- | --------------------------------------------------------------------- |
| 1. Horizontal Scroll    | integer | The amount to scroll horizontally.                                    |

## Return Value

`input.mouse_horizontal_scroll` returns an `integer` representing the number of inputs sent to the system, which in this case should be 1 (mouse horizontal scroll).

## Example

```lua
local input = require "lunar360.input";
input.mouse_horizontal_scroll(WHEEL_DELTA * 5);
```