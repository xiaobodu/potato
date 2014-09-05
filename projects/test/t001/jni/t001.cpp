#include <jni.h>
#include <cassert>
#include <android/log.h>
#include <android_native_app_glue.h>

#include "potato.h"
#include "utility/util_log.h"

#define NATIVE_CLASS_NAME "android/app/NativeActivity"
//#define HELPER_CLASS_NAME "me/alexchi/potato/PNativeHelper"

//#define NATIVE_CLASS_NAME "me/alexchi/potato/test/t001/MainActivity"
#define HELPER_CLASS_NAME "me/alexchi/potato/test/t001/NativeHelper"

void android_main(struct android_app* state)
{
  ac::utility::Log::Instance().Info("android_main");

  potato_main(state, NATIVE_CLASS_NAME, HELPER_CLASS_NAME);
}
