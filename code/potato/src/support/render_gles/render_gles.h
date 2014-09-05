#pragma once

#include "common.h"

#include "render.h"

namespace ac {

namespace core {
class IScene;
}

namespace render {
namespace gles {

class CRender : public core::IRender
{
public:
  CRender(const base::Config& roConfig);
  virtual ~CRender();

public:
  virtual void Start();
  virtual bool Resize(const int& riWidth, const int& riHeight);
  virtual bool Render(const float& rfDeltaTime, core::IScene* pScene);
  virtual void End();

private:
  void Perspective(double fovy, double aspect, double near, double far);
};

} // gles
} // render
} // ac
