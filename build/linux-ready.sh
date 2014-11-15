#/usr/bin/env bash

cd $(dirname $0)

cd ./../
git submodule init
git submodule update
cd build/
