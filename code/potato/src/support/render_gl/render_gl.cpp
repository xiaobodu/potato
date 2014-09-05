#include "render_gl.h"
#include "scene.h"

#include "utility/util_log.h"

#include <cassert>
#include <GL/gl.h>
#include <GL/glu.h>

namespace ac {
namespace render {
namespace gl {

GLfloat square1[] = { 0.25, 0.25, 0.0, 0.75, 0.25, 0.0, 0.25, 0.75, 0.0, 0.75, 0.75, 0.0 };
GLfloat square2[] = { 0.0, 0.0, 1.0, 0.5, 0.0, 1.0, 0.0, 0.5, 1.0, 0.5, 0.5, 1.0 };

void drawGL()
{
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
  gluPerspective(45.0f, (GLfloat) width / (GLfloat) height, 1.0f, 100.0f);

  glMatrixMode(GL_MODELVIEW);
  glFlush();

  return true;
}

bool CRender::Render(const float& rfDeltaTime, core::IScene* pScene)
{
  glClearColor(0.2, 0.4, 0.6, 1.0);
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

  return true;
}

void CRender::End()
{
  //
}

}
}
}

bool CreateRender(ac::core::IRender*& rpRender, const ac::base::Config& roConfig)
{
  assert(rpRender == NULL);
  rpRender = new ac::render::gl::CRender(roConfig);
  return true;
}

bool DestroyRender(ac::core::IRender*& rpRender, const ac::base::Config& roConfig)
{
  assert(rpRender != NULL);
  delete rpRender;
  rpRender = NULL;
  return true;
}
