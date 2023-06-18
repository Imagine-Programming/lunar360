# lunar360.controller

The controller module contains all the functionality for interacting with any of the connected controllers.

It can be loaded with the following code:

```lua
local controller = require "lunar360.controller";
```

## Instantiating a Controller

To instantiate a controller, you can use the `controller.new` function. This function takes a single argument, which is the index of the controller you want to instantiate. The indexing respects XInput's indexing, meaning that the first controller is index 0, the second is index 1, and so on.

```lua
local controller = require "lunar360.controller";
local controller_object = controller.new(0);
```

## Instantiating the First Available Controller

If you want to instantiate the first available controller, you can use the `controller.new_first_available` function. This function takes no arguments.

```lua
local controller = require "lunar360.controller";
local controller_object = controller.new_first_available();
```

This can also be done by looping through 0 to i.e. an arbitrary number like 10 and checking if the controller is connected:

```lua
local controller = require "lunar360.controller";
local controller_object;

for i = 0, 10 do
    controller_object = controller.new(i);
    if controller_object:connected() then
        break;
    end
end
```