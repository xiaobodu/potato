potato
======

a light weight mobile game engine. It belongs to [Code4Game][].

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

Please install [Git][], [CMake][], and [Qt][].


### Linux

* Into `build` directory.
* Run `linux-ready.sh`. (Initialize and update submodule)
* Run `linux-config.sh` (Create Makefile by CMake)
* Run `linux-make.sh` (Build all projects include static/shared library, third library, test)


### Android (in Linux)
* Need two environment variables - ANDROID_HOME and NDK_HOME
* Run `android-make-release.sh` (Build all projects include some static/shared libraries, some third libraries, and `test`)


Run
---

#### test

- For Linux
  * Run the `./build/linux-run-test.sh`.


- For Android
  * Call `./build/android-generate-release.sh` to build all static/shared libraries and generate `.apk` file.
  * Call `adb install -r ./build/android/test/bin/test-release.apk` to install the test app to your android device.
  * Copy all files/directories from `data/` to the `test/` of sd card in your android device.
  * At last, run the `test` in android system.


#### editor

- For Linux
  * Just run the `./build/linux-run-editor.sh`.
  * In the editor, open the `data/` directory by top-menu item - `Potato/Open` or Ctrl+O, then will load a test scene.


Log & Next
---

Please see [Trello][].


[CMake]: http://cmake.org/ "CMake"
[Git]: http://git-scm.com/ "Git"
[Qt]: http://qt-project.org/ "Qt"
[Code4Game]: http://c4g.io/ "Code 4 Game"
[LOG.md]: https://github.com/code4game/potato/blob/master/LOG.md "Log"
[Trello]: https://trello.com/code4game/ "Plan"
