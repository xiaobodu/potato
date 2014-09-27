#pragma once

#include <string>
#include <iostream>

#define TOSTRING1(num)             #num
#define TOSTRING(num)              TOSTRING1(num)
#define SLINE                      TOSTRING(__LINE__)

#if !defined(NULL)
# define NULL 0
#endif

#if defined(CXX_MSVC)
#define __PRETTY_FUNCTION__		__FUNCTION__
#endif

/// declare the function of library
#define FUNC_API_TYPE(function_name)          function_name##Func
#define FUNC_API_DECLARE(function_name, class_class, config_class)\
    extern "C" bool function_name(class_class*& rpClass, config_class& roConfig);
#define FUNC_API_TYPEDEF(function_name, class_class, config_class)\
    typedef bool (*FUNC_API_TYPE(function_name))(class_class*& rpClass, config_class& roConfig);

#if defined(BUILD_ANDROID)
struct android_app;
#endif

#if defined(C4G_API_EXPORT)
# define C4G_API      __declspec(dllexport)
#elif defined(C4G_API_IMPORT)
# define C4G_API      __declspec(dllimport)
#else
# define C4G_API
#endif

namespace c4g {

namespace base {

typedef struct tagConfig
{
  std::string _sLibrPath;
  std::string _sDataPath;

  std::string _sLibraryFile;

  std::string GetLibraryFile() const
  {
    return _sLibrPath + "/" + _sLibraryFile;
  }

#if defined(BUILD_ANDROID)
  std::string _sConfigureContext;
#else
  std::string _sConfigureFile;
#endif

#if !defined(BUILD_ANDROID)
  std::string GetConfigureFile() const
  {
    return _sDataPath + "/" + _sConfigureFile;
  }
#endif

} Config;

} // end of namespace base

namespace core {

class IEngine
{
public:
  virtual ~IEngine()
  {
    ;
  }

public:
#if defined(BUILD_ANDROID)
  virtual void Run(android_app* pApp) = 0;
#else
  virtual void Run() = 0;
#endif
};

} // end of namespace core

} // end of namespace ac
