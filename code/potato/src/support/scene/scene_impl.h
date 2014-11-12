#pragma once

#include "scene_base.h"

namespace c4g {

namespace core {
class IAsset;
class IFlash;
class IScript;
}
namespace utility{
class CSharedLibraryManager;
}

namespace scene {

class IPanel;

class C4G_API CScene : public ISceneImpl
{
public:
  explicit CScene();
  virtual ~CScene();

public:
  virtual bool Initialize(core::MString2Module& rmModule);

public:
  virtual void SetDataPath(const std::string& rsDataPath);
  virtual bool Load(core::IRender* const& rpRender, const std::string& rsFileName, bool bIsAbsolutePath = false);
  virtual bool Unload(core::IRender* const& rpRender);
  virtual bool Resize(const int& riWidth, const int& riHeight);
  virtual bool Tick(const float& rfDelta);
  virtual bool Draw(core::IRender* const& rpRender);
  virtual bool Handle(const display::IInput* const& rpInput);
  virtual bool Refresh(const display::ISensor* const& rpSensor);

public:
  virtual core::IAsset* const& GetAssetPtr();
  virtual core::IFlash* const& GetFlashPtr();
  virtual void BindScript(script::AHandler* const& rpHandler);
  virtual const char* const GetDataPath() const;
  virtual IPanel* const& GetPanel();

public:

private:
  core::Name<64>        m_sDataPath;
  //std::string           m_sDataPath;
  core::IAsset*         m_pAsset;
  core::IFlash*         m_pFlash;
  core::IScript*        m_pScript;

  IPanel* m_pPanel;
  bool m_bNeedFlush;

  bool m_bPlayEffect;
};

}
}
