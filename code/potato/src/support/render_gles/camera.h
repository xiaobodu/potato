#pragma once

#include "render.h"

#include "utility/mathematics.h"

namespace c4g {
namespace render {
namespace gles {

  class CCamera : public ICamera
  {
    static const int32_t Default_Screen_Width;
    static const int32_t Default_Screen_Height;
    static const float Default_Vec3_Position[C4G_DIM_NUM];
    static const float Default_Vec3_LookAt[C4G_DIM_NUM];
    static const float Default_Near;
    static const float Default_Far;

  public:
    CCamera();
    virtual ~CCamera();

  public:
    virtual void Size(const int32_t& riWidth, const int32_t& riHeight);
    virtual void Pos(const float afPos[C4G_DIM_NUM]);
    virtual void At(const float afAt[C4G_DIM_NUM]);
    virtual void Near(const float& rfNear);
    virtual void Far(const float& rfFar);

  public:
    virtual bool Tick(const float& rfDelta);
    virtual void Project();

  public:
    virtual void View2World(const float afView[C4G_DIM_NUM], float afWorld[C4G_DIM_NUM]);
    virtual void World2View(const float afWorld[C4G_DIM_NUM], float afView[C4G_DIM_NUM]);

  private:
    bool Calculate();

  private:
    bool m_bReCalculate;
    int32_t m_iWidth;
    int32_t m_iHeight;
    math::Vect3F m_v3Pos;
    math::Vect3F m_v3At;
    math::Matr4x4F m_m4x4Proj;
    float m_fNear;
    float m_fFar;
  };

}
}
}
