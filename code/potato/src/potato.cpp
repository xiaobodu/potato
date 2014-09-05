#include "potato.h"

#include "utility/util_dl.h"
#include "utility/util_file.h"
#include "utility/util_log.h"

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
  static Potato& Instance();

protected:
  Potato();
  virtual ~Potato();

public:
  Potato& Initialize(const std::string& rsDataPath, const std::string& rsConfigFile);
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

static utility::DynamicLibraryManager gs_DynamicLibraryManager;

Potato& Potato::Instance()
{
  static Potato s_potato;
  return s_potato;
}

Potato::Potato() :
    m_pEngine(NULL)
{
  ;
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
}

#if defined(BUILD_ANDROID)
Potato& Potato::Initialize(const std::string& rsLibPath, const std::string& rsDataPath, const std::string& rsConfigFile)
#else
Potato& Potato::Initialize(const std::string& rsDataPath, const std::string& rsConfigFile)
#endif
{
  utility::Log::Instance().Info("call %s", __FUNCTION__);
  if (NULL == m_pEngine)
  {
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

#if defined(BUILD_ANDROID)
    m_oConfigEngine._sLibrPath = rsLibPath;
#else
    m_oConfigEngine._sLibrPath = rsDataPath;
#endif
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
  std::string path;
  std::string file;
  GetConfig(path, file);
  ac::core::IEngine*& engine_ptr = ac::Potato::Instance().Initialize(path, file).GetEngine();
  engine_ptr->Run();
  return 0;
}
#endif
