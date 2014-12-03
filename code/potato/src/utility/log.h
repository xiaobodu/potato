#pragma once

#include <cstdio>
#include <cassert>
#include <cstdarg>
#include <cstdio>

#if defined(BUILD_ANDROID)

#include <android/log.h>

#define LOG_TAG             "potato"
#define LOGUNKNOWN(...)     ((void)__android_log_print(ANDROID_LOG_UNKNOWN, LOG_TAG, __VA_ARGS__))
#define LOGDEFAULT(...)     ((void)__android_log_print(ANDROID_LOG_DEFAULT, LOG_TAG, __VA_ARGS__))
#define LOGV(...)           ((void)__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__))
#define LOGD(...)           ((void)__android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__))
#define LOGI(...)           ((void)__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__))
#define LOGW(...)           ((void)__android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__))
#define LOGE(...)           ((void)__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__))
#define LOGF(...)           ((void)__android_log_print(ANDROID_LOG_FATAL, LOG_TAG, __VA_ARGS__))
#define LOGSILENT(...)      ((void)__android_log_print(ANDROID_LOG_SILENT, LOG_TAG, __VA_ARGS__))

#endif

namespace c4g {
namespace utility {

#if !defined(BUILD_ANDROID)
// define the style/color code
#define TEXT_STYLE_END                  "\x1b[0m"
#define TEXT_STYLE_BOLD                 "\x1b[1m"
#define TEXT_STYLE_UNDERLINE            "\x1b[4m"
#define TEXT_STYLE_COLOR_BLACK          "\x1b[30m"
#define TEXT_STYLE_COLOR_RED            "\x1b[31m"
#define TEXT_STYLE_COLOR_GREEN          "\x1b[32m"
#define TEXT_STYLE_COLOR_YELLOW         "\x1b[33m"
#define TEXT_STYLE_COLOR_BLUE           "\x1b[34m"
#define TEXT_STYLE_COLOR_MAGENTA        "\x1b[35m"
#define TEXT_STYLE_COLOR_CYAN           "\x1b[36m"
#define TEXT_STYLE_COLOR_WHITE          "\x1b[37m"
#define TEXT_STYLE_BGCOLOR_BLACK        "\x1b[40m"
#define TEXT_STYLE_BGCOLOR_RED          "\x1b[41m"
#define TEXT_STYLE_BGCOLOR_GREEN        "\x1b[42m"
#define TEXT_STYLE_BGCOLOR_YELLOW       "\x1b[43m"
#define TEXT_STYLE_BGCOLOR_BLUE         "\x1b[44m"
#define TEXT_STYLE_BGCOLOR_MAGENTA      "\x1b[45m"
#define TEXT_STYLE_BGCOLOR_CYAN         "\x1b[46m"
#define TEXT_STYLE_BGCOLOR_WHITE        "\x1b[47m"

const static char* TextStyleCode[] = { TEXT_STYLE_END,
TEXT_STYLE_BOLD, TEXT_STYLE_UNDERLINE,
TEXT_STYLE_COLOR_BLACK, TEXT_STYLE_COLOR_RED, TEXT_STYLE_COLOR_GREEN, TEXT_STYLE_COLOR_YELLOW,
TEXT_STYLE_COLOR_BLUE, TEXT_STYLE_COLOR_MAGENTA, TEXT_STYLE_COLOR_CYAN, TEXT_STYLE_COLOR_WHITE,
TEXT_STYLE_BGCOLOR_BLACK, TEXT_STYLE_BGCOLOR_RED, TEXT_STYLE_BGCOLOR_GREEN, TEXT_STYLE_BGCOLOR_YELLOW,
TEXT_STYLE_BGCOLOR_BLUE, TEXT_STYLE_BGCOLOR_MAGENTA, TEXT_STYLE_BGCOLOR_CYAN, TEXT_STYLE_BGCOLOR_WHITE };
#endif

#define TEXT_BUFFER_SIZE_MAX            1024
#if defined(CXX_GNU) ||  defined(BUILD_ANDROID)
#define GET_ARGS_TEXT(text, result)\
    char result[TEXT_BUFFER_SIZE_MAX];\
    va_list args;\
    va_start(args, text);\
    vsprintf(result, text, args);\
    va_end(args)
#elif defined(CXX_MSVC)
#define GET_ARGS_TEXT(text, result)\
    char result[TEXT_BUFFER_SIZE_MAX];\
    va_list args;\
    va_start(args, text);\
    vsprintf_s(result, TEXT_BUFFER_SIZE_MAX, text, args);\
    va_end(args)
#endif

class Log
{
public:
#if !defined(BUILD_ANDROID)
  typedef enum enmLogStyle
  {
    EStyle_End = 0,
    EStyle_Bold,
    EStyle_UnderLine,
    EStyle_Color_Black,
    EStyle_Color_Red,
    EStyle_Color_Green,
    EStyle_Color_Yellow,
    EStyle_Color_Blue,
    EStyle_Color_Magenta,
    EStyle_Color_Cyan,
    EStyle_Color_White,
    EStyle_BGColor_Black,
    EStyle_BGColor_Red,
    EStyle_BGColor_Green,
    EStyle_BGColor_Yellow,
    EStyle_BGColor_Blue,
    EStyle_BGColor_Magenta,
    EStyle_BGColor_Cyan,
    EStyle_BGColor_White,
    EStyle_None,
  } LogStyle;
#endif

public:
  static const Log& Instance()
  {
    static Log gs_Instance;
    return gs_Instance;
  }

protected:
  Log()
  {
    ;
  }
  virtual ~Log()
  {
    ;
  }

public:
  void Fatal(const char* const & rcText, ...) const
  {
    GET_ARGS_TEXT(rcText, result);
#if defined(BUILD_ANDROID)
    LOGF("[FATA] %s", result);
#else
    (*this)(stderr, EStyle_BGColor_Red, "FATA", result);
#endif
  }

