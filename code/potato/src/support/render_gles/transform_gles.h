#pragma once

#include "render.h"

/*#include <GLES/gl.h>*/

namespace c4g{
namespace render {
namespace gles {

class CTransform : public ITransform
{
public:
  static CTransform& Instance(float* const& rpfVertexData = NULL);

private:
  CTransform();
  virtual ~CTransform();

public:
  virtual void Translate(const float& rfX, const float& rfY, const float& rfZ = 0.0f);
  virtual void Scale(const float& rfX, const float& rfY, const float& rfZ = 1.0f);
  virtual void Rotate(const float& rfAngle, const float& rfX, const float& rfY, const float& rfZ);
  virtual void Free(float* const& rpfVertexData);

private:
  float* m_pVertexData;
};

}
}
}
