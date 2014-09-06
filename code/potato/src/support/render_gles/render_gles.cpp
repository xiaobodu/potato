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

static GLuint g_iTexId;
static GLubyte g_aiTexArray[4 * 4] = {
    0xFF, 0x00, 0x00, 0x88,
    0x00, 0xFF, 0x00, 0x88,
    0x00, 0x00, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF
};

void CRender::Start()
{
  glShadeModel(GL_SMOOTH);
  glClearColor(0.2f, 0.4f, 0.6f, 1.0f);
  glDepthFunc(GL_LEQUAL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

  glEnable(GL_BLEND);
  glEnable(GL_CULL_FACE);
  /// just 2d render, don't test the depth
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_DITHER);
  glEnable(GL_TEXTURE_2D);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glGenTextures(1, &g_iTexId);

  glBindTexture(GL_TEXTURE_2D, g_iTexId);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, g_aiTexArray);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
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

  Perspective(45.0f, (GLfloat) width / (GLfloat) height, 0.1f, 100.0f);
  glViewport(0, 0, width, height);
  glMatrixMode(GL_MODELVIEW);
  glFlush();

  return true;
}

GLfloat square1[] = { 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0 };
GLfloat texcoord1[] = { 0, 0, 1, 0, 0, 1, 1, 1 };
GLfloat color1[] = { 0.2, 0.2, 0.0, 1.0, 0.2, 0.0, 0.2, 1.0, 0.0, 0.7, 0.7, 1.0 };
GLfloat square2[] = { -0.5, -0.5, 0, 0, -0.5, 0, -0.5, 0, 0, 0, 0, 0 };
GLfloat color2[] = { 0.2, 0.2, 0.0, 1.0, 0.2, 1.0, 0.2, 0.0, 0.5, 0.7, 0.7, 1.0, 0.8, 0.7, 0.7, 1.0 };
GLubyte indices[] = {0, 1, 2, 2, 1, 3};
GLfloat rotate = 0.0f;

bool CRender::Render(const float& rfDelta, core::IScene* pScene)
{
  glClearColor(0.2f, 0.4f, 0.6f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();

  glTranslatef(0.0f, 0.0f, -10.0f);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  //glActiveTexture(GL_TEXTURE0);
  //glClientActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, g_iTexId);
  glTexCoordPointer(2, GL_FLOAT, 0, texcoord1);
  glVertexPointer(3, GL_FLOAT, 0, square1);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);

  rotate += rfDelta * 100.0f;
  glRotatef(rotate, 0.0f, 1.0f, 0.0f);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glColorPointer(4, GL_FLOAT, 0, color2);
  glVertexPointer(3, GL_FLOAT, 0, square2);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);

  //color2[1] += rfDelta * 1.0f; if (color2[1] > 1.0f) color2[1] -= 1.0f;
  //color2[3] += rfDelta * 0.3f; if (color2[3] > 1.0f) color2[3] = 1.0f;
  //color2[5] += rfDelta * 0.5f; if (color2[5] > 1.0f) color2[5] -= 1.0f;
  //color2[7] += rfDelta * 0.5f; if (color2[7] > 1.0f) color2[7] = 1.0f;
  //color2[9] += rfDelta * 0.5f; if (color2[9] > 1.0f) color2[7] -= 1.0f;

  return true;
}

void CRender::End()
{
  glDeleteTextures(1, &g_iTexId);
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

  //glOrtho();
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
