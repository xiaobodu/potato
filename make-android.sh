cd build/android/jni/
#ndk-build NDK_PROJECT_PATH=./out/android/ NDK_APPLICATION_MK=./build/android/jni/Application.mk APP_BUILD_SCRIPT=./../../build/android/jni/Android.mk $1
ndk-build $1
cd ../../../
