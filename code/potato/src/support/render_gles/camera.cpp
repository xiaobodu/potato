#include "camera.h"

#include "utility/log.h"

#include <cassert>
#include <cmath>
#if defined(CXX_GNU) || defined(BUILD_ANDROID)
#include <GLES/gl.h>
#elif defined(CXX_MSVC)
#include <windows.h>
#include <GL/gl.h>
#endif

namespace c4g {
namespace render {
namespace gles {

  const int32_t CCamera::Default_Screen_Width = 300;
  const int32_t CCamera::Default_Screen_Height = 300;
  const float CCamera::Default_Near = 1.0f;
  const float CCamera::Default_Far = 1000.0f;
  const float CCamera::Default_Vec3_Position[C4G_DIM_NUM] = { 0.0f, 0.0f, 0.0f };
  const float CCamera::Default_Vec3_LookAt[C4G_DIM_NUM] = { 0.0f, 0.0f, -1.0f };
  const float CCamera::Default_Vec3_LookUp[C4G_DIM_NUM] = { 0.0f, 1.0f, 0.0f };
  const float CCamera::Default_FOV = 45.0f;

  CCamera::CCamera()
    : m_bReCalculate(true)
    , m_eType(EProjectType_Perspective)
    , m_iWidth(Default_Screen_Width)
    , m_iHeight(Default_Screen_Height)
    , m_fNear(Default_Near)
    , m_fFar(Default_Far)
    , m_fFOV(Default_FOV)
    , m_v3Pos(Default_Vec3_Position[0], Default_Vec3_Position[1], Default_Vec3_Position[2])
    , m_v3At(Default_Vec3_LookAt[0], Default_Vec3_LookAt[1], Default_Vec3_LookAt[2])
    , m_v3Up(Default_Vec3_LookUp[0], Default_Vec3_LookUp[1], Default_Vec3_LookUp[2])
    , m_m4x4Proj(1.0f)
    , m_m4x4View(1.0f)
    , m_m4x4MVP(1.0f)
  {
    //
  }

  CCamera::~CCamera()
  {
    //
  }

  void CCamera::Type(const EProjectType& reType)
  {
    if (reType != EProjectType_Ortho && reType != EProjectType_Perspective) return;
    m_bReCalculate |= (m_eType != reType);
    m_eType = reType;
  }

  void CCamera::Size(const int32_t& riWidth, const int32_t& riHeight)
  {
    if (riWidth <= 0 || riHeight <= 0) return;

    m_bReCalculate |= (m_iWidth != riWidth);
    m_iWidth = riWidth;
    m_bReCalculate |= (m_iHeight != riHeight);
    m_iHeight = riHeight;
  }

  void CCamera::Near(const float& rfNear)
  {
    if (rfNear < 0.0f) return;
    m_bReCalculate |= (m_fNear != rfNear);
    m_fNear = rfNear;
  }

  void CCamera::Far(const float& rfFar)
  {
    if (rfFar < 0.0f) return;
    m_bReCalculate |= (m_fFar != rfFar);
    m_fFar = rfFar;
  }

  void CCamera::FOV(const float& rfFOV)
  {
    if (rfFOV <= 0.0f) return;
    m_bReCalculate |= (m_fFOV != rfFOV);
    m_fFOV = rfFOV;
  }

  void CCamera::Pos(const float afPos[C4G_DIM_NUM])
  {
    for (uint8_t i = 0; i < C4G_DIM_NUM; i++)
    {
      m_bReCalculate |= (m_v3Pos[i] != afPos[i]);
      m_v3Pos[i] = afPos[i];
    }
  }

  void CCamera::At(const float afAt[C4G_DIM_NUM])
  {
    for (uint8_t i = 0; i < C4G_DIM_NUM; i++)
    {
      m_bReCalculate |= (m_v3At[i] != afAt[i]);
      m_v3At[i] = afAt[i];
    }
    /// normalize
    m_v3At /= m_v3At.Length();
  }

  bool CCamera::Tick(const float& rfDelta)
  {
    if (!m_bReCalculate) return false;
    m_bReCalculate = false;
    return Calculate();
  }

  void CCamera::Project()
  {
    glViewport(0, 0, m_iWidth, m_iHeight);
    assert(GL_NO_ERROR == glGetError());

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glLoadMatrixf(m_m4x4Proj.TD());

    assert(GL_NO_ERROR == glGetError());

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glLoadMatrixf(m_m4x4View.TD());

    assert(GL_NO_ERROR == glGetError());
  }

  void CCamera::MVP(const float afModel[C4G_DIM_NUM], float afProj[C4G_DIM_NUM]) const
  {
    math::Vect4F pos_in_world(afModel[0], afModel[1], afModel[2], 1.0f);

    math::Vect4F res = m_m4x4MVP * pos_in_world;
    afProj[0] = res.x * m_iWidth * 0.5f;
    afProj[1] = res.y * m_iHeight * 0.5f;
    afProj[2] = Default_Near;
  }

  void CCamera::PVM(const float afProj[C4G_DIM_NUM], float afModel[C4G_DIM_NUM]) const
  {
    //
  }

