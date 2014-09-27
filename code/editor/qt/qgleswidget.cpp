#include <QtGui/QMouseEvent>

#include "render_gles.h"
#include "scene_impl.h"
#include "panel.h"
#include "utility/datetime.h"

#include "qgleswidget.h"
#include "../editor_common.h"

#include <cassert>
#if defined(CXX_GNU)
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GLES/gl.h>
#include <unistd.h>
#include <sys/time.h>
#elif defined(CXX_MSVC)
//#include <gl/GL.h>
#include <windowsx.h>
#include <QtGui/QWindow>
#endif

namespace c4g {
namespace qt {

QGLESFormat QGLESFormat::instance;


QGLESFormat::QGLESFormat()
    : QGLFormat()
{
  //QGLFormat::OpenGLVersionFlags flasg = openGLVersionFlags()
  setRgba(true);
  setDepth(true);
  setDoubleBuffer(true);
  setRedBufferSize(8);
  setGreenBufferSize(8);
  setBlueBufferSize(8);
  setAlphaBufferSize(8);
}

QGLESFormat::~QGLESFormat()
{
  ;
}

QGLESContext::QGLESContext(QGLESWidget* pWidget)
    : QGLContext(QGLESFormat::instance)
    , m_pWidget(pWidget)
#if defined(CXX_GNU)
    , m_pGLConfig(NULL)
    , m_pGLDisplay(EGL_NO_DISPLAY)
    , m_pGLContext(EGL_NO_CONTEXT)
    , m_pGLSurface(EGL_NO_SURFACE)
#elif defined(CXX_MSVC)
    , m_pRC(NULL)
    , m_pDC(NULL)
#endif
{
  ;
}

QGLESContext::~QGLESContext()
{
  ;
}

bool QGLESContext::create(const QGLContext* shareContext /*= 0*/)
{
#if defined(CXX_GNU)
  m_pGLDisplay = eglGetDisplay(NULL);
  assert(EGL_NO_DISPLAY != m_pGLDisplay);
#endif
  return QGLContext::create(shareContext);
}

bool QGLESContext::chooseContext(const QGLContext* shareContext /*= 0*/)
{
#if defined(CXX_GNU)
  return true;
#elif defined(CXX_MSVC)
  if (NULL == m_pWidget || NULL != m_pDC) return false;
  m_pDC = GetDC((HWND)m_pWidget->winId());
  if (NULL == m_pDC) return false;
  PIXELFORMATDESCRIPTOR pfd;
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 32;
  pfd.cRedBits = 0;
  pfd.cRedShift = 0;
  pfd.cGreenBits = 0;
  pfd.cGreenShift = 0;
  pfd.cBlueBits = 0;
  pfd.cBlueShift = 0;
  pfd.cAlphaBits = 0;
  pfd.cAlphaShift = 0;
  pfd.cAccumBits = 0;
  pfd.cAccumRedBits = 0;
  pfd.cAccumGreenBits = 0;
  pfd.cAccumBlueBits = 0;
  pfd.cAccumAlphaBits = 0;
  pfd.cDepthBits = 32;
  pfd.cStencilBits = 0;
  pfd.cAuxBuffers = 0;
  pfd.iLayerType = PFD_MAIN_PLANE;
  pfd.bReserved = 0;
  pfd.dwLayerMask = 0;
  pfd.dwVisibleMask = 0;
  pfd.dwDamageMask = 0;
  int pixel_format = ChoosePixelFormat(m_pDC, &pfd);
  if (0 == pixel_format) return false;
  if (!SetPixelFormat(m_pDC, pixel_format, &pfd)) return false;
  return true;
#endif
}

void QGLESContext::makeCurrent()
{
#if defined(CXX_GNU)
  if (EGL_NO_CONTEXT != m_pGLContext) return;

  EGLBoolean res = false;

  EGLint egl_major, egl_minor;
  res = eglInitialize(m_pGLDisplay, &egl_major, &egl_minor);
  assert(res);
  if (!res) return;

  int num_configs = 0;
  res = eglGetConfigs(m_pGLDisplay, &m_pGLConfig, 1, &num_configs);
  assert(res);

  EGLint vid = 0;
  res = eglGetConfigAttrib(m_pGLDisplay, m_pGLConfig, EGL_NATIVE_VISUAL_ID, &vid);
  assert(res);

  WId window_id = m_pWidget->winId();
  m_pGLSurface = eglCreateWindowSurface(m_pGLDisplay, m_pGLConfig, window_id, NULL);
  assert(EGL_NO_SURFACE != m_pGLSurface);

  static const EGLint ctx_attribs[] = {
  EGL_CONTEXT_CLIENT_VERSION, 1,
  EGL_NONE };
  m_pGLContext = eglCreateContext(m_pGLDisplay, m_pGLConfig, EGL_NO_CONTEXT, ctx_attribs);
  assert(EGL_NO_CONTEXT != m_pGLContext);

  //QGLContext::makeCurrent();
  eglMakeCurrent(m_pGLDisplay, m_pGLSurface, m_pGLSurface, m_pGLContext);
#elif defined(CXX_MSVC)
  if (NULL == m_pRC)
  {
    m_pRC = wglCreateContext(m_pDC);
    wglMakeCurrent(m_pDC, m_pRC);
  }
#endif
}

void QGLESContext::doneCurrent()
{
#if defined(CXX_GNU)
  //QGLContext::doneCurrent();
  if (EGL_NO_DISPLAY != m_pGLDisplay)
  {
    eglMakeCurrent(m_pGLDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    if (EGL_NO_CONTEXT != m_pGLContext) eglDestroyContext(m_pGLDisplay, m_pGLContext);
    if (EGL_NO_SURFACE != m_pGLSurface) eglDestroySurface(m_pGLDisplay, m_pGLSurface);
    eglTerminate(m_pGLDisplay);
  }
#elif defined(CXX_MSVC)
  if (NULL != m_pRC)
  {
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(m_pRC);
    m_pRC = NULL;
  }

  if (NULL != m_pWidget && NULL != m_pDC)
  {
    ReleaseDC((HWND)m_pWidget->winId(), m_pDC);
    m_pWidget = NULL;
    m_pDC = NULL;
  }
#endif
}

void QGLESContext::swapBuffers() const
{
#if defined(CXX_GNU)
  eglSwapBuffers(m_pGLDisplay, m_pGLSurface);
#elif defined(CXX_MSVC)
  if (NULL != m_pDC) SwapBuffers(m_pDC);
#endif
}

QGLESWidget::QGLESWidget(QWidget* pParent /*= NULL*/)
  : QGLWidget(new QGLESContext(this), pParent)
  , m_pRender(NULL)
  , m_pScene(NULL)
  , m_fWidth(0.0f)
  , m_fHeight(0.0f)
  , second(0.0)
  , second_temp(0.0)
  , second_delta(0.0)
  , second_sleep(0.0)
  , second_per_frame_min(0.0)
{
  c4g::base::Config config;
  config._sLibrPath = LIBR_PATH;
  config._sDataPath = DATA_PATH;

#if defined(CXX_GNU)
  config._sConfigureFile = "config/render.json";
#elif defined(CXX_MSVC)
  config._sConfigureFile = "config/render_windows_debug.json";
#endif
  m_pRender = new render::gles::CRender(config);

#if defined(CXX_GNU)
  config._sConfigureFile = "config/scene.json";
#elif defined(CXX_MSVC)
  config._sConfigureFile = "config/scene_windows_debug.json";
#endif
  m_pScene = new scene::CScene(config);
}

QGLESWidget::~QGLESWidget()
{
  doneCurrent();

  m_pScene->Unload(m_pRender);
  delete m_pScene;
  m_pScene = NULL;

  m_pRender->End();
  delete m_pRender;
  m_pRender = NULL;
}

void QGLESWidget::ToLoadScene(QString sScenePath)
{
  std::string scene_path = sScenePath.toUtf8().constData();
  m_pScene->SetDataPath(scene_path);
  m_pScene->GetPanel()->Clear();
  if (!m_pScene->Load(m_pRender, "scene/root.json")) return;
  m_pScene->Resize(m_fWidth, m_fHeight);

  DidLoadScene(m_pScene);
}

void QGLESWidget::mousePressEvent(QMouseEvent *e)
{
  ;
}

void QGLESWidget::mouseReleaseEvent(QMouseEvent *e)
{
  m_oInput.type = display::EInputType_Touch;
  m_oInput.event = display::EInputEvent_Up;
  (*m_oInput[C4G_INPUT_TOUCH_COUNT]) = 1;
  (*m_oInput[C4G_INPUT_TOUCH_X]) = static_cast<float>(e->x());
  (*m_oInput[C4G_INPUT_TOUCH_Y]) = static_cast<float>(e->y());
  (*m_oInput[C4G_INPUT_TOUCH_LEFT]) = static_cast<float>(e->globalX());
  (*m_oInput[C4G_INPUT_TOUCH_TOP]) = static_cast<float>(e->globalY());
  m_pScene->Handle(&m_oInput);
}

void QGLESWidget::timerEvent(QTimerEvent *e)
{
  paintGL();

  swapBuffers();
  //doneCurrent();
}

void QGLESWidget::initializeGL()
{
  m_pRender->Start();

#if defined(CXX_GNU)
  gettimeofday(&time, NULL);
#elif defined(CXX_MSVC)
  GetLocalTime(&time);
#endif

  timer.start(12, this);
}

void QGLESWidget::resizeGL(int w, int h)
{
  m_fWidth = static_cast<float>(w);
  m_fHeight = static_cast<float>(h);

  m_pRender->Resize(m_fWidth, m_fHeight);
  m_pScene->Resize(m_fWidth, m_fHeight);
}

void QGLESWidget::paintGL()
{
#if defined(CXX_GNU)
  gettimeofday(&time, NULL);
#elif defined(CXX_MSVC)
  GetLocalTime(&time);
#endif
  second_temp = second;

#if defined(CXX_GNU)
  second = time.tv_sec * 1.0 + time.tv_usec / 1000000.0;
#elif defined(CXX_MSVC)
  second = time::ConvertTime(time);
#endif;
  second_delta = second - second_temp;

  m_pRender->Render(second_delta, m_pScene);

#if defined(CXX_GNU)
  gettimeofday(&time, NULL);
  second_sleep = second_per_frame_min - (time.tv_sec * 1.0 + time.tv_usec / 1000000.0 - second);
#elif defined(CXX_MSVC)
  GetLocalTime(&time);
  second_sleep = second_per_frame_min - (time::ConvertTime(time) - second);
#endif
  if (0.001 < second_sleep)
  {
    //printf("%d time: s-%f | temp-%f | delta-%f | spf-%f | sleep-%f\n", ++count, second, second_temp, second_delta, second_per_frame_min, second_sleep);
#if defined(CXX_GNU)
    usleep(static_cast<__useconds_t >(second_sleep * 1000000));
#elif defined(CXX_MSVC)
    Sleep(static_cast<DWORD>(second_sleep * 1000));
#endif
  }
}

}
}
