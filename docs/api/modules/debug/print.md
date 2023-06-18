# debug_writer_object:print

The `debug_writer_object:print` function prints a message to the console. Parameters are separated by a tab `\t` character.

## Usage

```lua
debug_writer_object:print(value1, value2, value3, value4, value5, ...);
```

## Parameters

`debug_writer_object:print` has a variadic number of parameters, the table below shows that the first is required and the rest are optional. Up to 5 entries are shown in the table, but there is not a limit to the number of parameters.

| Parameter               | Type               | Description                    |
| ----------------------- | ------------------ | ------------------------------ |
| 1. Value 1              | any printable type | Any printable value            |
| 2. Value 2              | any printable type | (optional) Any printable value |
| 3. Value 3              | any printable type | (optional) Any printable value |
| 4. Value 4              | any printable type | (optional) Any printable value |
| 5. Value 5              | any printable type | (optional) Any printable value |
| ...                     | ...                | ...                            |

## Return value

`debug_writer_object:print` does not return any values.

## Example

```lua
local debug = require "lunar360.debug";
local instance = debug.get_instance();

instance:print("Hello World!", 3.14, true, nil, "foo", {});
-- prints: Hello World!	3.14	true	nil	foo	table: 0x0000000000000000
```