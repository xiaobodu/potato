#/usr/bin/env bash

cd $(dirname $0)

cd ../out/make/
make $1
cd ../../build/
