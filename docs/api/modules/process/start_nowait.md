# process.start_nowait

Starts a process and does not wait for it to finish.

## Usage

```lua
local process = require "lunar360.process";
local success, error_message = process.start_nowait(program, arguments, working_directory, show_state);
```

## Parameters

| Parameter            | Type     | Description                                                   |
| -------------------- | -------  | ------------------------------------------------------------- |
| 1. Program           | string   | The program to start                                          |
| 2. Arguments         | string   | (optional) The arguments to pass to the program               |
| 3. Working Directory | string   | (optional) The working directory to use                       |
| 4. Show State        | integer  | (optional) The [show state][1] to use                         |

## Return Values

`process.start_nowait` can return multiple values:

| Return Value         | Type     | Condition     | Description                                                      |
| -------------------- | -------  | ------------- | ---------------------------------------------------------------- |
| 1. Success           | boolean  | n/a           | True if the process was started successfully                     |
| 2. Error Message     | string   | `not Success` | (optional) The error message if the process could not be started |

## Example

```lua
local process = require "lunar360.process";
local success, error_message = process.start_nowait("notepad.exe", "C:\\test.txt", "C:\\", process.SW_SHOW);
if (not success) then
    error("process not started: "..error_message);
end 
```

[1]: /api/modules/process/constants.md