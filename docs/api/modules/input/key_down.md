# input_object:key_down

Adds a key down input to the queue in the input object.

## Usage

```lua
input_object:key_down(key);
```

## Parameters

| Parameter               | Type    | Description                                                  |
| ----------------------- | ------- | ------------------------------------------------------------ |
| 1. Key Name             | string  | The key name. See [Key Names](/api/modules/input/input-names.md) for a list of all supported key names. |

## Return Value

`input_object:key_down` returns `userdata:lunar_input` to allow for method chaining.

## Example

```lua
local input = require "lunar360.input";
local input_object <close> = input.new();

input_object:key_down("shift");
input_object:key_down("a");
input_object:key_up("a");
input_object:key_up("shift");
-- simulate a capital A
```
