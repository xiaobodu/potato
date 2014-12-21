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

/*void CRender::SetView(const int32_t& riWidth, const int32_t& riHeight, const float& rfFovy, const float& rfNear, const float& rfFar)
{
  C4G_LOG_INFO(__PRETTY_FUNCTION__);

  Ortho(static_cast<float>(riWidth), static_cast<float>(riHeight), rfFar);
  //Frustum(static_cast<float>(riWidth), static_cast<float>(riHeight), rfFovy, rfNear, rfFar);
}

void CRender::Ortho(const float& rfWidth, const float& rfHeight, const float& rfFar)
{
  C4G_LOG_INFO(__PRETTY_FUNCTION__);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  double left = 0.0 - rfWidth * 0.5;
  double right = rfWidth * 0.5;

  double top = 0.0 - rfHeight * 0.5;
  double bottom = rfHeight * 0.5;

#if defined(GL_VERSION_ES_CM_1_1)
  glOrthof(left, right, bottom, top, 0.0, rfFar);
#elif defined(GL_VERSION_1_1)
  //glOrtho(left, right, bottom, top, 0.0, rfFar);
  //glGetFloatv(GL_PROJECTION_MATRIX, m);
  float r = rfWidth * 0.5f; float l = -r;
  float b = rfHeight * 0.5f; float t = -b;
  float f = rfFar; float n = 1.0f;
  ::memset(tm, 0, sizeof(float) * 16);
  tm[0] = 2.0f / (r - l); tm[4] = 0.0f; tm[8] = 0.0f; tm[12] = -1.0f * (r + l) / (r - l);
  tm[1] = 0.0f; tm[5] = 2.0f / (t - b); tm[9] = 0.0f; tm[13] = -1.0f * (t + b) / (t - b);
  tm[2] = 0.0f; tm[6] = 0.0f; tm[10] = -2.0f / (f - n); tm[14] = -1.0f * (f + n) / (f - n);
  tm[3] = 0.0f; tm[7] = 0.0f; tm[11] = 0.0f; tm[15] = 1;
  glLoadMatrixf(tm);
  //glRotatef(120.0f, 1.0f, 0.0f, 0.0f);
#endif

  assert(GL_NO_ERROR == glGetError());
  glMatrixMode(GL_MODELVIEW);
}

void CRender::Frustum(const float& rfWidth, const float& rfHeight, const float& rfFovy, const float& rfNear, const float& rfFar)
{
  C4G_LOG_INFO(__PRETTY_FUNCTION__);

  glMatrixMode(GL_PROJECTION);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

  glLoadIdentity();

  double near_dis = (rfNear < FRUSTUM_NEAR_MIN) ? FRUSTUM_NEAR_MIN : rfNear;

  const double DEG2RAD = M_PI / 180;

  double tangent = tan(rfFovy / 2 * DEG2RAD);
  double height = near_dis * tangent;
  double width = height * (rfWidth / (rfHeight == 0.0 ? 0.01 : rfHeight));

#if defined(GL_VERSION_ES_CM_1_1)
  glFrustumf(left, right, bottom, top, near_dis, rfFar);
#elif defined(GL_VERSION_1_1)
  //glFrustum(left, right, bottom, top, near_dis, rfFar);
  //glFrustum(-10.0, 10.0, -10.0, 10.0, 0.1, 70.0);
  //glFrustum(-width, width, -height, height, near_dis, rfFar);

  SetFrustum(-width, width, -height, height, near_dis * 10, rfFar);
  glLoadMatrixf(GetTranspose());
#endif

  assert(GL_NO_ERROR == glGetError());
  glMatrixMode(GL_MODELVIEW);
}

void CRender::SetFrustum(float l, float r, float b, float t, float n, float f)
{
  m[0] = m[5] = m[10] = m[15] = 1.0f;
  m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = m[12] = m[13] = m[14] = 0.0f;
  m[0] = 2 * n / (r - l);
  m[2] = (r + l) / (r - l);
  m[5] = 2 * n / (t - b);
  m[6] = (t + b) / (t - b);
  m[10] = -(f + n) / (f - n);
  m[11] = -(2 * f * n) / (f - n);
  m[14] = -1;
  m[15] = 0;
}*/

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