  void Error(const char* const & rcText, ...) const
  {
    GET_ARGS_TEXT(rcText, result);
#if defined(BUILD_ANDROID)
    LOGE("[ERRO] %s", result);
#else
    (*this)(stderr, EStyle_Color_Red, "ERRO", result);
#endif
  }

  void Warning(const char* const & rcText, ...) const
  {
    GET_ARGS_TEXT(rcText, result);
#if defined(BUILD_ANDROID)
    LOGW("[WARN] %s", result);
#else
    (*this)(stdout, EStyle_Color_Yellow, "WARN", result);
#endif
  }

  void System(const char* const & rcText, ...) const
  {
    GET_ARGS_TEXT(rcText, result);
#if defined(BUILD_ANDROID)
    LOGV("[SYST] %s", result);
#else
    (*this)(stdout, EStyle_Color_Cyan, "SYST", result);
#endif
  }

  void Info(const char* const & rcText, ...) const
  {
    GET_ARGS_TEXT(rcText, result);
#if defined(BUILD_ANDROID)
    LOGI("[INFO] %s", result);
#else
    (*this)(stdout, EStyle_None, "INFO", result);
#endif
  }

  void Debug(const char* const & rcText, ...) const
  {
    GET_ARGS_TEXT(rcText, result);
#if defined(BUILD_ANDROID)
    LOGD("[DEBU] %s", result);
#else
    (*this)(stdout, EStyle_Color_Magenta, "DEBU", result);
#endif
  }

  void User(const char* const & rcText, ...) const
  {
    GET_ARGS_TEXT(rcText, result);
#if defined(BUILD_ANDROID)
    LOGV("[USER] %s", result);
#else
    (*this)(stdout, EStyle_Color_Green, "USER", result);
#endif
  }

#if !defined(BUILD_ANDROID)
  void operator()(FILE* pFile, const LogStyle& eStyle, const char* const & rcTitle, const char* const & rcText, ...) const
  {
    assert(pFile != NULL);
    assert(rcTitle != NULL);
    assert(rcText != NULL);

    GET_ARGS_TEXT(rcText, result);

    switch (eStyle)
    {
    case EStyle_None:
      fprintf(pFile, "[%s] %s\n", rcTitle, result);
      break;

    case EStyle_Bold:
    case EStyle_Color_Black:
    case EStyle_Color_Red:
    case EStyle_Color_Green:
    case EStyle_Color_Yellow:
    case EStyle_Color_Blue:
    case EStyle_Color_Magenta:
    case EStyle_Color_Cyan:
    case EStyle_Color_White:
    case EStyle_BGColor_Black:
    case EStyle_BGColor_Red:
    case EStyle_BGColor_Green:
    case EStyle_BGColor_Yellow:
    case EStyle_BGColor_Blue:
    case EStyle_BGColor_Magenta:
    case EStyle_BGColor_Cyan:
    case EStyle_BGColor_White:
#if defined(OS_IS_LINUX)
      fprintf(stdout, "[%s%s" TEXT_STYLE_END "] %s%s" TEXT_STYLE_END "\n", TextStyleCode[eStyle], rcTitle, TextStyleCode[eStyle], result);
#else
      fprintf(stdout, "[%s] %s\n", rcTitle, result);
#endif
      break;

    default:
      assert(0);
      break;
    }
  }
#endif

public:
  void TestAllLogTypes() const
  {
    Fatal("TestAllLogTypes %s", "fatal");
    Error("TestAllLogTypes %s", "error");
    Warning("TestAllLogTypes %s", "warning");
    System("TestAllLogTypes %s", "system");
    Info("TestAllLogTypes %s", "info");
    Debug("TestAllLogTypes %s", "debug");
    User("TestAllLogTypes %s", "user");
  }
};

}
}

#define C4G_LOG_FATAL(...)      c4g::utility::Log::Instance().Fatal(__VA_ARGS__)
#define C4G_LOG_ERROR(...)      c4g::utility::Log::Instance().Error(__VA_ARGS__)
#define C4G_LOG_WARNING(...)    c4g::utility::Log::Instance().Warning(__VA_ARGS__)
#if defined(BUILD_DEBUG)
#define C4G_LOG_SYSTEM(...)     c4g::utility::Log::Instance().System(__VA_ARGS__)
#define C4G_LOG_INFO(...)       c4g::utility::Log::Instance().Info(__VA_ARGS__)
#define C4G_LOG_DEBUG(...)      c4g::utility::Log::Instance().Debug(__VA_ARGS__)
#define C4G_LOG_USER(...)       c4g::utility::Log::Instance().User(__VA_ARGS__)
#else
#define C4G_LOG_SYSTEM(...)
#define C4G_LOG_INFO(...)
#define C4G_LOG_DEBUG(...)
#define C4G_LOG_USER(...)
#endif
