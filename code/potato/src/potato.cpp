#include "potato.h"

#include "utility/sharedlibrary.h"
#include "utility/file.h"
#include "utility/log.h"

#include <rapidjson/document.h>

#if !defined(BUILD_ANDROID)
#include "common.h"

namespace c4g {

/*!
 * \class Potato
 * \brief A main entry of the application
 */
class Potato
{
public:
  static Potato& Instance();

protected:
  Potato();
  virtual ~Potato();

public:
  Potato& Initialize(const std::string& rsLibPath, const std::string& rsDataPath, const std::string& rsConfigFile);
  core::IEngine*& GetEngine();

private:
  c4g::base::Config m_oConfigEngine;
  core::IEngine* m_pEngine;
};

}
#endif

FUNC_API_TYPEDEF(CreateEngine, c4g::core::IEngine, const c4g::base::Config);
FUNC_API_TYPEDEF(DestroyEngine, c4g::core::IEngine, const c4g::base::Config);

namespace c4g {

static utility::DynamicLibraryManager gs_DynamicLibraryManager;

Potato& Potato::Instance()
{
  static Potato s_potato;
  return s_potato;
}

Potato::Potato() :
    m_pEngine(NULL)
{
  utility::Log::Instance().Info(__PRETTY_FUNCTION__);
}

Potato::~Potato()
{
  if (NULL != m_pEngine)
  {
    /// load the dynamic library
    typedef FUNC_API_TYPE(DestroyEngine) DestroyEngineFuncPtr;
    DestroyEngineFuncPtr func_destroy_func_ptr = gs_DynamicLibraryManager.GetFunc<DestroyEngineFuncPtr>(m_oConfigEngine.GetLibraryFile(), TOSTRING(DestroyEngine));
    /// destroy the engine with configure
    func_destroy_func_ptr(m_pEngine, m_oConfigEngine);
  }
  utility::Log::Instance().Info(__PRETTY_FUNCTION__);
}

Potato& Potato::Initialize(const std::string& rsLibPath, const std::string& rsDataPath, const std::string& rsConfigFile)
{
  utility::Log::Instance().Info(__PRETTY_FUNCTION__);
  if (NULL == m_pEngine)
  {
    utility::Log::Instance().Info("libr:%s | data:%s", rsLibPath.c_str(), rsDataPath.c_str());
    std::string file_context = utility::ReadFile((rsDataPath + "/" + rsConfigFile).c_str());

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

    m_oConfigEngine._sLibrPath = rsLibPath;
    m_oConfigEngine._sDataPath = rsDataPath;
    m_oConfigEngine._sLibraryFile = library_file.GetString();
    m_oConfigEngine._sConfigureFile = configure_file.GetString();

    /// load the dynamic library
    typedef FUNC_API_TYPE(CreateEngine) CreateEngineFuncPtr;
    CreateEngineFuncPtr func_create_func_ptr = gs_DynamicLibraryManager.GetFunc<CreateEngineFuncPtr>(m_oConfigEngine.GetLibraryFile(), TOSTRING(CreateEngine));
    /// create the engine with configure
    func_create_func_ptr(m_pEngine, m_oConfigEngine);
  }

  return *this;
}

core::IEngine*& Potato::GetEngine()
{
  assert(NULL != m_pEngine);
  return m_pEngine;
}

}

#if !defined(BUILD_ANDROID)
int main(int argc, char* argv[])
{
  std::string libr_path;
  std::string data_path;
  std::string file;
  GetConfig(libr_path, data_path, file);
  c4g::core::IEngine*& engine_ptr = c4g::Potato::Instance().Initialize(libr_path, data_path, file).GetEngine();
  engine_ptr->Run();
  return 0;
}
#endif
