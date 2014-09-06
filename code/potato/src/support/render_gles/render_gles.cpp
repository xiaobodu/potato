#include "render_gles.h"
#include "scene.h"

#include "utility/util_log.h"

#include <cassert>
#include <cmath>
#include <GLES/gl.h>

namespace c4g {
namespace render {

namespace gles {

CRender::CRender(const base::Config& roConfig)
{
  ;
}

CRender::~CRender()
{
  ;
}

void CRender::Start()
{
  glShadeModel(GL_SMOOTH);
  glClearColor(0.2f, 0.4f, 0.6f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

  /*GLuint tex;
  glGenTextures(1, &tex);
  glBindTexture(GL_TEXTURE_2D, tex);
  //
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);*/
}

bool CRender::Resize(const int& riWidth, const int& riHeight)
{
  int width = riWidth;
  int height = riHeight;
  if (height == 0)
  {
    height = 1;
  }
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glViewport(0, 0, width, height);
  Perspective(45.0f, (GLfloat) width / (GLfloat) height, 1.0f, 100.0f);
  glMatrixMode(GL_MODELVIEW);
  //glFlush();

  return true;
}

GLfloat square1[] = { 0.25, 0.25, 0.0, 0.75, 0.25, 0.0, 0.25, 0.75, 0.0, 0.75, 0.75, 0.0 };
GLfloat square2[] = { 0.0, 0.0, 1.0, 0.5, 0.0, 1.0, 0.0, 0.5, 1.0, 0.5, 0.5, 1.0 };

bool CRender::Render(const float& rfDelta, core::IScene* pScene)
{
  glClearColor(0.2f, 0.4f, 0.6f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  glLoadIdentity();

  glTranslatef(0.0f, 0.0f, -6.0f);
  glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
  glVertexPointer(3, GL_FLOAT, 0, square1);
  glEnableClientState(GL_VERTEX_ARRAY);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
  glVertexPointer(3, GL_FLOAT, 0, square2);
  glEnableClientState(GL_VERTEX_ARRAY);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  //utility::Log::Instance().Info("second: %f", rfDelta);

  return true;
}

void CRender::End()
{
  //
}

void CRender::Perspective(double fovy, double aspect, double near, double far)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  double top = tan(M_PI * fovy * 0.5 / 360.0) * near;
  double bottom = 0.0 - top;

  double right = top * aspect;
  double left = 0.0 - right;

  glFrustumf(left, right, bottom, top, near, far);
  assert(GL_NO_ERROR == glGetError());
}

}
}
}

bool CreateRender(c4g::core::IRender*& rpRender, const c4g::base::Config& roConfig)
{
  assert(rpRender == NULL);
  rpRender = new c4g::render::gles::CRender(roConfig);
  return true;
}

bool DestroyRender(c4g::core::IRender*& rpRender, const c4g::base::Config& roConfig)
{
  assert(rpRender != NULL);
  delete rpRender;
  rpRender = NULL;
  return true;
}
