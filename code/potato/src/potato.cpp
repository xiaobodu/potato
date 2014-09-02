#include "potato.h"

#include "utility/util_dl.h"
#include "utility/util_file.h"

#include <rapidjson/document.h>

#if !defined(BUILD_ANDROID)
#include "common.h"

namespace ac {

/*!
 * \class Potato
 * \brief A main entry of the application
 */
class Potato
{
public:
  static Potato& Instance(const std::string& rsDataPath, const std::string& rsConfigFile);

protected:
  Potato(const std::string& rsDataPath, const std::string& rsConfigFile);
  virtual ~Potato();

public:
  core::IEngine*& GetEngine();

private:
  ac::base::Config m_oConfigEngine;
  core::IEngine* m_pEngine;
};

}
#endif

FUNC_API_TYPEDEF(CreateEngine, ac::core::IEngine, const ac::base::Config);
FUNC_API_TYPEDEF(DestroyEngine, ac::core::IEngine, const ac::base::Config);

namespace ac {

Potato& Potato::Instance(const std::string& rsDataPath, const std::string& rsConfigFile)
{
  static Potato s_potato(rsDataPath, rsConfigFile);
  return s_potato;
}

Potato::Potato(const std::string& rsRootPath, const std::string& rsConfigFile) :
    m_pEngine(NULL)
{
  std::string file_context = utility::ReadFile((rsRootPath + "/" + rsConfigFile).c_str());

  /// parse the configure file
  /// and check the value's type
  rapidjson::Document doc;
  doc.Parse(file_context.c_str());
  assert(doc.IsObject());
  const rapidjson::Value& engine = doc["engine"];
  assert(engine.IsObject());
  const rapidjson::Value& library = engine["library"];
  assert(library.IsObject());
  const rapidjson::Value& library_file = library["file"];
  assert(library_file.IsString());
  const rapidjson::Value& configure = engine["configure"];
  assert(configure.IsObject());
  const rapidjson::Value& configure_file = configure["file"];
  assert(configure_file.IsString());

  m_oConfigEngine._sPath = rsRootPath;
  m_oConfigEngine._sLibraryFile = library_file.GetString();
  m_oConfigEngine._sConfigureFile = configure_file.GetString();

  /// load the dynamic library
  typedef FUNC_API_TYPE(CreateEngine) CreateEngineFuncPtr;
#if defined(BUILD_ANDROID)
  CreateEngineFuncPtr func_create_func_ptr = utility::DynamicLibraryManager::Instance().GetFunc<CreateEngineFuncPtr>(m_oConfigEngine._sLibraryFile, TOSTRING(CreateEngine));
#else
  CreateEngineFuncPtr func_create_func_ptr = utility::DynamicLibraryManager::Instance().GetFunc<CreateEngineFuncPtr>(m_oConfigEngine.GetLibraryFile(), TOSTRING(CreateEngine));
#endif
  /// create the engine with configure
  func_create_func_ptr(m_pEngine, m_oConfigEngine);
}

Potato::~Potato()
{
  /// load the dynamic library
  typedef FUNC_API_TYPE(DestroyEngine) DestroyEngineFuncPtr;
#if defined(BUILD_ANDROID)
  DestroyEngineFuncPtr func_destroy_func_ptr = utility::DynamicLibraryManager::Instance().GetFunc<DestroyEngineFuncPtr>(m_oConfigEngine._sLibraryFile, TOSTRING(DestroyEngine));
#else
  DestroyEngineFuncPtr func_destroy_func_ptr = utility::DynamicLibraryManager::Instance().GetFunc<DestroyEngineFuncPtr>(m_oConfigEngine.GetLibraryFile(), TOSTRING(DestroyEngine));
#endif
  /// destroy the engine with configure
  func_destroy_func_ptr(m_pEngine, m_oConfigEngine);
}

core::IEngine*& Potato::GetEngine()
{
  return m_pEngine;
}

}

#if !defined(BUILD_ANDROID)
int main(int argc, char* argv[])
{
  std::string path;
  std::string file;
  GetConfig(path, file);
  ac::core::IEngine*& engine = ac::Potato::Instance(path, file).GetEngine();
  engine->Run();
  return 0;
}
#endif
