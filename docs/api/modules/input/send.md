# input_object:send

Sends all the queued inputs from this instance to the system and clears the queue.

## Usage

```lua
input_object:send();
```

> *Note*: When you mark the input object with the `<close>` attribute, the input object will be sent to the system when the object is leaving the scope (closed). See [Use the Lua 5.4 to-be-closed feature](/api/modules/input/introduction.md#use-the-lua-54-to-be-closed-feature) for more information. In that case, you don't need to call `input_object:send()`.

## Parameters

`input_object:send` takes no parameters.

## Return Value

`input_object:send` returns an `integer` representing the number of inputs sent to the system.

## Example

```lua
local input = require "lunar360.input";
local input_object = input.new();

input_object:mouse_left_down();
input_object:mouse_left_up();
-- simulate a mouse click

input_object:send();
```