potato
======

A light 2D mobile engine. It belongs to [Code4Game][].


#### Status

Still in developing.


## Overview

* [**Build**](#build)
  * [**Ready**](#ready)
  * [**Linux**](#linux)
  * [**Android**](#android)
* [**Log**](#log)


Build
-----

### Ready

Need [CMake][], [Git][].

* Into `build` directory.
* Run `ready.sh`. (Initialize and update submodule)
* Run `config.sh` (Create Makefile by CMake)


### Linux

* Run `make.sh` (Build all projects include static/shared library, third library, test)


### Android

* Run `make-android.sh` (Build all projects include static/shared library, third library, test)


Log
---

- 2014-09-16:
  -  improve the flash module
  - configure the file to test the flash module



[CMake]: http://cmake.org/ "CMake"
[Git]: http://www.git-scm.com/ "Git"
[Code4Game]: http://c4g.io/ "Code 4 Game"