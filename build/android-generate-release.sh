#/usr/bin/env bash

cd $(dirname $0)

./android-make-release.sh
cd ./android/test/
ant release
cd ../../
