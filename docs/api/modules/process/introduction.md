# lunar360.process 

The process module provides functionality to start processes and optionally wait for them to finish and obtain their exit code and output.

It can be loaded with the following code:

```lua
local process = require "lunar360.process";
```

## Starting a process and not waiting for it to finish

To start a process, `process.start_nowait` can be used. This function takes 4 arguments:

```lua
local process = require "lunar360.process";
local success, error_message = process.start_nowait("notepad.exe", "C:\\test.txt", "C:\\", process.SW_SHOW);
if (not success) then
    error("process not started: "..error_message);
end 
```

This is useful in combination with [function binding](/api/bind.md) to start a process when a button is pressed, as seen in the [introduction](/intro.md#tiny-impression):

```lua
c1:on(GAMEPAD_RIGHT_THUMB, "double-press", process.start_nowait:bind("osk.exe"));
```

## Starting a process and waiting for it to finish

To start a process and wait for it to finish, `process.start_wait` can be used. This function takes 4 arguments:

```lua
local process = require "lunar360.process";
local success, status_or_error = process.start_wait("notepad.exe", "C:\\test.txt", "C:\\", process.SW_SHOW);

if (not success) then
    error("process not started: "..status_or_error);
else 
    -- exit code: status_or_error
end
```

## Starting a process, waiting for it to finish and obtaining its output

To start a process, wait for it to finish and obtain its output, `process.start_stdout` can be used. This function takes 4 arguments:

```lua
local process = require "lunar360.process";
local success, status_or_errror, stdout = process.start_stdout("notepad.exe", "C:\\test.txt", "C:\\", process.SW_SHOW);

if (not success) then
    error("process not started: "..status_or_error);
else 
    -- exit code: status_or_error
    -- stdout: stdout
end
```