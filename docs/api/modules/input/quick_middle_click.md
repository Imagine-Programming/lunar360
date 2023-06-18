# input.middle_click

A one-shot function to simulate a middle mouse click.

## Usage

```lua
input.middle_click();
```

## Parameters

`input.middle_click` takes no parameters.

## Return Value

`input.middle_click` returns an `integer` representing the number of inputs sent to the system, which in this case should be 2 (middle mouse down + middle mouse up).

## Example

```lua
local input = require "lunar360.input";
input.middle_click();
```
