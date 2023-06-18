# controller_object:poll

Poll the controller for changes and trigger registered event handlers if necessary.

## Usage

```lua
poller:loop(function()
    controller_object:poll();
end);
```

## Parameters

`controller_object:poll` takes no parameters.

## Return Value

`controller_object:poll` returns `void`.

## Example

```lua
local controller = require "lunar360.controller";
local player1 = controller.new(0);

poller:set_interval(120);
poller:loop(function()
    player1:poll(); -- update controller state and trigger events

    if (not player1:connected()) then 
        return; -- nothing to do
    end 

    -- implement features here!
end);
```