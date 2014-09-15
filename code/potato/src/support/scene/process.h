#pragma once

#include "render.h"

#include "flash.h"

namespace c4g {
namespace scene {

class CProcess : public render::IProcess
{
public:
  CProcess();
  virtual ~CProcess();

public:
  void SetPos(const float& rfX, const float& rfY);

public:
  virtual bool Do(render::ITransform* const& rpTransform);

private:
  float m_fX;
  float m_fY;
};

}
}
