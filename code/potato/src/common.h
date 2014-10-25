#pragma once

#include <cassert>
#include <cstring>
#include <iostream>
#include <map>

#define ENGINE_NAME     "potato"
#define ENGINE_VERSION_MAX  0
#define ENGINE_VERSION_MIN  1

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
#define FUNC_API_DECLARE(function_name, class_class)\
    extern "C" bool function_name(class_class*& rpClass);
#define FUNC_API_TYPEDEF(function_name, class_class)\
    typedef bool (*FUNC_API_TYPE(function_name))(class_class*& rpClass);

#if defined(BUILD_ANDROID)
struct android_app;
#endif

#if defined(CXX_MSVC)
# if defined(C4G_API_EXPORT)
#  define C4G_API     __declspec(dllexport)
# elif defined(C4G_API_IMPORT)
#  define C4G_API     __declspec(dllimport)
# else
#   define C4G_API
# endif
#else
# define C4G_API
#endif

#define MODULE_TYPE_ENGINE    "engine"

#if defined(CXX_MSVC)
// stl export
//template class C4G_API std::basic_string<char, std::char_traits<char>, std::allocator<char> >;
#endif

namespace c4g {
namespace core {

class C4G_API IModule;

FUNC_API_TYPEDEF(CreateModule, IModule);
FUNC_API_TYPEDEF(DestroyModule, IModule);

template<unsigned int size>
class C4G_API Name
{
public:
  explicit Name()
  {
    memset(m_acBuffer, 0, sizeof(char) * size);
  }
  explicit Name(const std::string& rsValue)
  {
    assert(rsValue.length() < (sizeof(char) * size - 1));
    memset(m_acBuffer, 0, sizeof(char) * size);
    memcpy(m_acBuffer, rsValue.data(), sizeof(char) * rsValue.length());
  }
  explicit Name(const Name<size>& rOther)
  {
    memcpy(m_acBuffer, rOther.m_acBuffer, sizeof(char) * size);
  }

public:
  Name<size>& operator=(const Name<size>& rOther)
  {
    memcpy(m_acBuffer, rOther.m_acBuffer, sizeof(char) * size);
    return (*this);
  }
  Name<size>& operator=(const std::string& rsValue)
  {
    assert(rsValue.length() < (sizeof(char) * size - 1));
    memset(m_acBuffer, 0, sizeof(char) * size);
    memcpy(m_acBuffer, rsValue.data(), sizeof(char) * rsValue.length());
    return (*this);
  }
  bool operator==(const Name<size>& rOther) const
  {
    for (int i = 0; i < size; ++i)
    {
      if (rOther.m_acBuffer[i] != m_acBuffer[i]) return false;
    }
    return true;
  }
  bool operator<(const Name<size>& rOther) const
  {
    for (int i = 0; i < size; ++i)
    {
      if (rOther.m_acBuffer[i] < m_acBuffer[i]) return true;
    }
    return false;
  }
  const char* const operator*() const
  {
    return m_acBuffer;
  }

private:
  char m_acBuffer[size];

public:
  static Name<size> None;
};
typedef std::map<std::string, IModule*> MString2Module;

class C4G_API IModule
{
public:
  const Name<32> type;
  typedef FUNC_API_TYPE(core::CreateModule) CreateModuleFuncPtr;
  CreateModuleFuncPtr m_pCreateFunc;
  typedef FUNC_API_TYPE(core::DestroyModule) DestroyModuleFuncPtr;
  DestroyModuleFuncPtr m_pDestroyFunc;

public:
  explicit IModule(const std::string& rsType = "")
    : type(rsType)
    , m_pCreateFunc(NULL)
    , m_pDestroyFunc(NULL)
  {
    ;
  }
  virtual ~IModule()
  {
    ;
  }

public:
  virtual bool Initialize(core::MString2Module& rmModule) = 0;

public:
  template<class TClass>
  static TClass* Find(MString2Module& rmModule, const std::string& rsType)
  {
    TClass* res_ptr = NULL;
    core::MString2Module::iterator it_find = rmModule.find(rsType);
    if (it_find != rmModule.end())
    {
      res_ptr = reinterpret_cast<TClass*>(it_find->second);
    }
    return res_ptr;
  }
  static void Destroy(IModule*& rpModule)
  {
    if (NULL == rpModule) return;
    DestroyModuleFuncPtr func_ptr = rpModule->m_pDestroyFunc;
    if (NULL == func_ptr) return;
    rpModule->m_pDestroyFunc = NULL;
    func_ptr(rpModule);
  }
};

class C4G_API IEngine : public IModule
{
public:
  explicit IEngine()
    : IModule(MODULE_TYPE_ENGINE)
  {
    ;
  }
  virtual ~IEngine()
  {
    ;
  }

public:
#if defined(BUILD_ANDROID)
  virtual void Run(const std::string& rsDataPath, android_app* pApp) = 0;
#else
  virtual void Run(const std::string& rsDataPath) = 0;
#endif
};

} // end of namespace core
} // end of namespace ac
