#include "render_gl.h"
#include "scene.h"

#include "utility/sharedlibrary.h"
#include "utility/log.h"

#include <cassert>
#include <GL/gl.h>
#include <GL/glu.h>

namespace c4g {
namespace render {
namespace gl {

GLfloat square1[] = { 0.25, 0.25, 0.0, 0.75, 0.25, 0.0, 0.25, 0.75, 0.0, 0.75, 0.75, 0.0 };
GLfloat square2[] = { 0.0, 0.0, 1.0, 0.5, 0.0, 1.0, 0.0, 0.5, 1.0, 0.5, 0.5, 1.0 };

CRender::CRender(const base::Config& roConfig)
{
  utility::Log::Instance().Info(__PRETTY_FUNCTION__);
}

CRender::~CRender()
{
  utility::Log::Instance().Info(__PRETTY_FUNCTION__);
}

void CRender::Start()
{
  utility::Log::Instance().Info(__PRETTY_FUNCTION__);

  glShadeModel(GL_SMOOTH);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClearDepth(1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

bool CRender::Resize(const int& riWidth, const int& riHeight)
{
  utility::Log::Instance().Info(__PRETTY_FUNCTION__);

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

bool CRender::Render(const float& rfDelta, core::IScene* const& rpScene)
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

  if (NULL != rpScene && rpScene->Tick(rfDelta))
  {
    //TODO:
    rpScene->Draw(NULL);
  }

  return true;
}

void CRender::End()
{
  utility::Log::Instance().Info(__PRETTY_FUNCTION__);
}

unsigned int CRender::GenerateTexId(const int& riWidth, const int& riHeight, const unsigned char* const& rpBuffer)
{
  unsigned int tex_id = 0;
  glGenTextures(1, &tex_id);
  glBindTexture(GL_TEXTURE_2D, tex_id);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, riWidth, riHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, rpBuffer);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  return 0;
}

void CRender::DeleteTexId(const int& riCount, const unsigned int* const& rpiTexId)
{
  glDeleteTextures(riCount, rpiTexId);
}

}
}
}

bool CreateRender(c4g::core::IRender*& rpRender, const c4g::base::Config& roConfig)
{
  assert(rpRender == NULL);
  rpRender = new c4g::render::gl::CRender(roConfig);
  return true;
}

bool DestroyRender(c4g::core::IRender*& rpRender, const c4g::base::Config& roConfig)
{
  assert(rpRender != NULL);
  delete rpRender;
  rpRender = NULL;
  return true;
}
