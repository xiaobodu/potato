#include "render_gles.h"

#include "display/display.h"

#include "utility/util_log.h"

#include <cassert>
#include <cmath>
#include <GLES/gl.h>

namespace ac {
namespace render {

GLfloat square1[] = { 0.25, 0.25, 0.0, 0.75, 0.25, 0.0, 0.25, 0.75, 0.0, 0.75, 0.75, 0.0 };
GLfloat square2[] = { 0.0, 0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.5, 0.0, 0.5, 0.5, 0.0 };

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
  GLenum err = glGetError();
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void CRender::Resize(int iWidth, int iHeight)
{
  if (iHeight == 0)
  {
    iHeight = 1;
  }
  GLenum err = glGetError();
  glViewport(0, 0, iWidth, iHeight);
  err = glGetError();
  glMatrixMode(GL_PROJECTION);
  err = glGetError();
  glLoadIdentity();
  err = glGetError();

  glViewport(0, 0, iWidth, iHeight);
  err = glGetError();
  Perspective(45.0f, (GLfloat) iWidth / (GLfloat) iHeight, 1.0f, 100.0f);
  glMatrixMode(GL_MODELVIEW);
  err = glGetError();
  err = 0;
  //glFlush();
}

bool CRender::Tick(const double& rdDeltaS)
{
  glClearColor(0.2, 0.4, 0.6, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  glLoadIdentity();

  /*glTranslatef(0.0f, 0.0f, 6.0f);
  glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
  glVertexPointer(3, GL_FLOAT, 0, square1);
  glEnableClientState(GL_VERTEX_ARRAY);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
  glVertexPointer(3, GL_FLOAT, 0, square2);
  glEnableClientState(GL_VERTEX_ARRAY);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);*/

  //utility::Log::Instance().Info("second: %f", rdDeltaS);

  return true;
}

void CRender::End()
{
  //
}

void CRender::Perspective(double fovy, double aspect, double near, double far)
{
  GLenum err = glGetError();
  glMatrixMode(GL_PROJECTION);
  err = glGetError();
  glLoadIdentity();
  err = glGetError();

  double left, right, top, bottom;

  top = tan(M_PI * fovy * 0.5 / 360.0) * near;
  bottom = 0.0 - top;

  right = top * aspect;
  left = 0.0 - right;

  glFrustumf(left, right, top, bottom, near, far);
  err = glGetError();
  err = 0;
  //assert(GL_NO_ERROR == err);
}

}
}

bool CreateRender(ac::core::IRender*& rpRender, const ac::base::Config& roConfig)
{
  assert(rpRender == NULL);
  rpRender = new ac::render::CRender(roConfig);
  return true;
}

bool DestroyRender(ac::core::IRender*& rpRender, const ac::base::Config& roConfig)
{
  assert(rpRender != NULL);
  delete rpRender;
  rpRender = NULL;
  return true;
}
