#include <jni.h>
#include <cassert>
#include <pthread.h>
#include <android/log.h>
#include <android_native_app_glue.h>

#include "potato.h"
#include "utility/util_log.h"

#include <EGL/egl.h>
#include <GLES/gl.h>

#define PLOG_TAG             "potato"
#define PLOGI(...)           ((void)__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__))

#define CLASS_NAME "android/app/NativeActivity"
#define HELPER_CLASS_NAME "me/alexchi/potato/PNativeHelper"

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
  void Initialize(struct android_app*& rpApp, const std::string& rsClassName);
  void Destroy();

public:
  std::string GetLibraryPath();
  std::string GetExternalPath();

protected:
  jclass RetrieveClass(JNIEnv*& rpEnv, const std::string& rsClassName);

private:
  bool m_bIsReady;
  mutable pthread_mutex_t m_Mutex;
  ANativeActivity* m_pActivity;
  std::string m_sAppName;
  std::string m_sClassName;
  jobject m_JNIObject;
  jclass m_JNIClass;
};

NativeHelper& NativeHelper::Instance()
{
  static NativeHelper s_Instance;
  return s_Instance;
}

NativeHelper::NativeHelper()
  : m_bIsReady(false), m_pActivity(NULL), m_sClassName("")
{
  ;
}

NativeHelper::~NativeHelper()
{
  ;
}

void NativeHelper::Initialize(struct android_app*& rpApp, const std::string& rsClassName)
{
  pthread_mutex_init(&m_Mutex, NULL);
  assert(NULL != rpApp);
  m_pActivity = rpApp->activity;
  m_sClassName = rsClassName;

  scope::ThreadMutex jni_env = scope::ThreadMutex(&m_Mutex, m_pActivity);
  JNIEnv*& env = jni_env.GetEnv();

  //Retrieve app name
  jclass android_content_Context = env->GetObjectClass(m_pActivity->clazz);
  jmethodID midGetPackageName = env->GetMethodID(android_content_Context, "getPackageName", "()Ljava/lang/String;");

  jstring packageName = (jstring) env->CallObjectMethod(m_pActivity->clazz, midGetPackageName);
  const char* appname = env->GetStringUTFChars(packageName, NULL);
  m_sAppName = std::string(appname);

  jclass cls = RetrieveClass(env, rsClassName);
  m_JNIClass = (jclass) env->NewGlobalRef(cls);

  jmethodID constructor = env->GetMethodID(m_JNIClass, "<init>", "()V" );
  m_JNIObject = env->NewObject(m_JNIClass, constructor);
  m_JNIObject = env->NewGlobalRef(m_JNIObject);

  env->ReleaseStringUTFChars(packageName, appname);

  m_bIsReady = true;
}

