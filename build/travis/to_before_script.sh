#/usr/bin/env bash

echo ">>> before script"

if [ "$TRAVIS_TAG" ]; then
if [ "$DEPLOY_RELEASE"x = "true"x ]; then
  VALID=ok
fi
else
if [ "$RUN_COVERALLS"x = "true"x ]; then
  VALID=ok
fi
fi

if [ "$VALID"x != "ok"x ]; then
  exit
fi

if [ "$CXX" = "g++" ]; then export CXX="g++-4.8" CC="gcc-4.8"; fi
	
cppcheck code/editor code/potato code/test -I code/editor/ -I code/potato/ -I code/potato/inc -I code/potato/src -I code/potato/src/engine -I code/test/ --quiet --error-exitcode=1
git submodule init
git submodule update
cd code/external/
cd tinycc/
./configure
cd ../
cd libpng/
cmake ./
cd ../
cd ../../
mkdir -p out
mkdir -p out/bin
mkdir -p out/lib
mkdir -p out/make
cd out/make
if [ "$RUN_COVERALLS"x = "true"x ]; then
cmake -D C4G_BUILD_EDITOR=TRUE -D CMAKE_BUILD_TYPE=Release -D QT_SDK_PATH=/usr -D USE_COVERALLS=TRUE ../../build/cmake/
else
cmake -D C4G_BUILD_EDITOR=TRUE -D CMAKE_BUILD_TYPE=Release -D QT_SDK_PATH=/usr ../../build/cmake/
fi
cd ../../

echo "<<< before script"
