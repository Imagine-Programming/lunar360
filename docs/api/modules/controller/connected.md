# controller_object:connected

Check if the controller is connected after a poll.

## Usage

```lua
controller_object:connected();
```

## Parameters

`controller_object:connected` takes no parameters.

## Return Value

`controller_object:connected` returns `true` if the controller is connected, `false` otherwise.

## Example

```lua
local controller = require "lunar360.controller";
local player1 = controller.new(0);

poller:loop(function()
    player1:poll(); -- update controller state and trigger events

    if (not player1:connected()) then 
        return; -- nothing to do
    end 

    -- implement features here!
end);
```