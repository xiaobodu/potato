#include <jni.h>
#include <cassert>
#include <android/log.h>
#include <android_native_app_glue.h>

#include "potato.h"
#include "utility/util_log.h"

void android_main(struct android_app* state)
{
  ac::utility::Log::Instance().Info("android_main");

  potato_main(state);
}
