#pragma once

#define GLM_SWIZZLE
#include <glm/glm.hpp>

namespace c4g {
namespace utility {
namespace glmw {

  enum
  {
    EMatrix4X4SizeU = 4,
    EMatrix4X4SizeV = 4,
  };
  typedef float    Matrix4X4Raw[EMatrix4X4SizeU][EMatrix4X4SizeV];

  class Matrix4X4
  {
  public:
    explicit Matrix4X4() { ::memset(m_Raw, 0, sizeof(float) * EMatrix4X4SizeU * EMatrix4X4SizeV); }

  public:
    const Matrix4X4Raw& operator*() const { return m_Raw; }
    Matrix4X4& operator<<(const glm::mat4x4& rM4X4)
    {
      for (uint8_t i = 0; i < EMatrix4X4SizeU; ++i)
      {
        m_Raw[i][0] = rM4X4[i].x;
        m_Raw[i][1] = rM4X4[i].y;
        m_Raw[i][2] = rM4X4[i].z;
        m_Raw[i][3] = rM4X4[i].w;
      }
      return *this;
    }
    const Matrix4X4& operator>>(glm::mat4x4& rM4X4) const
    {
      for (uint8_t i = 0; i < EMatrix4X4SizeU; ++i)
      {
        rM4X4[i].x = m_Raw[i][0];
        rM4X4[i].y = m_Raw[i][1];
        rM4X4[i].z = m_Raw[i][2];
        rM4X4[i].w = m_Raw[i][3];
      }
      return *this;
    }
    Matrix4X4& operator<<(const Matrix4X4Raw& rRaw)
    {
      ::memcpy(m_Raw, rRaw, sizeof(float) * EMatrix4X4SizeU * EMatrix4X4SizeV);
      return *this;
    }
    const Matrix4X4& operator>>(Matrix4X4Raw& rRaw) const
    {
      ::memcpy(rRaw, m_Raw, sizeof(float) * EMatrix4X4SizeU * EMatrix4X4SizeV);
      return *this;
    }

  private:
    Matrix4X4Raw m_Raw;
  };

}
}
}
