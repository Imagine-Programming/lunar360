# Function Binding

The Lunar 360 API includes two functions that allow you to create a new bound variant of a function which will always include one or more specific parameters. This is useful for creating functions that can be used as callbacks, but with a specific parameter.

## bind

The `bind` function takes a function as `self` and one or more parameters that should be bound to it. It returns a new function that will always include the bound parameters.

```lua
local function add(a, b)
    return a + b;
end

local add_5 = add:bind(5);

print(add_5(10)); -- prints 15
```

## bind_self

The `bind_self` function is an optimized version of `bind` that only binds the `self` parameter. It takes a function as `self` and returns a new function that will always include the bound `self` parameter.

```lua
local input = require "lunar360.input";
local input_object <close> = input.new();

local mouse_left_down = input_object.mouse_left_down:bind_self(input_object);

mouse_left_down(); -- will add a mouse_left_down input to input_object, as it is bound to it.
```