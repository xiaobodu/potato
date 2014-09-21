potato
======

A light weight 2D mobile engine. It belongs to [Code4Game][].


#### Status

Still in developing.

[![Build Status](https://travis-ci.org/code4game/potato.svg)](https://travis-ci.org/code4game/potato)


----------------------------


## Overview

* [**Build**](#build)
  * [**Ready**](#ready)
  * [**Linux**](#linux)
  * [**Android**](#android)
* [**Run**](#run)
  * [**t001**](#t001)
  * [**editor**](#editor)
* [**Log**](#log)


Build
-----

### Ready

Need [Git][], [CMake][], [Qt][] for the editor.

* Into `build` directory.
* Run `ready.sh`. (Initialize and update submodule)
* Run `config.sh` (Create Makefile by CMake)


### Linux

* Run `make.sh` (Build all projects include static/shared library, third library, test)


### Android

* Run `make-android.sh` (Build all projects include static/shared library, third library, test)


Run
---

#### t001

- For Linux
  * Just run the `out/bin/t001`.


- For Android
  * Copy all files/directories from `data/` to the `t001/` of sd card in the device.
  * Install the unsigned package - `android/t001.apk` into the device.


#### editor

- For Linux
  * Just run the `out/bin/editor`.
  * In the editor, open the `data/` directory to load the scene.


Log
---

Please see [LOG.md][].


Next
----

Please see [Trello][].


[CMake]: http://cmake.org/ "CMake"
[Git]: http://git-scm.com/ "Git"
[Qt]: http://qt-project.org/ "Qt"
[Code4Game]: http://c4g.io/ "Code 4 Game"
[LOG.md]: https://github.com/code4game/potato/blob/master/LOG.md "Log"
[Trello]: https://trello.com/code4game/ "Plan"
