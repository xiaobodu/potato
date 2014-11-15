#/usr/bin/env bash

cd $(dirname $0)

export PATH=$PATH:$ANDROID_HOME:$NDK_HOME

./android-make-release.sh
cd ./android/test/
ant release
cd ../../
