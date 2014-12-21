#include "render_impl.h"

#include "camera.h"
#include "canvas.h"
#include "space.h"
#include "scene.h"

#include "utility/log.h"

#include <cassert>
#include <cmath>
#if defined(CXX_GNU) || defined(BUILD_ANDROID)
#include <GLES/gl.h>
#elif defined(CXX_MSVC)
#include <windows.h>
#include <GL/gl.h>
#endif

#if !defined(M_PI)
# define M_PI    3.1415926
#endif

#if !defined(FRUSTUM_NEAR_MIN)
#define FRUSTUM_NEAR_MIN    0.1
#else
#error has another min near for frustum?
#endif

namespace c4g {
namespace render {
namespace gles {

CRender::CRender()
  : m_pCamera(nullptr)
  , m_pCanvas(nullptr)
  , m_pSpace(nullptr)
{
  C4G_LOG_INFO(__PRETTY_FUNCTION__);

  m_pCamera = new CCamera();
  m_pCanvas = new CCanvas();
  m_pSpace = new CSpace();
}

CRender::~CRender()
{
  delete m_pCamera;
  m_pCamera = nullptr;
  delete m_pCanvas;
  m_pCanvas = nullptr;
  delete m_pSpace;
  m_pSpace = nullptr;

  C4G_LOG_INFO(__PRETTY_FUNCTION__);
}

bool CRender::Initialize(core::MString2Module& rmModule)
{
  //TODO:
  return true;
}

void CRender::Start()
{
  C4G_LOG_INFO(__PRETTY_FUNCTION__);

  glShadeModel(GL_SMOOTH);
  glClearColor(0.2f, 0.4f, 0.6f, 1.0f);

  //glEnable(GL_CULL_FACE);
  glEnable(GL_DITHER);
}

bool CRender::Resize(const int32_t& riWidth, const int32_t& riHeight)
{
  C4G_LOG_INFO(__PRETTY_FUNCTION__);

  m_pCamera->Size(riWidth, riHeight);

  //glViewport(0, 0, riWidth, riHeight);

  //SetView(riWidth, riHeight, 45.0f, 1.0f, 3000.0f);
  //glFlush();

  return true;
}

bool CRender::Render(const float& rfDelta, core::IScene* const& rpScene)
{
  glClearColor(0.2f, 0.4f, 0.6f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();

  static GLfloat rot = 0;
  rot += rfDelta * 10.0f;
  //glRotatef(rot, 0.0f, 1.0f, 0.0f);

  if (!!m_pCamera && m_pCamera->Tick(rfDelta)) m_pCamera->Project();
  if (!!rpScene && rpScene->Tick(rfDelta)) return rpScene->Draw(this);

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

render::ICamera* const& CRender::Camera()
{
  return m_pCamera;
}

render::ICanvas* const& CRender::Canvas()
{
  return m_pCanvas;
}

render::ISpace* const& CRender::Space()
{
  return m_pSpace;
}

}
}
}

bool CreateModule(c4g::core::IModule*& rpRender)
{
  assert(rpRender == NULL);
  if (NULL != rpRender) return false;
  rpRender = new c4g::render::gles::CRender();
  return true;
}

bool DestroyModule(c4g::core::IModule*& rpRender)
{
  assert(rpRender != NULL);
  if (NULL == rpRender) return false;
  delete rpRender;
  rpRender = NULL;
  return true;
}
