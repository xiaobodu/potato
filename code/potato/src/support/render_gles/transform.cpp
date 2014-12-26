#include "transform.h"

#include "utility/log.h"
#include "utility/mathematics.h"

#include <memory.h>
#if defined(CXX_GNU) || defined(BUILD_ANDROID)
#include <GLES/gl.h>
#elif defined(CXX_MSVC)
#include <Windows.h>
#include <GL/gl.h>
#endif


namespace c4g{
namespace render {
namespace gles {

CTransform& CTransform::Instance(float* const& rpfVertexData)
{
  static CTransform s_Instance;
  s_Instance.m_pVertexData = rpfVertexData;
  return s_Instance;
}

CTransform::CTransform()
  : m_pVertexData(nullptr)
{
  ;
}

CTransform::~CTransform()
{
  ;
}

void CTransform::Translate(const float& rfX, const float& rfY, const float& rfZ /*= 0.0f*/)
{
  math::Matr4x4F matr(1.0f);
  matr[C4G_MATRIX_INDEX(4, 0, 3)] = rfX;
  matr[C4G_MATRIX_INDEX(4, 1, 3)] = rfY;
  matr[C4G_MATRIX_INDEX(4, 2, 3)] = rfZ;

  glLoadMatrixf(matr.TD());
}

void CTransform::Scale(const float& rfX, const float& rfY, const float& rfZ /*= 1.0f*/)
{
  math::Matr4x4F matr(1.0f);
  matr[C4G_MATRIX_INDEX(4, 0, 0)] = rfX;
  matr[C4G_MATRIX_INDEX(4, 1, 1)] = rfY;
  matr[C4G_MATRIX_INDEX(4, 2, 2)] = rfZ;

  glLoadMatrixf(matr.TD());
}

void CTransform::Rotate(const float& rfAngle, const float& rfX, const float& rfY, const float& rfZ)
{
  math::Matr4x4F matr(1.0f);
  float c = cos(rfAngle);
  float s = sin(rfAngle);
  matr[C4G_MATRIX_INDEX(4, 0, 0)] = rfX * rfX * (1 - c) + c;
  matr[C4G_MATRIX_INDEX(4, 0, 1)] = rfX * rfY * (1 - c) - rfZ * s;
  matr[C4G_MATRIX_INDEX(4, 0, 2)] = rfX * rfZ * (1 - c) + rfY * s;

  matr[C4G_MATRIX_INDEX(4, 1, 0)] = rfY * rfX * (1 - c) + rfZ * s;
  matr[C4G_MATRIX_INDEX(4, 1, 1)] = rfY * rfY * (1 - c) + c;
  matr[C4G_MATRIX_INDEX(4, 1, 2)] = rfY * rfZ * (1 - c) - rfX * s;

  matr[C4G_MATRIX_INDEX(4, 2, 0)] = rfZ * rfX * (1 - c) - rfY * s;
  matr[C4G_MATRIX_INDEX(4, 2, 1)] = rfZ * rfY * (1 - c) + rfX * s;
  matr[C4G_MATRIX_INDEX(4, 2, 2)] = rfZ * rfZ * (1 - c) + c;

  glLoadMatrixf(matr.TD());
}

void CTransform::Free(float* const& rpfData)
{
  if (!rpfData || !m_pVertexData) return;
  ::memcpy(m_pVertexData, rpfData, sizeof(GLfloat) * 12);
}

}
}
}
