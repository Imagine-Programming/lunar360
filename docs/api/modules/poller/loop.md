# poller:loop

Enter the infinite polling loop, which automatically terminates when the application exits or errors.

## Usage

```lua
poller:loop(function()
    -- polling code, i.e. player1:poll();
end);
```

> *Note*: `poller:poll` does not return, execute all your preparation code before entering the polling loop.

## Parameters

| Parameter               | Type     | Description                                                  |
| ----------------------- | -------  | ------------------------------------------------------------ |
| 1. Function             | function | The polling function that will be executed on each interval. |

## Return Value

`poller:loop` returns `void`.

## Example

```lua
local controller = require "lunar360.controller";
local player1 = controller.new(0);

poller:set_interval(60);
poller:loop(function()
    player1:poll(); -- update controller state and trigger events

    if (not player1:connected()) then 
        return; -- nothing to do
    end 

    -- implement features here!
end);
```