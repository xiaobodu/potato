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

Need [Git][], [CMake][], and [Qt][].

* Into `build` directory.
* Run `ready.sh`. (Initialize and update submodule)
* Run `config.sh` (Create Makefile by CMake)


### Linux

* Run `make.sh` (Build all projects include static/shared library, third library, test)


### Android

* Run `make-android-release.sh` (Build all projects include static/shared library, third library, test)


Run
---

#### test

- For Linux
  * Just run the `./build/run_test.sh`.


- For Android
  * Copy all files/directories from `data/` to the `test/` of sd card in the device.
  * Import the android/libpotato and android/test to eclipse.


#### editor

- For Linux
  * Just run the `./build/run_editor.sh`.
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
