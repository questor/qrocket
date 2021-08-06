GNU Rocket OpenGL editor (slightly improved and protocol changed!)
==================================================================

Beta Disclaimer
---------------

First a screenshot of how it looks:
![screenshot](/bin/rocketeditor_screen.png)

Regular disclaimer: Backup your stuff before using the software :)

THIS IS A MODIFIED VERSION OF THE ORIGINAL https://github.com/emoon/rocket, BUT IF YOU FIND ERRORS PLEASE DON'T REPORT IT TO EMOON!


About
-----

RocketEditor is coded by Daniel 'emoon' Collin with documentation and testing by Heine 'bstrr' Gundersen.
Daniel Collin can be contacted at daniel aat collin dot com

The SDL-based linux support is written by Konsta 'sooda' Hölttä at https://github.com/sooda/rocket, and later updated to use SDL2 by Lauri 'gustafla' Gustafsson at https://github.com/gustafla/rocket

Motivation
----------

About a year ago me and Heine 'bstrr' Gundersen (at Revision 2012) started to talk about that having an editor for GNU Rocket that worked on macOS would be great as we both used Mac as our primary development platform.
This was the start of this another version of the editor. I (Daniel 'emoon' Collin) also wanted some features that weren't in the old editor (such as folding of tracks, having it cross platform, etc)
Some small work was started on the editor during spring and summer but not much happened. It was really during last autumn 2012 I started to work on it for real to get in the features I want to have.

Features:

* Includes (or should at least :) all features from the old editor (except track re-arrangement)
* More optimized for laptop keyboards (no usage of page up/down and similar keys)
* Group support. It's now possible to group channels together that makes sense (maybe a group for each part) The syntax for this is to name the tracks "mygroup:mytrack"
* Folding support for both groups and tracks. Something I found annoying in the old editor was that you had to scroll around quite a bit to get to channel you wanted. Now with folding you use the screen space better.
* Faster navigation: Can jump between key values, jump in step of 8 and also with bookmarks.
* Other features such as using more of the keyboard for biasing of values (see key layout below)
* Trackpad support (OS X only, mouse wheel elsewhere) to scroll around (can only be used with biasing)
* Cross platform. Read more about the code in the next section.
* Navigation while play-backing. It's now possible to jump forward/backward when playing the demo (demo "scratching")
* Fast way to insert a interpolated value by just pressing return on an empty row.

Building the code
-----------------

All macOS, Windows and Linux versions use the Tundra build system (https://github.com/deplinenoise/tundra) so in order to build the code you need a tundra executable for your OS.
For macOS and Windows the binaries are included within the repo, but for Linux see the build instructions bellow.


Linux
-----

The following was tested on Ubuntu 16.10 (yakkety).

Install SDL-dev:

```
sudo apt-get install libsdl1.2-dev
```

Install [tundra](https://github.com/deplinenoise/tundra):

```
git clone --depth=1 --recursive https://github.com/deplinenoise/tundra
cd tundra
make
sudo checkinstall make install
```

Install rocket No project files are generated - Tundra builds the editor straight away.

```
git clone --depth=1 --retursive https://github.com/emoon/rocket
cd rocket
./scripts/linux-build.sh
```

Install `libbass.so` from the repo folder:

```
sudo cp external/bass/linux/libbass.so /usr/local/lib/
sudo chmod a+rx /usr/local/lib/libbass.so
sudo ldconfig
```

Start the basic example:

```
./t2-output/linux-gcc-release-default/basic_example
```

Start rocket:

```
./t2-output/linux-gcc-release-default/editor
```

Tips & tricks
-------------

* Fold away tracks or groups you are not currently working with using Alt+Left/Right and Ctrl+Alt+Left/Right

* Use Return to insert current interpolated value - also sets the interpolation type to what the previous key uses.

* A good way of bundling parameters for effects is by naming your tracks 'groupname:trackname', as this will group them together, thus making better tracknames than "logo-x-pos", "logo-y-pos", "title-x-pos", "title-y-pos". Groups can also be folded, so they don't take up screen estate when you are working on a different part of the demo.

* Insert bookmarks using the B key to easily jump between parts in the demo.

* To rename a track (or add it to a group), close the editor and open the .rocket xml file, which should be nicely formatted. Locate the track and rename it - then rename it in your demo.

* Bias using Alt+trackpad/scrollwheel. Add the Shift-key to bias even faster.

* Use selection to bias multiple keys - even across multiple tracks!

Keys
----

### Windows and Linux:

#### Editing:

Key | Action
--- | ---
0-9                 | Edit value
Esc                 | Cancel edit
QWERTY              | Bias selection +0.01, +0.1, +1, +10, +100, +1000
ASDFGH              | Bias selection -0.01, -0.1, -1, -10, -100, -1000
I                   | Toggle interpolation (step/linear/smooth/ramp)
Ctrl+I              | Invert selection
Return              | Insert current interpolated value
Shift+Arrows        | Select
Ctrl+T              | Select all keys in track
Ctrl+X              | Cut
Ctrl+C              | Copy
Ctrl+V              | Paste
Ctrl+Z              | Undo
Ctrl+Shift+Z        | Redo
Delete/Backspace    | Delete key
C                   | Move selection up
X                   | Move selection down
K                   | Offset Track +1
Ctrl+K              | Offset Track +8
L                   | Offset Track -1
Ctrl+L              | Offset Track -8
Shift+K             | Offset Group +8
Shift+L             | Offset Group -8


#### View:

Key | Action
--- | ---
Space               | Start/Stop
Ctrl+Space          | StartLoop
Arrows              | Move cursor around
Alt+Up/Down         | Jump 8 rows
Ctrl+Alt+Up/Down    | Jump to StartRow/NextBookmark - PrevBookmark/EndRow
Ctrl+Left/Right     | Jump to first/last track
Ctrl+Up/Down        | Jump to Previous/Next key in current track
Alt+Left/Right      | Fold/Unfold track
Ctrl+Alt+Left/Right | Fold/Unfold group
Trackpad scroll     | Scroll
B                   | Toggle Bookmark
Ctrl+B              | Clear all Bookmarks
Tab                 | Jump between Row, Start Row, End Row, Track editing
M                   | Mute/Unmute
Z                   | Toggle loopmark
Ctrl+Z              | Clear loopmarks

#### Files:

Key | Action
--- | ---
Ctrl+O              | Open file
Ctrl+S              | Quicksave
Ctrl+Shift+S        | Save as
Ctrl+1/2/3/4        | Quickload recent files
Ctrl+E              | Remote export
Ctrl+L              | Load Music
Ctrl+W              | Quit
