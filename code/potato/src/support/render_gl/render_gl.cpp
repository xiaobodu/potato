#include "render_gl.h"

#include "utility/util_log.h"

#include <cassert>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>

namespace ac{
namespace core{

void resizeGL(int width, int height)
{
  if (height == 0)
  {
      height = 1;
  }
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
  glMatrixMode(GL_MODELVIEW);
  glFlush();
}

void drawGL()
{
  glClearColor(0.2, 0.4, 0.6, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();
  glTranslatef(-1.5f, 0.0f, -6.0f);
  glBegin(GL_TRIANGLES);
      glVertex3f(0.0f, 1.0f, 0.0f);
      glVertex3f(-1.0f, -1.0f, 0.0f);
      glVertex3f(1.0f, -1.0f, 0.0f);
  glEnd();
  glTranslatef(3.0f, 0.0f, 0.0f);
  glBegin(GL_QUADS);
      glVertex3f(-1.0f, 1.0f, 0.0f);
      glVertex3f(1.0f, 1.0f, 0.0f);
      glVertex3f(1.0f, -1.0f, 0.0f);
      glVertex3f(-1.0f, -1.0f, 0.0f);
  glEnd();
}


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
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClearDepth(1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

bool CRender::Tick(const double& rdDeltaS)
{
  drawGL();

  //utility::Log::Instance().Info("second: %f", rdDeltaS);
  //

  return true;
}

void CRender::End()
{
  //
}

void CRender::Resize(const int& riWidth, const int& riHeight)
{
  resizeGL(riWidth, riHeight);
}

}
}

bool CreateRender(ac::core::IRender*& rpRender, const ac::base::Config& roConfig)
{
  assert(rpRender == NULL);
  rpRender = new ac::core::CRender(roConfig);
  return true;
}

bool DestroyRender(ac::core::IRender*& rpRender, const ac::base::Config& roConfig)
{
  assert(rpRender != NULL);
  delete rpRender;
  rpRender = NULL;
  return true;
}
