#include "transform_gles.h"

#include <GLES/gl.h>
#include <memory.h>

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
  : m_pVertexData(NULL)
{
  ;
}

CTransform::~CTransform()
{
  ;
}

void CTransform::Translate(const float& rfX, const float& rfY, const float& rfZ /*= 0.0f*/)
{
  //TODO: use matrix
  //NOTE: reverse the y axis
  glTranslatef(rfX, -rfY, rfZ);
}

void CTransform::Scale(const float& rfX, const float& rfY, const float& rfZ /*= 1.0f*/)
{
  //TODO: use matrix
  glScalef(rfX, rfY, rfZ);
}

void CTransform::Rotate(const float& rfAngle, const float& rfX, const float& rfY, const float& rfZ, const float& rfAX /*= 0.0f*/, const float& rfAY /*= 0.0f*/, const float& rfAZ /*= 0.0f*/)
{
  //TODO: use matrix
  glTranslatef(rfAX, -rfAY, rfAZ);
  glRotatef(rfAngle, rfX, rfY, rfZ);
  glTranslatef(-rfAX, rfAY, -rfAZ);
}

void CTransform::Free(float* const& rpfData)
{
  if (NULL == rpfData || NULL == m_pVertexData)
  {
    return;
  }
  memcpy(m_pVertexData, rpfData, sizeof(GLfloat) * 12);
}

}
}
}
