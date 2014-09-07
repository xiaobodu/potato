#pragma once

#include "common.h"

#include "render.h"

namespace c4g {

namespace core {
class IScene;
}

namespace render {
namespace gl {

class CRender : public core::IRender
{
public:
  CRender(const base::Config& roConfig);
  virtual ~CRender();

public:
  virtual void Start();
  virtual bool Resize(const int& riWidth, const int& riHeight);
  virtual bool Render(const float& rfDelta, core::IScene* const& rpScene);
  virtual void End();

public:
  virtual unsigned int GenerateTexId(const int& riWidth, const int& riHeight, const unsigned char* const& rpBuffer);
  virtual void DeleteTexId(const int& riCount, const unsigned int* const& rpiTexId);
};

}
}
}
