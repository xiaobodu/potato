#include <jni.h>
#include <cassert>
#include <pthread.h>
#include <android/log.h>
#include <android_native_app_glue.h>

#include "potato.h"
#include "utility/log.h"
#include "utility/sharedlibrary.h"

#include <EGL/egl.h>
#include <GLES/gl.h>

#define PLOG_TAG             "potato"
#define PLOGI(...)           ((void)__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__))

namespace scope {

class ThreadMutex
{
public:
  explicit ThreadMutex(pthread_mutex_t* pMutex, ANativeActivity*& rpActivity)
    : m_pMutex(pMutex), m_pActivity(rpActivity), m_pEnv(NULL)
  {
    assert(NULL != pMutex);
    assert(NULL != rpActivity);
    assert(NULL != rpActivity->vm);
    pthread_mutex_lock(m_pMutex);
    m_pActivity->vm->AttachCurrentThread(&m_pEnv, NULL);
    assert(NULL != m_pEnv);
  }

  ~ThreadMutex()
  {
    m_pActivity->vm->DetachCurrentThread();
    pthread_mutex_unlock(m_pMutex);
  }

public:
  JNIEnv*& GetEnv() { return m_pEnv; }

private:
  pthread_mutex_t* m_pMutex;
  ANativeActivity* m_pActivity;
  JNIEnv* m_pEnv;
};

}

class NativeHelper
{
public:
  static NativeHelper& Instance();

protected:
  NativeHelper();
  virtual ~NativeHelper();

public:
  void Initialize(struct android_app*& rpApp, const std::string& rsNativeClassName, const std::string& rsHelperClassName);

public:
  virtual std::string GetLibraryPath();
  virtual std::string GetExternalPath();
  virtual void HasReady();

protected:
  jclass RetrieveClass(JNIEnv*& rpEnv, const std::string& rsNativeClassName, const std::string& rsHelperClassName);

private:
  mutable pthread_mutex_t m_Mutex;
  ANativeActivity* m_pActivity;
  std::string m_sAppName;
  jobject m_JNIObject;
  jclass m_JNIClass;
};

NativeHelper& NativeHelper::Instance()
{
  static NativeHelper s_Instance;
  return s_Instance;
}

NativeHelper::NativeHelper()
  : m_pActivity(NULL)
  , m_JNIObject(NULL)
  , m_JNIClass(NULL)
{
  ;
}

NativeHelper::~NativeHelper()
{
  pthread_mutex_lock(&m_Mutex);

  JNIEnv* env = NULL;
  m_pActivity->vm->AttachCurrentThread( &env, NULL );

  if (NULL != m_JNIObject) env->DeleteGlobalRef(m_JNIObject);
  if (NULL != m_JNIClass) env->DeleteGlobalRef(m_JNIClass);

  pthread_mutex_destroy(&m_Mutex);
}

void NativeHelper::Initialize(struct android_app*& rpApp, const std::string& rsNativeClassName, const std::string& rsHelperClassName)
{
  pthread_mutex_init(&m_Mutex, NULL);
  assert(NULL != rpApp);
  m_pActivity = rpApp->activity;

  scope::ThreadMutex jni_env = scope::ThreadMutex(&m_Mutex, m_pActivity);
  JNIEnv*& env = jni_env.GetEnv();

  //Retrieve app name
  jclass android_content_Context = env->GetObjectClass(m_pActivity->clazz);
  jmethodID midGetPackageName = env->GetMethodID(android_content_Context, "getPackageName", "()Ljava/lang/String;");

  jstring packageName = (jstring) env->CallObjectMethod(m_pActivity->clazz, midGetPackageName);
  const char* appname = env->GetStringUTFChars(packageName, NULL);
  m_sAppName = std::string(appname);

  jclass cls = RetrieveClass(env, rsNativeClassName, rsHelperClassName);
  m_JNIClass = (jclass) env->NewGlobalRef(cls);

  jmethodID constructor = env->GetMethodID(m_JNIClass, "<init>", "()V");
  m_JNIObject = env->NewObject(m_JNIClass, constructor);
  m_JNIObject = env->NewGlobalRef(m_JNIObject);

  env->ReleaseStringUTFChars(packageName, appname);
}

