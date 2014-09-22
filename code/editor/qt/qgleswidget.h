#pragma once

#include "input.h"
#include "scene_impl.h"

#include <QtOpenGL/QGLWidget>
#include <QtCore/QBasicTimer>

#include <EGL/egl.h>

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
  virtual void makeCurrent();
  virtual void doneCurrent();
  virtual void swapBuffers() const;

protected:
  virtual bool chooseContext(const QGLContext* shareContext = 0);

private:
  QGLESWidget* m_pWidget;
  EGLConfig m_pGLConfig;
  EGLDisplay m_pGLDisplay;
  EGLContext m_pGLContext;
  EGLSurface m_pGLSurface;
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

  timeval time;
  double second;
  double second_temp;
  double second_delta;
  double second_sleep;
  double second_per_frame_min;
};

}
}
