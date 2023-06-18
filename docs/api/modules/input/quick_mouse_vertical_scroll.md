# input.mouse_vertical_scroll

A one-shot function to simulate a vertical mouse scroll.

## Usage

```lua
input.mouse_vertical_scroll(WHEEL_DELTA * 5);
```

## Parameters

| Parameter               | Type    | Description                                                           |
| ----------------------- | ------- | --------------------------------------------------------------------- |
| 1. Vertical Scroll      | integer | The amount to scroll vertically.                                      |

## Return Value

`input.mouse_vertical_scroll` returns an `integer` representing the number of inputs sent to the system, which in this case should be 1 (mouse vertical scroll).

## Example

```lua
local input = require "lunar360.input";
input.mouse_vertical_scroll(WHEEL_DELTA * 5);
```