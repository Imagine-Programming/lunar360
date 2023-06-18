# input.key_press

A one-shot function to simulate a key press.

## Usage

```lua
input.key_press("a");
```

## Parameters

| Parameter               | Type    | Description                                                  |
| ----------------------- | ------- | ------------------------------------------------------------ |
| 1. Key Name             | string  | The key name to press. See [Key Names](/api/modules/input/input-names.md) for a list of all supported key names. |

## Return Value

`input.key_press` returns an `integer` representing the number of inputs sent to the system, which in this case should be 2 (key down + key up).

## Example

```lua
local input = require "lunar360.input";
input.key_press("a");
```