# input.left_click

A one-shot function to simulate a left mouse click.

## Usage

```lua
input.left_click();
```

## Parameters

`input.left_click` takes no parameters.

## Return Value

`input.left_click` returns an `integer` representing the number of inputs sent to the system, which in this case should be 2 (left mouse down + left mouse up).

## Example

```lua
local input = require "lunar360.input";
input.left_click();
```
