#/usr/bin/env bash

cd $(dirname $0)

export PATH=$PATH:$ANDROID_HOME:$NDK_HOME

cd ./android/demo/
ant clean
./../../android-make-release.sh clean
./../../android-make-release.sh
ant release
cd ../../