  bool CCamera::Calculate()
  {
    /// calculate model-view matrix
    {
      math::Vect3F axis_z = (m_v3Pos - m_v3At).Normalize();
      math::Vect3F axis_x = (axis_z * m_v3Up).Normalize();
      math::Vect3F axis_y = (axis_x * axis_z);

      for (uint8_t i = 0; i < 3; i++) m_m4x4View[C4G_MATRIX_INDEX(4, i, 0)] = axis_x[i];
      for (uint8_t i = 0; i < 3; i++) m_m4x4View[C4G_MATRIX_INDEX(4, i, 1)] = axis_y[i];
      for (uint8_t i = 0; i < 3; i++) m_m4x4View[C4G_MATRIX_INDEX(4, i, 2)] = -axis_z[i];
      m_m4x4View[C4G_MATRIX_INDEX(4, 0, 3)] = -1.0f * axis_x.Dot(m_v3At);
      m_m4x4View[C4G_MATRIX_INDEX(4, 1, 3)] = -1.0f * axis_y.Dot(m_v3At);
      m_m4x4View[C4G_MATRIX_INDEX(4, 2, 3)] = 1.0f * axis_z.Dot(m_v3At);
    }

    /// calculate the ortho project matrix
    if (m_eType == EProjectType_Ortho)
    {
      float r = m_iWidth * 0.5f; float l = -r;
      float b = m_iHeight * -0.5f; float t = -b;
      float f = m_fFar; float n = m_fNear;

      m_m4x4Proj[C4G_MATRIX_INDEX(4, 0, 0)] = 2.0f / (r - l);
      m_m4x4Proj[C4G_MATRIX_INDEX(4, 0, 1)] = 0.0f;
      m_m4x4Proj[C4G_MATRIX_INDEX(4, 0, 2)] = 0.0f;
      m_m4x4Proj[C4G_MATRIX_INDEX(4, 0, 3)] = -1.0f * (r + l) / (r - l);

      m_m4x4Proj[C4G_MATRIX_INDEX(4, 1, 0)] = 0.0f;
      m_m4x4Proj[C4G_MATRIX_INDEX(4, 1, 1)] = 2.0f / (t - b);
      m_m4x4Proj[C4G_MATRIX_INDEX(4, 1, 2)] = 0.0f;
      m_m4x4Proj[C4G_MATRIX_INDEX(4, 1, 3)] = -1.0f * (t + b) / (t - b);

      m_m4x4Proj[C4G_MATRIX_INDEX(4, 2, 0)] = 0.0f;
      m_m4x4Proj[C4G_MATRIX_INDEX(4, 2, 1)] = 0.0f;
      m_m4x4Proj[C4G_MATRIX_INDEX(4, 2, 2)] = -2.0f / (f - n);
      m_m4x4Proj[C4G_MATRIX_INDEX(4, 2, 3)] = -1.0f * (f + n) / (f - n);

      m_m4x4Proj[C4G_MATRIX_INDEX(4, 3, 0)] = 0.0f;
      m_m4x4Proj[C4G_MATRIX_INDEX(4, 3, 1)] = 0.0f;
      m_m4x4Proj[C4G_MATRIX_INDEX(4, 3, 2)] = 0.0f;
      m_m4x4Proj[C4G_MATRIX_INDEX(4, 3, 3)] = 1.0f;
    }
    /// calculate the perspective project matrix
    else if (m_eType == EProjectType_Perspective)
    {
      float fov = m_fFOV;
      float f = m_fFar; float n = m_fNear;
      float t = tan(fov) * n; float b = -t;
      float r = t * m_iWidth / m_iHeight; float l = -r;

      m_m4x4Proj[C4G_MATRIX_INDEX(4, 0, 0)] = 2.0f * n / (r - l);
      m_m4x4Proj[C4G_MATRIX_INDEX(4, 0, 1)] = 0.0f;
      m_m4x4Proj[C4G_MATRIX_INDEX(4, 0, 2)] = (r + l) / (r - l);
      m_m4x4Proj[C4G_MATRIX_INDEX(4, 0, 3)] = 0.0f;

      m_m4x4Proj[C4G_MATRIX_INDEX(4, 1, 0)] = 0.0f;
      m_m4x4Proj[C4G_MATRIX_INDEX(4, 1, 1)] = 2.0f * n / (t - b);
      m_m4x4Proj[C4G_MATRIX_INDEX(4, 1, 2)] = (t + b) / (t - b);
      m_m4x4Proj[C4G_MATRIX_INDEX(4, 1, 3)] = 0.0f;

      m_m4x4Proj[C4G_MATRIX_INDEX(4, 2, 0)] = 0.0f;
      m_m4x4Proj[C4G_MATRIX_INDEX(4, 2, 1)] = 0.0f;
      m_m4x4Proj[C4G_MATRIX_INDEX(4, 2, 2)] = -1.0f * (f + n) / (f - n);
      m_m4x4Proj[C4G_MATRIX_INDEX(4, 2, 3)] = -2.0f * f * n / (f - n);

      m_m4x4Proj[C4G_MATRIX_INDEX(4, 3, 0)] = 0.0f;
      m_m4x4Proj[C4G_MATRIX_INDEX(4, 3, 1)] = 0.0f;
      m_m4x4Proj[C4G_MATRIX_INDEX(4, 3, 2)] = -1.0f;
      m_m4x4Proj[C4G_MATRIX_INDEX(4, 3, 3)] = 0.0f;
    }
    else
    {
      assert(0);
    }

    m_m4x4MVP = m_m4x4View * m_m4x4Proj;
    return true;
  }

}
}
}
