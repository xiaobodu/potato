#pragma once

#include "common.h"

#include "render.h"

namespace c4g {
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
  virtual bool Render(const float& rfDeltaTime, core::IScene* const& rpScene);
  virtual void End();

public:
  virtual unsigned int GenerateTexId(const int& riWidth, const int& riHeight, const unsigned char* const& rpBuffer);
  virtual void DeleteTexId(const int& riCount, const unsigned int* const& rpiTexId);

private:
  void SetView(const int& riWidth, const int& riHeight, const double& rdNear, const double& rdFar);
  void Perspactive(const double& rdFovy, const double& rdAspect, const double& rdNear, const double& rdFar);

private:
  render::ICanvas* m_pCanvas;
};

} // gles
} // render
} // ac
