# Poller

`poller` is a global object available to the script by default. The poller is a reasonably accurate loop implementation that executes your code at a fixed interval. Using [poller:set_interval][1] one can specify the frequency of the poller in Hertz. 

When [poller:loop][2] is invoked the function you provided as callback will be invoked at the specified frequency. 

## Default Frequency
By default, the standard frequency without invoking [poller:set_interval][1] is 120Hz.

## Garbage Collection
To make Lua's garbage collection a bit more consistent, the poller will collect garbage after each iteration. This is done by calling `lua_gc(L, LUA_GCCOLLECT)`. This is to prevent the garbage collector from running at unpredictable times and causing stuttering in any possible controller input handling and translation code.

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

[1]: /api/modules/poller/set_interval.md
[2]: /api/modules/poller/loop.md