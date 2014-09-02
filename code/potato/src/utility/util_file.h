#pragma once

/*#if defined(BUILD_ANDROID)
#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <cassert>
#else*/
#include <fstream>
#include <sstream>
/*#endif*/

namespace ac{
namespace utility{

/*#if defined(BUILD_ANDROID)
inline std::string ReadFile(JNIEnv* pEnv, jobject pAssetMgr, const std::string& rsPathFile)
{
  AAssetManager* mgr = AAssetManager_fromJava(pEnv, pAssetMgr);
  assert(NULL != mgr);
  AAsset* asset = AAssetManager_open(mgr, rsPathFile.c_str(), AASSET_MODE_UNKNOWN);
  assert(NULL != mgr);

  std::string file_context;
  const char* c_context_ptr = static_cast<const char*>(AAsset_getBuffer(asset));
  assert(NULL != c_context_ptr);
  file_context = c_context_ptr;
  AAsset_close(asset);
  return file_context;
}
#else*/
inline std::string ReadFile(const std::string& rsPathFile)
{
  std::ifstream fstr;
  fstr.open(rsPathFile.c_str(), std::ios_base::in);
  std::stringbuf file_buffer;
  fstr >> &file_buffer;
  return file_buffer.str();
}
/*#endif*/

}
}
