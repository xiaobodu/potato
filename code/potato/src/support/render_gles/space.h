#pragma once

#include "render.h"

#if defined(CXX_GNU) || defined(BUILD_ANDROID)
#include <GLES/gl.h>
#elif defined(CXX_MSVC)
#include <Windows.h>
#include <GL/gl.h>
#endif

namespace c4g{
namespace render {
namespace gles {

class CSpace : public ISpace
{
public:
  explicit CSpace(ICamera* const pCamera);
  virtual ~CSpace();

public:
  virtual void EffectBegin(IProcess* const& rpProcess);
  virtual void EffectEnd(IProcess* const& rpProcess);
  virtual void DrawModel(const base::Model& rModel, IProcess* const& rpProcess = NULL);

private:
  ICamera* m_pCamera;
};

}
}
}
