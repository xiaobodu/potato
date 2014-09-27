#include "render_gles.h"

#include "scene.h"
#include "canvas_gles.h"

#include "utility/log.h"

#include <cassert>
#include <cmath>
#if defined(CXX_GNU)
#include <GLES/gl.h>
#elif defined(CXX_MSVC)
#include <GL/gl.h>
#endif

#if !defined(M_PI)
# define M_PI    3.1415926
#endif

namespace c4g {
namespace render {
namespace gles {

CRender::CRender(const base::Config& roConfig)
  : m_pCanvas(NULL)
{
  C4G_LOG_INFO(__PRETTY_FUNCTION__);

  m_pCanvas = new CCanvas();
}

CRender::~CRender()
{
  delete m_pCanvas;
  m_pCanvas = NULL;

  C4G_LOG_INFO(__PRETTY_FUNCTION__);
}

void CRender::Start()
{
  C4G_LOG_INFO(__PRETTY_FUNCTION__);

  GLenum err = glGetError();
  const GLubyte* err_msg = glGetString(err);
  //assert(GL_NO_ERROR == glGetError());
  glShadeModel(GL_SMOOTH);
  err = glGetError();
  //assert(GL_NO_ERROR == glGetError());
  glClearColor(0.2f, 0.4f, 0.6f, 1.0f);
  err = glGetError();
  //assert(GL_NO_ERROR == glGetError());

  // it is not necessary to cull the face
  //glEnable(GL_CULL_FACE);
  glEnable(GL_DITHER);
  err = glGetError();
  //assert(GL_NO_ERROR == glGetError());
  /// just 2d render, don't test the depth
  //glEnable(GL_DEPTH_TEST);
  //glDepthFunc(GL_LEQUAL);
  //glEnable(GL_BLEND);
}

bool CRender::Resize(const int& riWidth, const int& riHeight)
{
  C4G_LOG_INFO(__PRETTY_FUNCTION__);

  glViewport(0, 0, riWidth, riHeight);

  SetView(riWidth, riHeight, -1000.0f, 1000.0f);
  //glFlush();

  return true;
}

bool CRender::Render(const float& rfDelta, core::IScene* const& rpScene)
{
  glClearColor(0.2f, 0.4f, 0.6f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();

  if (NULL != rpScene && rpScene->Tick(rfDelta))
  {
    return rpScene->Draw(m_pCanvas);
  }

  return false;
}

void CRender::End()
{
  C4G_LOG_INFO(__PRETTY_FUNCTION__);
}

unsigned int CRender::GenerateTexId(const int& riWidth, const int& riHeight, const unsigned char* const& rpBuffer)
{
  unsigned int tex_id = 0;
  glGenTextures(1, &tex_id);
  glBindTexture(GL_TEXTURE_2D, tex_id);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, riWidth, riHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, rpBuffer);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  return tex_id;
}

void CRender::DeleteTexId(const int& riCount, const unsigned int* const& rpiTexId)
{
  glDeleteTextures(riCount, rpiTexId);
}

void CRender::SetView(const int& riWidth, const int& riHeight, const double& rdNear, const double& rdFar)
{
  C4G_LOG_INFO(__PRETTY_FUNCTION__);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  double left = 0.0;
  double right = riWidth;

  double top = 0;
  double bottom = 0.0 - riHeight;

#if defined(GL_VERSION_ES_CM_1_1)
  glOrthof(left, right, bottom, top, rdNear, rdFar);
#elif defined(GL_VERSION_1_1)
  glOrtho(left, right, bottom, top, rdNear, rdFar);
#endif

  assert(GL_NO_ERROR == glGetError());
  glMatrixMode(GL_MODELVIEW);
}

void CRender::Perspactive(const double& rdFovy, const double& rdAspect, const double& rdNear, const double& rdFar)
{
  C4G_LOG_INFO(__PRETTY_FUNCTION__);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  double top = tan(M_PI * rdFovy * 0.5 / 360.0) * rdNear;
  double bottom = 0.0 - top;

  double right = top * rdAspect;
  double left = 0.0 - right;

#if defined(GL_VERSION_ES_CM_1_1)
  glFrustumf(left, right, bottom, top, rdNear, rdFar);
#elif defined(GL_VERSION_1_1)
  glFrustum(left, right, bottom, top, rdNear, rdFar);
#endif

  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  assert(GL_NO_ERROR == glGetError());
  glMatrixMode(GL_MODELVIEW);
}

}
}
}

bool CreateRender(c4g::core::IRender*& rpRender, const c4g::base::Config& roConfig)
{
  assert(rpRender == NULL);
  if (NULL != rpRender) return false;
  rpRender = new c4g::render::gles::CRender(roConfig);
  return true;
}

bool DestroyRender(c4g::core::IRender*& rpRender, const c4g::base::Config& roConfig)
{
  assert(rpRender != NULL);
  if (NULL == rpRender) return false;
  delete rpRender;
  rpRender = NULL;
  return true;
}
