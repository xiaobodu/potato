potato
======

a light weight mobile game engine.

[![Gitter](https://badges.gitter.im/Join Chat.svg)](https://gitter.im/code4game/potato?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

----------------------------

version: in develop

[![Build Status](https://travis-ci.org/code4game/potato.svg)](https://travis-ci.org/code4game/potato)
[![Build status](https://ci.appveyor.com/api/projects/status/l563xi5j23vep2wg)](https://ci.appveyor.com/project/alexchicn/potato)
[![Coverage Status](https://coveralls.io/repos/code4game/potato/badge.png?branch=master)](https://coveralls.io/r/code4game/potato?branch=master)


----------------------------


## Overview

* [**Build**](#build)
  * [**Ready**](#ready)
  * [**Linux**](#linux)
  * [**Android**](#android)
* [**Run**](#run)
  * [**test**](#test)
  * [**editor**](#editor)
* [**Log**](#log)


Build
-----

### Ready

Please install [Git][], [CMake][], and [Qt5][].


### Linux

* Into `./build` directory.
* Run `./linux-ready.sh`. (Initialize and Update submodule)
* Run `./linux-config.sh` + `DEBUG` or `RELEASE` (Configure the project and Create Makefile by CMake)
* Run `./linux-make.sh` (Build all projects include static/shared library, third library, demo)


### Windows

coming soon


### Android (in Linux)
* Need two environment variables - ANDROID_HOME and NDK_HOME
* Run `./build/android-make-release.sh` (Build all projects include some static/shared libraries, some third libraries, and `demo`)


Run
---

#### demo

- For Linux
  * Run the `./build/linux-run-demo.sh`.


- For Windows
  coming soon


- For Android (in Linux)
  * Call `./build/android-generate-release.sh` to build all static/shared libraries and generate `.apk` file.
  * Call `adb install -r ./build/android/demo/bin/demo-release.apk` to install the demo app to your android device.
  * Copy all files/directories from `data/` to the `demo/` of the sd card in your android device.
  * At last, run the `demo` application in android system.


#### editor

- For Linux
  * Just run the `./build/linux-run-editor.sh`.
  * In the editor, open the `data/` directory by top-menu item - `Potato/Open` or Ctrl+O, then will load a demo scene.

- For Windows
  coming soon


Log & Next
---

Please see [Trello][].


License (MIT)
---

Please see the `LICENSE` file in detail.


[CMake]: http://cmake.org/ "CMake"
[Git]: http://git-scm.com/ "Git"
[Qt5]: http://qt-project.org/ "Qt5"
[code4game]: http://c4g.io/ "code 4 game"
[LOG.md]: https://github.com/code4game/potato/blob/master/LOG.md "Log"
[Trello]: https://trello.com/code4game/ "Plan"
