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
    static const float Default_Near;
    static const float Default_Far;
    static const float Default_FOV;
    static const float Default_Vec3_Position[C4G_DIM_NUM];
    static const float Default_Vec3_LookAt[C4G_DIM_NUM];
    static const float Default_Vec3_LookUp[C4G_DIM_NUM];

  public:
    CCamera();
    virtual ~CCamera();

  public:
    virtual void Type(const EProjectType& reType);
    virtual void Size(const int32_t& riWidth, const int32_t& riHeight);
    virtual void Near(const float& rfNear);
    virtual void Far(const float& rfFar);
    virtual void FOV(const float& rfFOV);
    virtual void Pos(const float afPos[C4G_DIM_NUM]);
    virtual void At(const float afAt[C4G_DIM_NUM]);

  public:
    virtual bool Tick(const float& rfDelta);
    virtual void Project();

  public:
    virtual void MVP(const float afModel[C4G_DIM_NUM], float afProj[C4G_DIM_NUM]) const;
    virtual void PVM(const float afProj[C4G_DIM_NUM], float afModel[C4G_DIM_NUM]) const;

  private:
    bool Calculate();

  private:
    bool m_bReCalculate;
    EProjectType m_eType;
    int32_t m_iWidth;
    int32_t m_iHeight;
    float m_fNear;
    float m_fFar;
    float m_fFOV;
    math::Vect3F m_v3Pos;
    math::Vect3F m_v3At;
    math::Vect3F m_v3Up;
    math::Matr4x4F m_m4x4Proj;
    math::Matr4x4F m_m4x4View;
    math::Matr4x4F m_m4x4MVP;
  };

}
}
}
