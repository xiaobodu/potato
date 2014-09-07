#pragma once

#include "common.h"

#include "render.h"

namespace c4g {

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
  void SetView(const int& riWidth, const int& riHeight, const double& rdNear, const double& rdFar);
  void Perspactive(double fovy, double aspect, double near, double far);

private:
};

} // gles
} // render
} // ac
