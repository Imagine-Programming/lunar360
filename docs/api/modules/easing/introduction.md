# lunar360.easing 

The `lunar360.easing` module contains easing functions that can be used to create smooth transitions between values.
These easing functions can be used to soften/smoothen controller input to mouse movement, as can be seen in the example in the [introduction](/intro.md#tiny-impression).

It can be loaded with the following code:

```lua
local easing = require "lunar360.easing";
```

## Easing Function Signature

All easing functions have the same signature:

```lua
local value = easing_function(factor);
```

Where `factor` is a value between 0 and 1, and `value` is the value that is returned by the easing function.

## Parameters

| Parameter               | Type    | Description                                                  |
| ----------------------- | ------- | ------------------------------------------------------------ |
| 1. Factor               | number  | The factor to use for the easing function. This value should be between 0 and 1. |

## Return Value

`easing_function` returns a `number` representing the value that is returned by the easing function, usually between 0 and 1. 

> *Note* Easing functions that 'bounce', 'overshoot' or are 'elastic' can return values outside of the 0-1 range.

## Example

```lua
local easing = require "lunar360.easing";
local value = easing.ease_in_linear(0.5);
```

## Available Easing Functions

Currently there are only ease-in functions for smoothing controller input to mouse movement.

| Function Name           | Description                                                  |
| ----------------------- | ------------------------------------------------------------ |
| ease_in_linear          | Ease in linear.                                              |
| ease_in_sine            | Ease in sine.                                                |
| ease_in_quadratic       | Ease in quadratic.                                           |
| ease_in_cubic           | Ease in cubic.                                               |
| ease_in_quartic         | Ease in quartic.                                             |
| ease_in_quintic         | Ease in quintic.                                             |
| ease_in_exponential     | Ease in exponential.                                         |
| ease_in_circular        | Ease in circular.                                            |
