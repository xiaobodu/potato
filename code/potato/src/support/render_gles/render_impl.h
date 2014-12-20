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
  virtual bool Resize(const int& riWidth, const int& riHeight);
  virtual bool Render(const float& rfDeltaTime, core::IScene* const& rpScene);
  virtual void End();

public:
  virtual unsigned int GenerateTexId(const int& riWidth, const int& riHeight, const unsigned char* const& rpBuffer);
  virtual void DeleteTexId(const int& riCount, const unsigned int* const& rpiTexId);
  virtual render::ICamera* const& Camera();
  virtual render::ICanvas* const& Canvas();
  virtual render::ISpace* const& Space();

private:
  void SetView(const int32_t& riWidth, const int32_t& riHeight, const float& rfFovy, const float& rfNear, const float& rfFar);
  void Ortho(const float& rfWidth, const float& rfHeight, const float& rfFar);
  void Frustum(const float& rfWidth, const float& rfHeight, const float& rfFovy, const float& rfNear, const float& rfFar);

private:
  render::ICamera* m_pCamera;
  render::ICanvas* m_pCanvas;
  render::ISpace* m_pSpace;

private:
  void SetFrustum(float l, float r, float b, float t, float n, float f);
  const float* GetTranspose();
  float m[16];
  float tm[16];
};

} // gles
} // render
} // ac
