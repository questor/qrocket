Rocket
======

[![Build status](https://ci.appveyor.com/api/projects/status/dfq8qaedc6mtsefg/branch/master?svg=true)](https://ci.appveyor.com/project/kusma/rocket/branch/master)
[![Build status](https://travis-ci.org/rocket/rocket.svg?branch=master)](https://travis-ci.org/rocket/rocket)
[![Gitter](https://badges.gitter.im/rocket.svg)](https://gitter.im/rocket?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge)
[![License: Zlib](https://img.shields.io/badge/License-Zlib-blue.svg)](https://opensource.org/licenses/Zlib)

Rocket is an intuitive new way of... bah, whatever. It's a sync-tracker, a
tool for synchronizing music and visuals in demoscene productions. It
consists of a GUI editor (using Qt), and an ANSI C library that can either
communicate with the editor over a network socket, or play back an exported
data-set.

Compile Editor
--------------
The Rocket editor uses qmake as a build-system abstraction, which can be
used to output Makefiles, Visual Studio project files or can be built
directly from QtCreator. See the qmake documentation for details.

Compile Example
---------------
Rocket contains an example client called example\_bass. This is a simple
OpenGL, SDL 1.2 and BASS audio library application, that demonstrates how to
use the Rocket API.

Before compiling the example, you need to make sure you have recent
[SDL](http://www.libsdl.org/) and [BASS](http://www.un4seen.com/) libraries
and includes.

If you're using VS2013 or above, this should happen automatically, as
these libraries are consumed through NuGet.

The header files and libraries can be installed local to the project by
copying all .lib-files to the example\_bass/lib/, all .h files to
example\_bass/include/, and all .dll files to the example\_bass/.

Once the prerequisites are installed, the example can be compiled either by
opening examples.sln and selecting "Build" -> "Build Solution" from Visual
Studio 2008 or 2013, or by doing `make examples/example_bass` on Unix-based
systems.

JavaScript
----------
Thanks to the excellent work of [mog](http://github.com/mog), there's now
JavaScript support. Have a look at [js/README.md](js/README.md) for more
information.

Using the editor
----------------
The Rocket editor is laid out like a music-tracker; tracks (or columns) and
rows. Each track represents a separate "variable" in the demo, over the entire
time-domain of the demo. Each row represents a specific point in time, and
consists of a set of key frames. The key frames are interpolated over time
according to their interpolation modes.

Interpolation modes
-------------------
Each key frame has an interpolation mode associated with it, and that
interpolation mode is valid until the next key frame is reached. The different
interpolation modes are the following:

* Step   : This is the simplest mode, and always returns the key's value.
* Linear : This does a linear interpolation between the current and the next
           key's values.
* Smooth : This interpolates in a smooth fashion, the exact function is what
           is usually called "smoothstep". Do not confuse this mode with
           splines; this only interpolates smoothly between two different
           values, it does not try to calculate tangents or any such things.
* Ramp   : This is similar to "Linear", but additionally applies an
           exponentiation of the interpolation factor.

Keyboard shortcuts
-------------------
Some of the Rocket editor's features are available through the menu and some
keyboard shortcut. Here's a list of the supported keyboard shortcuts:

| Shortcut                 | Action                       |
|:-------------------------|:-----------------------------|
| Up/Down/Left/Right       | Move cursor                  |
| PgUp/PgDn                | Move cursor 16 rows up/down  |
| Home/End                 | Move cursor to begining/end  |
| Ctrl+Left/Right          | Move track                   |
| Enter                    | Enter key frame value        |
| Del                      | Delete key frame             |
| i                        | Enumerate interpolation mode |
| k                        | Toggle bookmark              |
| Alt+PgUp/PgDn            | Go to prev/next bookmark     |
| Space                    | Pause/Resume demo            |
| Shift+Up/Down/Left/Right | Select                       |
| Ctrl+C                   | Copy                         |
| Ctrl+V                   | Paste                        |
| Ctrl+Z                   | Undo                         |
| Shift+Ctrl+Z             | Redo                         |
| Ctrl+B                   | Bias key frames              |
| Shift+Ctrl+Up/Down       | Quick-bias by +/- 0.1        |
| Ctrl+Up/Down             | Quick-bias by +/- 1          |
| Ctrl+PgUp/PgDn           | Quick-bias by +/- 10         |
| Shift+Ctrl+PgUp/PgDn     | Quick-bias by +/- 100        |

Alternatives and ports
----------------------
* [PBRocket](https://github.com/dartcode/pbrocket), a PureBasic port of the
  Rocket editor, client and player.
* [RocketEditor](https://github.com/emoon/rocket/tree/master/ogl_editor), an
  alternative editor written in pure C using OpenGL for the GUI.
* [GroundControl](https://github.com/edoreshef/ground-control), an alternative
  editor written in C# using WPF for the GUI.
* [RocketNet](https://github.com/kebby/RocketNet), a pure .NET implementation
  of the client and player.
* [Moonlander](https://github.com/anttihirvonen/moonlander), a Java
  implementation of the client and player, for integration with
  [Processing](https://processing.org/).

Bugs and feedback
-----------------
Please report bugs or other feedback to the Rocket mailing list:
<gnu-rocket@googlegroups.com>
