#pragma once

#include "common.h"

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

class IScene
{
public:
  virtual ~IScene()
  {
    ;
  }

public:
  virtual bool Load(core::IRender* const& rpRender, const std::string& rsFileName) = 0;
  virtual bool Unload(core::IRender* const& rpRender) = 0;
  virtual bool Resize(const int& riWidth, const int& riHeight) = 0;
  virtual bool Tick(const float& rfDelta) = 0;
  virtual bool Draw(render::ICanvas* const& rpCanvas) = 0;
  virtual bool Handle(const display::IInput* const& rpInput) = 0;
  virtual bool Refresh(const display::ISensor* const& rpSensor) = 0;
};

}

}

FUNC_API_DECLARE(CreateScene, c4g::core::IScene, const c4g::base::Config);
FUNC_API_DECLARE(DestroyScene, c4g::core::IScene, const c4g::base::Config);
