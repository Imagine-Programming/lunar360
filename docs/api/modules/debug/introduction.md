# lunar360.debug

The `lunar360.debug` module provides a simple interface for printing debug messages to a newly allocated console which is only opened when an instance if requested.

It can be loaded with the following code:

```lua
local debug = require "lunar360.debug";
```

> *Note*: This module is purely for debugging purposes, it's not made to be efficient and should not be used in production code.

## Getting an instance

To get an instance of the debug module, `debug.get_instance` can be used. This function takes no arguments and returns a singleton instance of the debug module.

```lua
local debug = require "lunar360.debug";
local instance = debug.get_instance();
```

> *Note*: The debug module is a singleton, so calling `debug.get_instance` multiple times will always return the same instance.

## Printing a message

To print a message to the console, `obj:print` can be used. This function takes a single string argument and prints it to the console.

```lua
local debug = require "lunar360.debug";
local instance = debug.get_instance();
instance:print("Hello World!");
```