std::string NativeHelper::GetLibraryPath()
{
  scope::ThreadMutex jni_env = scope::ThreadMutex(&m_Mutex, m_pActivity);
  JNIEnv*& env = jni_env.GetEnv();

  assert(m_bIsReady);
  jmethodID method_id = env->GetMethodID(m_JNIClass, "GetLibraryPath", "()Ljava/lang/String;");
  assert(NULL != method_id);
  jstring res = (jstring)env->CallObjectMethod(m_JNIObject, method_id);
  const char* c_res = env->GetStringUTFChars(res, NULL);
  assert(NULL != c_res);
  std::string res_str = std::string(c_res);
  env->ReleaseStringUTFChars(res, c_res);
  return res_str;
}

std::string NativeHelper::GetExternalPath()
{
  scope::ThreadMutex jni_env = scope::ThreadMutex(&m_Mutex, m_pActivity);
  JNIEnv*& env = jni_env.GetEnv();

  assert(m_bIsReady);
  jmethodID method_id = env->GetMethodID(m_JNIClass, "GetExternalPath", "()Ljava/lang/String;");
  assert(NULL != method_id);
  jstring res = (jstring)env->CallObjectMethod(m_JNIObject, method_id);
  const char* c_res = env->GetStringUTFChars(res, NULL);
  assert(NULL != c_res);
  std::string res_str = std::string(c_res);
  env->ReleaseStringUTFChars(res, c_res);
  return res_str;
}

void NativeHelper::HasReady()
{
  scope::ThreadMutex jni_env = scope::ThreadMutex(&m_Mutex, m_pActivity);
  JNIEnv*& env = jni_env.GetEnv();

  assert(m_bIsReady);
  jmethodID method_id = env->GetMethodID(m_JNIClass, "HasReady", "()V");
  assert(NULL != method_id);
  env->CallVoidMethod(m_JNIObject, method_id);
}

jclass NativeHelper::RetrieveClass(JNIEnv*& rpEnv, const std::string& rsNativeClassName, const std::string& rsHelperClassName)
{
  jclass activity_class = rpEnv->FindClass(rsNativeClassName.c_str());
  jmethodID get_class_loader = rpEnv->GetMethodID(activity_class, "getClassLoader", "()Ljava/lang/ClassLoader;");
  jobject cls = rpEnv->CallObjectMethod(m_pActivity->clazz, get_class_loader);
  jclass class_loader = rpEnv->FindClass("java/lang/ClassLoader");
  jmethodID find_class = rpEnv->GetMethodID(class_loader, "loadClass", "(Ljava/lang/String;)Ljava/lang/Class;");

  jstring str_class_name = rpEnv->NewStringUTF(rsHelperClassName.c_str());
  jclass class_retrieved = (jclass)rpEnv->CallObjectMethod(cls, find_class, str_class_name);
  rpEnv->DeleteLocalRef(str_class_name);
  return class_retrieved;
}

void potato_main(android_app* pApp, const std::string& rsNativeClassName, const std::string& rsHelperClassName)
{
  C4G_LOG_INFO(__PRETTY_FUNCTION__);

  app_dummy();

  NativeHelper::Instance().Initialize(pApp, rsNativeClassName, rsHelperClassName);

  std::string libr_path = NativeHelper::Instance().GetLibraryPath();
  std::string data_path = NativeHelper::Instance().GetExternalPath();
  std::string config = "{\"engine\":{\"library\":\"lib/libengine.so\"}}";
  c4g::Potato::Instance().Initialize(libr_path, data_path, config);

  NativeHelper::Instance().HasReady();

  c4g::core::IEngine*& engine_ptr = c4g::Potato::Instance().GetEngine();
  C4G_LOG_INFO("engine: %d", engine_ptr);
  assert(NULL != engine_ptr);
  engine_ptr->Run(pApp);
}
