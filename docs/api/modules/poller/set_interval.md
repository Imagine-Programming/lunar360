# poller:set_interval

Change the interval for the global poller instance in Herz.

## Usage

```lua
poller:set_interval(120);
```

> *Note*: Ensure that the interval you specify is not too high, executing your code takes time too!

## Parameters

| Parameter               | Type    | Description                                                  |
| ----------------------- | ------- | ------------------------------------------------------------ |
| 1. Interval             | integer | The desired interval, in Herz                                |

## Return Value

`poller:set_interval` returns `void`.

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