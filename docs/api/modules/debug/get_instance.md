# debug.get_instance

The `debug.get_instance` function returns a singleton instance of the debug module.

## Usage

```lua
local debug = require "lunar360.debug";
local instance = debug.get_instance();
```

## Arguments 

`debug.get_instance` takes no parameters.

## Return value

`debug.get_instance` returns a `userdata:lunar_debug` representing the writer.

## Example

```lua
local debug = require "lunar360.debug";
local instance = debug.get_instance();
instance:print("Hello World!");
```