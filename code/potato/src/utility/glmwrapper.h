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
  typedef float    Matrix4X4Raw[EMatrix4X4SizeU * EMatrix4X4SizeV];

  class Matrix4X4
  {
  public:
    explicit Matrix4X4();

  public:
    const float* const Raw() const;
    const float* const TRaw();

  public:
    Matrix4X4& operator<<(const glm::mat4x4& rM4X4);
    const Matrix4X4& operator>>(glm::mat4x4& rM4X4) const;
    Matrix4X4& operator<<(const Matrix4X4Raw& rRaw);
    const Matrix4X4& operator>>(Matrix4X4Raw& rRaw) const;

  private:
    Matrix4X4Raw m_Raw;
    Matrix4X4Raw m_TRaw;
  };

  void To(const glm::mat4x4& rM4X4, Matrix4X4Raw& rM4X4Raw);

}
}
}
