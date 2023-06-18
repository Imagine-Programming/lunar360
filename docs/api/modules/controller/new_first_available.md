# controller.new_first_available

Instantiate a new controller object from the first available controller index.

## Usage

```lua
local controller = require "lunar360.controller";
local player1 = controller.new_first_available();
```

> *Note*: This method is not guaranteed to return the same controller every time or even a controller at all. It is recommended to use `controller.new` instead if you want to instantiate a specific controller and want certainty that it will be the same controller every time.

## Parameters

`controller.new_first_available` takes no parameters.

## Return Value

`controller.new_first_available` returns a `userdata:lunar_controller` representing the controller if one was available, `nil` otherwise.