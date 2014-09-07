#include "render_gles.h"
#include "scene.h"

#include "utility/sharedlibrary.h"
#include "utility/log.h"

#include <cassert>
#include <cmath>
#include <GLES/gl.h>

namespace c4g {
namespace render {

namespace gles {

CRender::CRender(const base::Config& roConfig)
{
  utility::Log::Instance().Info(__PRETTY_FUNCTION__);
}

CRender::~CRender()
{
  utility::Log::Instance().Info(__PRETTY_FUNCTION__);
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
  utility::Log::Instance().Info(__PRETTY_FUNCTION__);

  glShadeModel(GL_SMOOTH);
  glClearColor(0.2f, 0.4f, 0.6f, 1.0f);

  // about blend
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // it is not necessary to cull the face
  //glEnable(GL_CULL_FACE);
  glEnable(GL_DITHER);
  /// just 2d render, don't test the depth
  //glEnable(GL_DEPTH_TEST);
  //glDepthFunc(GL_LEQUAL);

  // about texture
  glGenTextures(1, &g_iTexId);
  glBindTexture(GL_TEXTURE_2D, g_iTexId);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, g_aiTexArray);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

bool CRender::Resize(const int& riWidth, const int& riHeight)
{
  utility::Log::Instance().Info(__PRETTY_FUNCTION__);

  glViewport(0, 0, riWidth, riHeight);

  SetView(riWidth, riHeight, -10.0f, 10.0f);
  glFlush();

  return true;
}

GLfloat square1[]   = { 100, -100, 0,       200, -100, 0,       100, -200, 0,       200, -200, 0 };
GLfloat texcoord1[] = { 0, 0,               1, 0,               0, 1,               1, 1 };
GLfloat color1[]    = { 0.2, 0.2, 0.0, 1.0, 0.2, 0.0, 0.2, 1.0, 0.0, 0.7, 0.7, 1.0, 1.0, 1.0, 1.0, 1.0 };
GLubyte indice1[]   = { 0, 1, 2, 2, 1, 3 };

GLfloat square2[]   = { 0, -200, 0,         0, -200, 0,         0, -100, 0,         100, -100, 0 };
GLfloat color2[]    = { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 };
GLfloat rotate      = 0.0f;

bool CRender::Render(const float& rfDelta, core::IScene* pScene)
{
  glClearColor(0.2f, 0.4f, 0.6f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();

  glEnable(GL_TEXTURE_2D);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  //glActiveTexture(GL_TEXTURE0);
  //glClientActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, g_iTexId);
  glTexCoordPointer(2, GL_FLOAT, 0, texcoord1);
  glVertexPointer(3, GL_FLOAT, 0, square1);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indice1);

  glDisable(GL_TEXTURE_2D);
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);

  rotate += rfDelta * 100.0f;
  glRotatef(rotate, 0.0f, 0.0f, 1.0f);
  glEnable(GL_COLOR_MATERIAL);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  glColorPointer(4, GL_FLOAT, 0, color2);
  glVertexPointer(3, GL_FLOAT, 0, square2);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  glDisable(GL_COLOR_MATERIAL);
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);

  color2[0] += rfDelta * 1.0f; if (color2[0] > 1.0f) color2[0] -= 1.0f;
  color2[2] += rfDelta * 0.3f; if (color2[2] > 1.0f) color2[2] -= 1.0f;
  color2[5] += rfDelta * 0.5f; if (color2[5] > 1.0f) color2[5] -= 1.0f;
  color2[6] += rfDelta * 0.5f; if (color2[6] > 1.0f) color2[6] -= 1.0f;
  color2[9] += rfDelta * 0.5f; if (color2[9] > 1.0f) color2[9] -= 1.0f;

  return true;
}

void CRender::End()
{
  glDeleteTextures(1, &g_iTexId);

  utility::Log::Instance().Info(__PRETTY_FUNCTION__);
}

void CRender::SetView(const int& riWidth, const int& riHeight, const double& rdNear, const double& rdFar)
{
  utility::Log::Instance().Info(__PRETTY_FUNCTION__);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  double left = 0.0;
  double right = riWidth;

  double top = 0;
  double bottom = 0.0 - riHeight;

  glOrthof(left, right, bottom, top, rdNear, rdFar);
  assert(GL_NO_ERROR == glGetError());
  glMatrixMode(GL_MODELVIEW);
}

void CRender::Perspactive(double fovy, double aspect, double near, double far)
{
  utility::Log::Instance().Info(__PRETTY_FUNCTION__);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  double top = tan(M_PI * fovy * 0.5 / 360.0) * near;
  double bottom = 0.0 - top;

  double right = top * aspect;
  double left = 0.0 - right;

  glFrustumf(left, right, bottom, top, near, far);
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
