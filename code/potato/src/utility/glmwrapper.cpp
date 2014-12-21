#include "glmwrapper.h"

#include <memory>

namespace c4g {
namespace utility {
namespace glmw {

  Matrix4X4::Matrix4X4()
  {
    ::memset(m_Raw, 0, sizeof(float) * EMatrix4X4SizeU * EMatrix4X4SizeV);
    ::memset(m_TRaw, 0, sizeof(float) * EMatrix4X4SizeU * EMatrix4X4SizeV);
  }

  const float* const Matrix4X4::Raw() const
  {
    return m_Raw;
  }

  const float* const Matrix4X4::TRaw()
  {
    for (uint8_t i = 0; i < EMatrix4X4SizeV; ++i)
    {
      m_TRaw[0 * EMatrix4X4SizeU + i] = m_Raw[i * EMatrix4X4SizeU + 0];
      m_TRaw[1 * EMatrix4X4SizeU + i] = m_Raw[i * EMatrix4X4SizeU + 1];
      m_TRaw[2 * EMatrix4X4SizeU + i] = m_Raw[i * EMatrix4X4SizeU + 2];
      m_TRaw[3 * EMatrix4X4SizeU + i] = m_Raw[i * EMatrix4X4SizeU + 3];
    }
    return m_TRaw;
  }

  Matrix4X4& Matrix4X4::operator<<(const glm::mat4x4& rM4X4)
  {
    for (uint8_t i = 0; i < EMatrix4X4SizeU; ++i)
    {
      m_Raw[i * EMatrix4X4SizeU + 0] = rM4X4[i].x;
      m_Raw[i * EMatrix4X4SizeU + 1] = rM4X4[i].y;
      m_Raw[i * EMatrix4X4SizeU + 2] = rM4X4[i].z;
      m_Raw[i * EMatrix4X4SizeU + 3] = rM4X4[i].w;
    }
    return *this;
  }

  const Matrix4X4& Matrix4X4::operator>>(glm::mat4x4& rM4X4) const
  {
    for (uint8_t i = 0; i < EMatrix4X4SizeU; ++i)
    {
      rM4X4[i].x = m_Raw[i * EMatrix4X4SizeU + 0];
      rM4X4[i].y = m_Raw[i * EMatrix4X4SizeU + 1];
      rM4X4[i].z = m_Raw[i * EMatrix4X4SizeU + 2];
      rM4X4[i].w = m_Raw[i * EMatrix4X4SizeU + 3];
    }
    return *this;
  }

  Matrix4X4& Matrix4X4::operator<<(const Matrix4X4Raw& rRaw)
  {
    ::memcpy(m_Raw, rRaw, sizeof(float) * EMatrix4X4SizeU * EMatrix4X4SizeV);
    return *this;
  }

  const Matrix4X4& Matrix4X4::operator>>(Matrix4X4Raw& rRaw) const
  {
    ::memcpy(rRaw, m_Raw, sizeof(float) * EMatrix4X4SizeU * EMatrix4X4SizeV);
    return *this;
  }

  void To(const glm::mat4x4& rM4X4, Matrix4X4Raw& rM4X4Raw)
  {
    for (uint8_t i = 0; i < EMatrix4X4SizeU; ++i)
    {
      rM4X4Raw[i * EMatrix4X4SizeU + 0] = rM4X4[i].x;
      rM4X4Raw[i * EMatrix4X4SizeU + 1] = rM4X4[i].y;
      rM4X4Raw[i * EMatrix4X4SizeU + 2] = rM4X4[i].z;
      rM4X4Raw[i * EMatrix4X4SizeU + 3] = rM4X4[i].w;
    }
  }

}
}
}
