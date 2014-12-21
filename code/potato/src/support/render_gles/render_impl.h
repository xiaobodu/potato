#pragma once

#include "common.h"

#include "render.h"

namespace c4g {
namespace render {
namespace gles {

class C4G_API CRender : public core::IRender
{
public:
  CRender();
  virtual ~CRender();

public:
  virtual bool Initialize(core::MString2Module& rmModule);

public:
  virtual void Start();
  virtual bool Resize(const int32_t& riWidth, const int32_t& riHeight);
  virtual bool Render(const float& rfDeltaTime, core::IScene* const& rpScene);
  virtual void End();

public:
  virtual unsigned int GenerateTexId(const int& riWidth, const int& riHeight, const unsigned char* const& rpBuffer);
  virtual void DeleteTexId(const int& riCount, const unsigned int* const& rpiTexId);
  virtual render::ICamera* const& Camera();
  virtual render::ICanvas* const& Canvas();
  virtual render::ISpace* const& Space();

private:
  render::ICamera* m_pCamera;
  render::ICanvas* m_pCanvas;
  render::ISpace* m_pSpace;
};

} // gles
} // render
} // ac
