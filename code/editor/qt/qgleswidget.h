#pragma once

#include "input.h"
#include "scene_impl.h"

#include <QtOpenGL/QGLWidget>
#include <QtCore/QBasicTimer>

#if defined(CXX_GNU)
#include <EGL/egl.h>
#elif defined(CXX_MSVC)
#include <Windows.h>
#endif

namespace c4g {
namespace core {
class IRender;
class IScene;
}

namespace qt {

class QGLESFormat : public QGLFormat
{
public:
  static QGLESFormat instance;

private:
  QGLESFormat();
  virtual ~QGLESFormat();

public:
};

class QGLESWidget;
class QGLESContext : public QGLContext
{
public:
  explicit QGLESContext(QGLESWidget* widget);
  virtual ~QGLESContext();

public:
  virtual bool create(const QGLContext* shareContext = 0);

protected:
  virtual bool chooseContext(const QGLContext* shareContext = 0);

public:
  virtual void makeCurrent();
  virtual void doneCurrent();
  virtual void swapBuffers() const;

private:
  QGLESWidget* m_pWidget;
#if defined(CXX_GNU)
  EGLConfig m_pGLConfig;
  EGLDisplay m_pGLDisplay;
  EGLContext m_pGLContext;
  EGLSurface m_pGLSurface;
#elif defined(CXX_MSVC)
  HGLRC m_pRC;
  HDC m_pDC;
#endif
};

class QGLESWidget : public QGLWidget
{
  Q_OBJECT

public:
  QGLESWidget(QWidget* pParent = NULL);
  virtual ~QGLESWidget();

public Q_SLOTS:
  void ToLoadScene(QString sScenePath);

Q_SIGNALS:
  void DidLoadScene(c4g::scene::ISceneImpl*const pScene);

protected:
  void mousePressEvent(QMouseEvent *e);
  void mouseReleaseEvent(QMouseEvent *e);
  void timerEvent(QTimerEvent *e);

protected:
  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL();

private:
  core::IRender* m_pRender;
  scene::ISceneImpl* m_pScene;
  QBasicTimer timer;
  float m_fWidth;
  float m_fHeight;
  display::CInput       m_oInput;

#if defined(CXX_GNU)
  timeval time;
#elif defined(CXX_MSVC)
  SYSTEMTIME time;
#endif
  double second;
  double second_temp;
  double second_delta;
  double second_sleep;
  double second_per_frame_min;
};

}
}
