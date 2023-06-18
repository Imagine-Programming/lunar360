# controller_object:on 

Register an event handler for a supported controller event on a specific button.

## Usage

```lua
controller_object:on(button, event, handler);
```

## Parameters

| Parameter               | Type     | Description                                                  |
| ----------------------- | -------- | ------------------------------------------------------------ |
| 1. Button ID            | integer  | The [button ID][1] to register the event handler for.        |
| 2. Event                | string   | The event to register the event handler for.                 |
| 3. Event Handler        | function | The event handler to register.                               |

## Available Events
| Event        | Description                                                                   |
| ------------ | ----------------------------------------------------------------------------- |
| down-press   | Fires when the button is pressed down.                                        |
| up-press     | Fires when the button is released.                                            |
| single-press | Fires when the button is pressed down and released.                           |
| double-press | Fires when the button is pressed down and released twice in quick succession. |

## Return Value

`controller_object:on` returns `controller_object` to allow for method chaining.

## Example

```lua
local controller = require "lunar360.controller";
local player1 = controller.new(0);

player1:on(GAMEPAD_A, "down-press", function()
    print("A button pressed!");
end);
```

[1]: /api/modules/controller/constants.md