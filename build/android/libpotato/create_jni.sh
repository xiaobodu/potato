#/usr/bin/env bash

javah -d jni/ -classpath $ANDROID_HOME/platforms/android-10/android.jar:./bin/classes/ io.c4g.potato.PNativeHelper
