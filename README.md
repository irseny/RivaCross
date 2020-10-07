RivaCross - Customizable Crosshair Overlay
==========================================

Adds a customizable crosshair to MSI Afterburner /
RivaTuner Statistics Server overlays

RivaCross makes use of a feature in RivaTuner Statistics Server (RTSS)
that allows for adding custom text to RTSS overlays.<br>
It includes a simple, text-based user interface for crosshair customization.

Examples
--------
These examples show different crosshair styling made with RivaCross.<br>
Levels of usability may vary.

[RivaCross in Games #1](docs/images/example00_clear_sky.png)

[RivaCross in Games #2](docs/images/example01_mankind_divided.png)

Releases
--------

Release of the first binary package is pending with high priority

Usage
-----

1. Open MSI Afterburner / RivaTuner Statistics Server
1. Execute RivaCross.exe
1. For customization follow the instructions on screen


Manual Build
------------

If not done already initialize and update the PDCurses dependency:
1. `git submodule update --init`

Do a static build of the PDCurses library:
1. Open a developer console
1. Navigate to `external/pdcurses/wincon`
1. `nmake -f Makefile.vc WIDE=Y UTF8=Y`
1. From there copy `pdcurses.lib` to the `lib` folder at the root of the repository

Build RivaCross.exe:
1. Open a developer console
1. Navigate to the root of the repository
1. `nmake`

Limitations
-----------
* The crosshair is limited to one line of text
  - might be overcome with a more advanced configuration interface in the future
* The application does not necessarily understand all keys
  - certain keys could get fixed in the future
* The crosshair can only be moved when the configuration window is in focus
  - there are plans to maybe implement a testing area to work around this issue
* Availability of colorization and scaling features depend on RTSS rendering mode
  - try out a different rendering mode (Vector2D, Vector3D, Raster)
* The crosshair positioning is not very fine grained
  - this seems to be a limitation of RTSS
* The crosshair cannot be positioned to the left of the MSI Afterburner overlay
  - no workaround so far (negative position values are not interpreted as such by RTSS)
* Running the application multiple times does not yield multiple independent crosshairs
  - this behaviour exists for simplicity reasons and is required for the "hard exit" feature
* Configuration presets must be created and modified manually in the `config` folder
  - see [`config/HELPME.md`](config/HELPME.md) for formatting information

Credits
-------

The initial plan to create this tool has been elevated by the existing
[RTSS_Crosshair](https://github.com/RecursiveLife/RTSS_Crosshair) project.<br>
Parts of the codebase by
[Slava (RecursiveLife)](https://github.com/RecursiveLife)
have been used as a starting point for RivaCross.

Special thanks to
[Guru3D](https://www.guru3d.com)
for RivaTuner Statistics Server and the RTSS SDK.

License
-------

MIT License

Copyright (c) 2020 Irseny

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

