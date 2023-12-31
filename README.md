<p align="center"><img src="./icon/icon-face.svg" width="256" alt="Lunar 360 Logo displaying a controller with a face" /></p>

# Lunar 360

[![MSBuild](https://github.com/Imagine-Programming/lunar360/actions/workflows/msbuild.yml/badge.svg?branch=main)](https://github.com/Imagine-Programming/lunar360/actions/workflows/msbuild.yml)

Lunar 360 is a simple binding between XInput and Lua 5.4 with a polling process putting it together. It allows you to decide how you would like to use your XBox controller outside of games, for example as an HID. The included example script (`src/lunar360.lua`) translates inputs from the controller to mouse and keyboard inputs to the system.

## Alternatives
Lunar 360 is heavily inspired by [Gopher360][2], if you would like a similar tool that does not require you to write scripts then [Gopher360][2] might be a much better option for you. Lunar 360 includes a script that you can customize, but it does require a little scripting experience.

## Installation

Download a release version, extract the files and start lunar360.exe. 

## Support 

If you require a bit of support, you can open an issue here and ask a question. You can also send me a message on [Twitter @BGroothedde][3].

## Usage

Check out the [getting started][5] topic from the documentation.

For information about how to customize the behavior of lunar360, check out the [extensive documentation][4] on all the currently included features. It's all Lua, so the possibilities are limitless. 

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

Please make sure to update any existing tests as appropriate.

## License

[MIT][1]

[1]: https://choosealicense.com/licenses/mit/
[2]: https://github.com/Tylemagne/Gopher360
[3]: https://twitter.com/BGroothedde
[4]: https://imagine-programming.github.io/lunar360
[5]: https://imagine-programming.github.io/lunar360/#/getting-started