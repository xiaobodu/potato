#pragma once

#include "render.h"

namespace c4g {
namespace scene {

class IWidget;

class CProcess : public render::IProcess
{
public:
  CProcess(IWidget* const& rpWidget);
  virtual ~CProcess();

public:
  void SetPos(const float& rfX, const float& rfY);

public:
  virtual bool Do(render::ITransform* const& rpTransform);

private:
  IWidget* m_pWidget;
  float m_fX;
  float m_fY;
};

}
}