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

  CCamera::CCamera()
    : m_bReCalculate(true)
    , m_fNear(1.0f)
    , m_fFar(1000.0f)
  {
    /// set the default value
    m_v3At.x = 0.0f;
    m_v3At.y = 0.0f;
    m_v3At.z = 1.0f;
  }

  CCamera::~CCamera()
  {
    //
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
      m_bReCalculate |= (m_v3At[i] == afAt[i]);
      m_v3At[i] = afAt[i];
    }
    /// normalize
    m_v3At /= m_v3At.length();
  }

  void CCamera::Near(const float& rfNear)
  {
    if (rfNear < 0.0f) return;
    m_fNear = rfNear;
  }

  void CCamera::Far(const float& rfFar)
  {
    if (rfFar < 0.0f) return;
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

    glLoadMatrixf((float*)(*m_m4x4Proj));

    assert(GL_NO_ERROR == glGetError());
    glMatrixMode(GL_MODELVIEW);
  }

  bool CCamera::Calculate()
  {
    //
    return false;
  }

}
}
}
