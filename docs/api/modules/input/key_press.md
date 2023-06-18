# input_object:key_press

Adds a key down and key up input to the queue in the input object.

## Usage

```lua
input_object:key_press(key);
```

## Parameters

| Parameter               | Type    | Description                                                  |
| ----------------------- | ------- | ------------------------------------------------------------ |
| 1. Key Name             | string  | The key name. See [Key Names](/api/modules/input/input-names.md) for a list of all supported key names. |

## Return Value

`input_object:key_press` returns `userdata:lunar_input` to allow for method chaining.

## Example

```lua
local input = require "lunar360.input";
local input_object <close> = input.new();

input_object:key_press("a");
-- simulate a lowercase a
```