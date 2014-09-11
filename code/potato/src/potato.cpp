#include <rapidjson/document.h>

#include "potato.h"

#include "utility/sharedlibrary.h"
#include "utility/file.h"
#include "utility/log.h"

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
  Potato& Initialize(const std::string& rsLibrPath, const std::string& rsDataPath, const std::string& rsConfigFile);
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

static utility::CSharedLibraryManager gs_SharedLibraryManager;

Potato& Potato::Instance()
{
  static Potato s_potato;
  return s_potato;
}

Potato::Potato()
  : m_pEngine(NULL)
{
  C4G_LOG_INFO(__PRETTY_FUNCTION__);
}

Potato::~Potato()
{
  if (NULL != m_pEngine)
  {
    /// load the shared library
    typedef FUNC_API_TYPE(DestroyEngine) DestroyEngineFuncPtr;
    DestroyEngineFuncPtr func_destroy_func_ptr = gs_SharedLibraryManager.GetFunc<DestroyEngineFuncPtr>(m_oConfigEngine.GetLibraryFile(), TOSTRING(DestroyEngine));
    /// destroy the engine with configure
    func_destroy_func_ptr(m_pEngine, m_oConfigEngine);
  }
  C4G_LOG_INFO(__PRETTY_FUNCTION__);
}

#if defined(BUILD_ANDROID)
Potato& Potato::Initialize(const std::string& rsLibrPath, const std::string& rsDataPath, const std::string& rsConfig)
#else
Potato& Potato::Initialize(const std::string& rsLibrPath, const std::string& rsDataPath, const std::string& rsConfigFile)
#endif
{
  C4G_LOG_INFO(__PRETTY_FUNCTION__);
  if (NULL == m_pEngine)
  {
#if defined(BUILD_ANDROID)
    std::string file_context = rsConfig.c_str();
#else
    std::string file_context = utility::ReadFile((rsDataPath + "/" + rsConfigFile).c_str());
#endif
    //C4G_LOG_INFO("0- %s %s %s %s", __PRETTY_FUNCTION__, rsLibrPath.c_str(), rsDataPath.c_str(), file_context.c_str());

    /// parse the configure file
    /// and check the value's type
    rapidjson::Document doc;
    doc.Parse(file_context.c_str());
    assert(doc.IsObject());

    m_oConfigEngine._sLibrPath = rsLibrPath;
    m_oConfigEngine._sDataPath = rsDataPath;

    const rapidjson::Value& engine = doc["engine"];
    assert(engine.IsObject());

    const rapidjson::Value& library = engine["library"];
    assert(library.IsString());
    m_oConfigEngine._sLibraryFile = library.GetString();

#if defined(BUILD_ANDROID)
    m_oConfigEngine._sConfigureContext = "\
{\
  \"display\":{\
    \"library\":\"lib/libdisplay_gles.so\"\
  },\
  \"scene\":{\
    \"library\":\"lib/libscene.so\"\
  }\
}";
#else
    const rapidjson::Value& configure = engine["configure"];
    assert(configure.IsString());
    m_oConfigEngine._sConfigureFile = configure.GetString();
#endif

    typedef FUNC_API_TYPE(CreateEngine) CreateEngineFuncPtr;
    /// load the shared library
    CreateEngineFuncPtr func_create_func_ptr = gs_SharedLibraryManager.GetFunc<CreateEngineFuncPtr>(m_oConfigEngine.GetLibraryFile(), TOSTRING(CreateEngine));
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
