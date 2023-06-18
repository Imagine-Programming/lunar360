# Modules

Lunar 360 is built up using Lua modules. Most of these modules are built-in and preloaded, so requiring them will expose the preloaded module to the Lua environment. This can be as simple as; 

```lua
local controller = require "lunar360.controller";
local p1 = controller.new(0);
```

Check out all the modules listed as subchapters of this Modules chapter.