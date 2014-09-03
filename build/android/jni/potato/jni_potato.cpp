#include <jni.h>
#include <android/log.h>
#include <cassert>

#include "me_alexchi_potato_Potato.h"
#include "me_alexchi_potato_Potato_Render.h"

#include "potato.h"

#define LOG_TAG    "jni_potato"
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__))


void GetConfig(std::string& rsPath, std::string& rsFile)
{
  rsPath = "";
  rsFile = "data/config.json";
}


JNIEXPORT void JNICALL Java_me_alexchi_potato_Potato_create
  (JNIEnv * pEnv, jobject pObj, jstring sLibrPath, jstring sDataPath, jstring sFile)
{
  LOGI("call Java_me_alexchi_potato_Potato_create");

  const char* c_libr_path = pEnv->GetStringUTFChars(sLibrPath, NULL);
  std::string libr_path = c_libr_path;
  pEnv->ReleaseStringUTFChars(sLibrPath, c_libr_path);

  const char* c_data_path = pEnv->GetStringUTFChars(sDataPath, NULL);
  std::string data_path = c_data_path;
  pEnv->ReleaseStringUTFChars(sDataPath, c_data_path);

  const char* c_file = pEnv->GetStringUTFChars(sFile, NULL);
  std::string file = c_file;
  pEnv->ReleaseStringUTFChars(sFile, c_file);

  ac::Potato::Instance().Initialize(libr_path, data_path, file);
}

JNIEXPORT void JNICALL Java_me_alexchi_potato_Potato_destroy
  (JNIEnv *, jobject)
{
  //
}

JNIEXPORT void JNICALL Java_me_alexchi_potato_Potato_00024Render_start
 (JNIEnv *, jobject)
{
  ac::core::IEngine*& engine_ptr = ac::Potato::Instance().GetEngine();
  assert(NULL != engine_ptr);
  engine_ptr->Run();
}

JNIEXPORT void JNICALL Java_me_alexchi_potato_Potato_00024Render_resize
  (JNIEnv *, jobject, jint, jint)
{
  //
}

JNIEXPORT void JNICALL Java_me_alexchi_potato_Potato_00024Render_stop
  (JNIEnv *, jobject)
{
  //
}
