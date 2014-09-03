#include <jni.h>
#include <cassert>
#include <android/log.h>
#include <android_native_app_glue.h>

#include "potato.h"

#define TLOG_TAG    "t001"
#define TLOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, TLOG_TAG, __VA_ARGS__))
#define TLOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, TLOG_TAG, __VA_ARGS__))
#define TLOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, TLOG_TAG, __VA_ARGS__))

void android_main(struct android_app* state)
{
  TLOGI("android_main");
  potato_main(state);
}
