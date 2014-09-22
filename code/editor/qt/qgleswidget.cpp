#include <QtGui/QMouseEvent>

#include "render_gles.h"
#include "scene_impl.h"
#include "panel.h"

#include "qgleswidget.h"
#include "../editor_common.h"

#if defined(CXX_GNU)
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GLES/gl.h>
#elif defined(CXX_MSVC)
#include <Windows.h>
#include <GL/gl.h>
#endif
#include <cassert>
#include <unistd.h>
#include <sys/time.h>

namespace c4g {
namespace qt {

QGLESFormat QGLESFormat::instance;


QGLESFormat::QGLESFormat()
    : QGLFormat()
{
  //QGLFormat::OpenGLVersionFlags flasg = openGLVersionFlags();
}

QGLESFormat::~QGLESFormat()
{
  ;
}

QGLESContext::QGLESContext(QGLESWidget* pWidget)
    : QGLContext(QGLESFormat::instance), m_pWidget(pWidget), m_pGLConfig(NULL), m_pGLDisplay(EGL_NO_DISPLAY), m_pGLContext(EGL_NO_CONTEXT), m_pGLSurface(EGL_NO_SURFACE)
{
  ;
}

QGLESContext::~QGLESContext()
{
  ;
}

bool QGLESContext::create(const QGLContext* shareContext /*= 0*/)
{
  m_pGLDisplay = eglGetDisplay(NULL);
  assert(EGL_NO_DISPLAY != m_pGLDisplay);
  return QGLContext::create(shareContext);
}

void QGLESContext::makeCurrent()
{
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
}

void QGLESContext::doneCurrent()
{
  //QGLContext::doneCurrent();
  if (EGL_NO_DISPLAY != m_pGLDisplay)
  {
    eglMakeCurrent(m_pGLDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    if (EGL_NO_CONTEXT != m_pGLContext) eglDestroyContext(m_pGLDisplay, m_pGLContext);
    if (EGL_NO_SURFACE != m_pGLSurface) eglDestroySurface(m_pGLDisplay, m_pGLSurface);
    eglTerminate(m_pGLDisplay);
  }
}

void QGLESContext::swapBuffers() const
{
  eglSwapBuffers(m_pGLDisplay, m_pGLSurface);
}

bool QGLESContext::chooseContext(const QGLContext* shareContext /*= 0*/)
{
  return true;
}

QGLESWidget::QGLESWidget(QWidget* pParent /*= NULL*/)
  : QGLWidget(new QGLESContext(this), pParent)
  , m_fWidth(0.0f)
  , m_fHeight(0.0f)
  , second(0.0)
  , second_temp(0.0)
  , second_delta(0.0)
  , second_sleep(0.0)
  , second_per_frame_min(0.0)
{
  base::Config config;
  config._sLibrPath = LIBR_PATH;
  config._sDataPath = DATA_PATH;

  config._sConfigureFile = "config/render.json";
  m_pRender = new render::gles::CRender(config);

  config._sConfigureFile = "config/scene.json";
  m_pScene = new scene::CScene(config);
}

QGLESWidget::~QGLESWidget()
{
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
}

void QGLESWidget::initializeGL()
{
  m_pRender->Start();

  gettimeofday(&time, NULL);

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
  gettimeofday(&time, NULL);
  second_temp = second;
  second = time.tv_sec * 1.0 + time.tv_usec / 1000000.0;
  second_delta = second - second_temp;

  m_pRender->Render(second_delta, m_pScene);

  gettimeofday(&time, NULL);
  second_sleep = second_per_frame_min - (time.tv_sec * 1.0 + time.tv_usec / 1000000.0 - second);
  if (0.001 < second_sleep)
  {
    //printf("%d time: s-%f | temp-%f | delta-%f | spf-%f | sleep-%f\n", ++count, second, second_temp, second_delta, second_per_frame_min, second_sleep);
    usleep(static_cast<__useconds_t >(second_sleep * 1000000));
  }
}

}
}
