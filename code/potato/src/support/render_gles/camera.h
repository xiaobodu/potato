#pragma once

#include "render.h"

#include "utility/glmwrapper.h"

namespace c4g {
namespace render {
namespace gles {

  class CCamera : public ICamera
  {
  public:
    CCamera();
    virtual ~CCamera();

  public:
    virtual void Pos(const float afPos[C4G_DIM_NUM]);
    virtual void At(const float afAt[C4G_DIM_NUM]);
    virtual void Near(const float& rfNear);
    virtual void Far(const float& rfFar);

  public:
    virtual bool Tick(const float& rfDelta);
    virtual void Project();

  private:
    bool Calculate();

  private:
    glm::vec3 m_v3Pos;
    glm::vec3 m_v3At;
    bool m_bReCalculate;
    utility::glmw::Matrix4X4 m_m4x4Proj;
    float m_fNear;
    float m_fFar;
  };

}
}
}
