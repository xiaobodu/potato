#pragma once

#include "common.h"

namespace c4g {

namespace display {
class IInput;
}

namespace render {
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
  virtual bool Load(const std::string& rsFileName) = 0;
  virtual bool Resize(const int& riWidth, const int& riHeight) = 0;
  virtual bool Handle(const display::IInput* const pInput) = 0;
  virtual bool Tick(const float& rfDelta) = 0;
  virtual bool Draw(const render::ICanvas* pCanvas) = 0;
};

}

}

FUNC_API_DECLARE(CreateScene, c4g::core::IScene, const c4g::base::Config);
FUNC_API_DECLARE(DestroyScene, c4g::core::IScene, const c4g::base::Config);
