RivaCross - Customizable Crosshair Overlay
==========================================

Adds a customizable crosshair to MSI Afterburner /
RivaTuner Statistics Server

RivaCross makes use of a feature in RivaTuner Statistics Server (RTSS)
that enables the addition of custom text to the RTSS on screen display (OSD).<br>
It includes a simple text terminal user interface for crosshair customization.

Examples
--------
These examples show different crosshair designs made with RivaCross.<br>
Levels of usability may vary.

[RivaCross in Games #1](docs/images/example00_clear_sky.jpg)

[RivaCross in Games #2](docs/images/example01_mankind_divided.jpg)

[RivaCross in Games #3](docs/images/example02_acc.jpg)

Releases
--------

The current binary package of RivaCross is available in the 
[Releases section](https://github.com/irseny/RivaCross/releases)
([Direct download](https://github.com/irseny/RivaCross/releases/download/v0.5.2/RivaCross.Windows.64bit.zip)

Usage
-----

1. Open MSI Afterburner / RivaTuner Statistics Server
1. Execute RivaCross.exe
1. For crosshair customization follow the instructions on screen

For bug reports or feature suggestions please use the 
[Issues section](https://github.com/irseny/RivaCross/issues).

Manual Build
------------

If not done already initialize and update the PDCurses dependency:
1. `git submodule update --init`

Do a static build of the PDCurses library from a developer console:
1. Navigate to `external/pdcurses/wincon`
1. `nmake -f Makefile.vc WIDE=Y UTF8=Y`
1. From there copy `pdcurses.lib` to the `lib` folder at the root of the repository

Build RivaCross from a developer console:
1. Navigate to the root of the repository
1. `nmake`
1. A successful build yields the console application `RivaCross.exe`

Limitations
-----------
* The crosshair is limited to one line of text
  - any further work in this direction is unlikely
* The application does not necessarily understand all keys
  - probably a limitation of the technology and not easily fixable
* The crosshair can only be moved when the configuration window is in focus
  - enter the movement mode with M, then the crosshair can be moved while another windows is in focus
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
  - a saving feature could be implemented if requested

Credits
-------

The initial plan to create this tool has been elevated by the existing
[RTSS_Crosshair](https://github.com/RecursiveLife/RTSS_Crosshair) project.<br>
Parts of the codebase by
[Slava (RecursiveLife)](https://github.com/RecursiveLife)
have been used as a starting point for RivaCross.

Special thanks to
[Guru3D](https://www.guru3d.com)
for [RivaTuner Statistics Server](https://www.guru3d.com/content-page/rivatuner.html)
and the RTSS SDK.

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

