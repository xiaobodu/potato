#/usr/bin/env bash

cd $(dirname $0)

cd ../code/external/tinycc
./configure
cd ../../../build

cd ../code/external/libpng
cmake ./
cd ../../../build

mkdir -p ../out
mkdir -p ../out/bin
mkdir -p ../out/lib
mkdir -p ../out/make

cd ../out/make/
cmake -D CMAKE_BUILD_TYPE=$1 -D QT_SDK_PATH=/usr -D USE_COVERALLS=FALSE -D C4G_BUILD_EDITOR=TRUE ../../build/cmake/
cd ../../build/
