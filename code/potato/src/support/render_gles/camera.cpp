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
  const float CCamera::Default_Vec3_Position[C4G_DIM_NUM] = { 0.0f, 0.0f, 0.0f };
  const float CCamera::Default_Vec3_LookAt[C4G_DIM_NUM] = { 0.0f, 0.0f, 1.0f };
  const float CCamera::Default_Near = 1.0f;
  const float CCamera::Default_Far = 1000.0f;

  CCamera::CCamera()
    : m_bReCalculate(true)
    , m_iWidth(Default_Screen_Width)
    , m_iHeight(Default_Screen_Height)
    , m_v3Pos(Default_Vec3_Position[0], Default_Vec3_Position[1], Default_Vec3_Position[2])
    , m_v3At(Default_Vec3_LookAt[0], Default_Vec3_LookAt[1], Default_Vec3_LookAt[2])
    , m_fNear(Default_Near)
    , m_fFar(Default_Far)
  {
    //
  }

  CCamera::~CCamera()
  {
    //
  }

  void CCamera::Size(const int32_t& riWidth, const int32_t& riHeight)
  {
    if (riWidth <= 0 || riHeight <= 0) return;

    m_bReCalculate |= (m_iWidth != riWidth);
    m_iWidth = riWidth;
    m_bReCalculate |= (m_iHeight != riHeight);
    m_iHeight = riHeight;
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

  bool CCamera::Tick(const float& rfDelta)
  {
    if (!m_bReCalculate) return false;
    m_bReCalculate = false;
    return Calculate();
  }

  void CCamera::Project()
  {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glLoadMatrixf(m_m4x4Proj.TD());

    glViewport(0, 0, m_iWidth, m_iHeight);

    assert(GL_NO_ERROR == glGetError());
    glMatrixMode(GL_MODELVIEW);
  }

  void CCamera::View2World(const float afView[C4G_DIM_NUM], float afWorld[C4G_DIM_NUM])
  {
    //
  }

  void CCamera::World2View(const float afWorld[C4G_DIM_NUM], float afView[C4G_DIM_NUM])
  {
    //
  }

  bool CCamera::Calculate()
  {
    float r = m_iWidth * 0.5f; float l = -r;
    float b = m_iHeight * 0.5f; float t = -b;
    float f = m_fFar; float n = m_fNear;

    m_m4x4Proj[0] = 2.0f / (r - l);
    m_m4x4Proj[1] = 0.0f;
    m_m4x4Proj[2] = 0.0f;
    m_m4x4Proj[3] = -1.0f * (r + l) / (r - l);

    m_m4x4Proj[4] = 0.0f;
    m_m4x4Proj[5] = 2.0f / (t - b);
    m_m4x4Proj[6] = 0.0f;
    m_m4x4Proj[7] = -1.0f * (t + b) / (t - b);

    m_m4x4Proj[8] = 0.0f;
    m_m4x4Proj[9] = 0.0f;
    m_m4x4Proj[10] = -2.0f / (f - n);
    m_m4x4Proj[11] = -1.0f * (f + n) / (f - n);

    m_m4x4Proj[12] = 0.0f;
    m_m4x4Proj[13] = 0.0f;
    m_m4x4Proj[14] = 0.0f;
    m_m4x4Proj[15] = 1.0f;
    return true;
  }

}
}
}
