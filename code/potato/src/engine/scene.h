#pragma once

#include "base.h"

#define MODULE_TYPE_SCENE    "scene"

namespace c4g {

namespace core {
class IRender;
}
namespace display {
class IInput;
class ISensor;
}

namespace render {
struct Glyph;
class ICanvas;
}

namespace core {

class C4G_API IScene : public IModule
{
public:
  explicit IScene()
    : IModule(MODULE_TYPE_SCENE)
  {
    ;
  }
  virtual ~IScene()
  {
    ;
  }

public:
  virtual void SetDataPath(const std::string& rsDataPath) = 0;
  virtual bool Load(core::IRender* const& rpRender, const std::string& rsFileName, bool bIsAbsolutePath = false) = 0;
  virtual bool Unload(core::IRender* const& rpRender) = 0;
  virtual bool Resize(const int& riWidth, const int& riHeight) = 0;
  virtual bool Tick(const float& rfDelta) = 0;
  virtual bool Draw(render::ICanvas* const& rpCanvas) = 0;
  virtual bool Handle(const display::IInput* const& rpInput) = 0;
  virtual bool Refresh(const display::ISensor* const& rpSensor) = 0;
};

}

}
