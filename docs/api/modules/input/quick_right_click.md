# input.right_click

A one-shot function to simulate a right mouse click.

## Usage

```lua
input.right_click();
```

## Parameters

`input.right_click` takes no parameters.

## Return Value

`input.right_click` returns an `integer` representing the number of inputs sent to the system, which in this case should be 2 (right mouse down + right mouse up).

## Example

```lua
local input = require "lunar360.input";
input.right_click();
```