void NativeHelper::Destroy()
{
  if (!m_bIsReady)
  {
    return;
  }
  pthread_mutex_lock(&m_Mutex);

  JNIEnv* env = NULL;
  m_pActivity->vm->AttachCurrentThread( &env, NULL );

  env->DeleteGlobalRef(m_JNIObject);
  env->DeleteGlobalRef(m_JNIClass);

  pthread_mutex_destroy(&m_Mutex);
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

jclass NativeHelper::RetrieveClass(JNIEnv*& rpEnv, const std::string& rsClassName)
{
  jclass activity_class = rpEnv->FindClass(CLASS_NAME);
  jmethodID get_class_loader = rpEnv->GetMethodID(activity_class, "getClassLoader", "()Ljava/lang/ClassLoader;");
  jobject cls = rpEnv->CallObjectMethod(m_pActivity->clazz, get_class_loader);
  jclass class_loader = rpEnv->FindClass("java/lang/ClassLoader");
  jmethodID find_class = rpEnv->GetMethodID(class_loader, "loadClass", "(Ljava/lang/String;)Ljava/lang/Class;");

  jstring str_class_name = rpEnv->NewStringUTF(rsClassName.c_str());
  jclass class_retrieved = (jclass)rpEnv->CallObjectMethod(cls, find_class, str_class_name);
  rpEnv->DeleteLocalRef(str_class_name);
  return class_retrieved;
}

/*static void handle_cmd(struct android_app* app, int32_t cmd)
{
  switch (cmd)
  {
  case APP_CMD_INPUT_CHANGED:
    ac::utility::Log::Instance().Info("handle_cmd APP_CMD_INPUT_CHANGED");
    break;

  case APP_CMD_INIT_WINDOW:
    ac::utility::Log::Instance().Info("handle_cmd APP_CMD_INIT_WINDOW");
    if (NULL != app->window)
    {
      EGLDisplay dpy = eglGetDisplay(EGL_DEFAULT_DISPLAY);
      ac::utility::Log::Instance().Info("display: %d", (int)dpy);
      assert(EGL_NO_DISPLAY != m_pGLDisplay);
      EGLint egl_major = 0;
      EGLint egl_minor = 0;
      if (EGL_TRUE == eglInitialize(dpy, &egl_major, &egl_minor))
      {
        assert(0);
      }
      ac::utility::Log::Instance().Info("using EGL v%d.%d", egl_major, egl_minor);
    }
    break;

  case APP_CMD_TERM_WINDOW:
    ac::utility::Log::Instance().Info("handle_cmd APP_CMD_TERM_WINDOW");
    break;

  case APP_CMD_WINDOW_RESIZED:
    ac::utility::Log::Instance().Info("handle_cmd APP_CMD_WINDOW_RESIZED");
    break;

  case APP_CMD_WINDOW_REDRAW_NEEDED:
    ac::utility::Log::Instance().Info("handle_cmd APP_CMD_WINDOW_REDRAW_NEEDED");
    break;

  case APP_CMD_CONTENT_RECT_CHANGED:
    ac::utility::Log::Instance().Info("handle_cmd APP_CMD_CONTENT_RECT_CHANGED");
    break;

  case APP_CMD_GAINED_FOCUS:
    ac::utility::Log::Instance().Info("handle_cmd APP_CMD_GAINED_FOCUS");
    break;

  case APP_CMD_LOST_FOCUS:
    ac::utility::Log::Instance().Info("handle_cmd APP_CMD_LOST_FOCUS");
    break;

  case APP_CMD_CONFIG_CHANGED:
    ac::utility::Log::Instance().Info("handle_cmd APP_CMD_CONFIG_CHANGED");
    break;

  case APP_CMD_LOW_MEMORY:
    ac::utility::Log::Instance().Info("handle_cmd APP_CMD_LOW_MEMORY");
    break;

  case APP_CMD_START:
    ac::utility::Log::Instance().Info("handle_cmd APP_CMD_START");
    break;

  case APP_CMD_RESUME:
    ac::utility::Log::Instance().Info("handle_cmd APP_CMD_RESUME");
    break;

  case APP_CMD_SAVE_STATE:
    ac::utility::Log::Instance().Info("handle_cmd APP_CMD_SAVE_STATE");
    break;

  case APP_CMD_PAUSE:
    ac::utility::Log::Instance().Info("handle_cmd APP_CMD_PAUSE");
    break;

  case APP_CMD_STOP:
    ac::utility::Log::Instance().Info("handle_cmd APP_CMD_STOP");
    break;

  case APP_CMD_DESTROY:
    ac::utility::Log::Instance().Info("handle_cmd APP_CMD_DESTROY");
    break;
  }
}*/

void potato_main(struct android_app* state)
{
  PLOGI("potato_main");

  app_dummy();

  /*NativeHelper::Instance().Destroy();
  NativeHelper::Instance().Initialize(state, HELPER_CLASS_NAME);

  std::string libr_path = NativeHelper::Instance().GetLibraryPath();
  ac::utility::Log::Instance().Info("libr_path: %s", libr_path.c_str());
  std::string data_path = NativeHelper::Instance().GetExternalPath();
  ac::utility::Log::Instance().Info("data_path: %s", data_path.c_str());

  ac::Potato::Instance().Initialize(libr_path, data_path, "potato.json");*/
  ac::Potato::Instance().Initialize("/data/data/me.alexchi.test", "/mnt/sdcard/potato", "potato.json");

  ac::core::IEngine*& engine_ptr = ac::Potato::Instance().GetEngine();
  assert(NULL != engine_ptr);
  engine_ptr->Run(state);

  /*state->onAppCmd = handle_cmd;

  bool bIsRunning = true;
  while (bIsRunning)
  {
    // Read all pending events.
    int ident;
    int events;
    struct android_poll_source* source = NULL;

    while ((ident=ALooper_pollAll(bIsRunning ? 0 : -1, NULL, &events, (void**)&source)) >= 0)
    {
      // Process this event.
      if (source != NULL)
      {
        source->process(state, source);
      }

      // If a sensor has data, process it now.
      if (ident == LOOPER_ID_USER) { ; }

      // Check if we are exiting.
      if (state->destroyRequested != 0)
      {
        bIsRunning = false;
        break;
      }
    }
  }*/
}
