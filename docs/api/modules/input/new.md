# input.new 

Instantiate a new input object.

## Usage

```lua
local input = require "lunar360.input";
local input_object = input.new();
```

> *Note*: When you mark the input object with the `<close>` attribute, the input object will be sent to the system when the object is leaving the scope (closed). See [Use the Lua 5.4 to-be-closed feature](/api/modules/input/introduction.md#use-the-lua-54-to-be-closed-feature) for more information.

## Parameters

`input.new` takes no parameters.

## Return Value

`input.new` returns a `userdata:lunar_input` representing the input object.

## Example

```lua
local input = require "lunar360.input";
local input_object = input.new();

input_object:mouse_left_down();
input_object:mouse_left_up();
-- simulate a mouse click

input_object:send();
```