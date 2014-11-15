#/usr/bin/env bash

cd $(dirname $0)

export PATH=$PATH:$ANDROID_HOME:$NDK_HOME

cd android/libpotato/jni/
#ndk-build NDK_PROJECT_PATH=./out/android/ NDK_APPLICATION_MK=./build/android/jni/Application.mk APP_BUILD_SCRIPT=./../../build/android/jni/Android.mk $1
ndk-build NDK_DEBUG=1 NDK_MODULE_PATH=`pwd` $1
cd ../../test/jni/
ndk-build NDK_MODULE_PATH=`pwd` $1
cd ../../
