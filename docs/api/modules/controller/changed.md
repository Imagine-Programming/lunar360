# controller_object:changed

Check if the controller state has changed after a poll.

## Usage

```lua
controller_object:changed();
```

## Parameters

`controller_object:changed` takes no parameters.

## Return Value

`controller_object:changed` returns `true` if the controller state has changed, `false` otherwise.

## Example

```lua
local controller = require "lunar360.controller";
local player1 = controller.new(0);

poller:loop(function()
    player1:poll(); -- update controller state and trigger events

    if (not player1:connected()) then 
        return; -- nothing to do
    end 

    if (player1:changed()) then 
        -- only implement features if the controller state has changed, i.e. thumbstick was moved, button was pressed, etc.
    end 
end);
```