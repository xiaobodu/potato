#pragma once

#include "scene_base.h"

namespace c4g {

namespace core {
class IAsset;
class IScript;
}
namespace utility{
class CSharedLibraryManager;
}

namespace scene {

class IPanel;

class CScene : public ISceneWithScript
{
public:
  explicit CScene(const base::Config& roConfig);
  virtual ~CScene();

public:
  virtual bool Load(core::IRender* const& rpRender, const std::string& rsFileName);
  virtual bool Unload(core::IRender* const& rpRender);
  virtual bool Resize(const int& riWidth, const int& riHeight);
  virtual bool Tick(const float& rfDelta);
  virtual bool Draw(render::ICanvas* const& rpCanvas);
  virtual bool Handle(const display::IInput* const& rpInput);
  virtual bool Refresh(const display::ISensor* const& rpSensor);

public:
  virtual void BindScript(script::AHandler* const& rpHandler);

private:
  base::Config          m_oConfig;
  base::Config          m_oConfigAsset;
  core::IAsset*         m_pAsset;
  base::Config          m_oConfigScript;
  core::IScript*        m_pScript;
  utility::CSharedLibraryManager* m_pLibraryManager;

  IPanel* m_pPanel;
};

}
}
