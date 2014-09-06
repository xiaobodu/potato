#pragma once

#include "common.h"

#include "display.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/glx.h>

namespace c4g {
namespace display {
namespace linux_gl{

class CDisplay: public core::IDisplay
{
public:
  CDisplay(const base::Config& roConfig);
  virtual ~CDisplay();

public:
  virtual void BindRender(core::IRender*& rpRender);
  virtual void Run();

protected:
  void CreateWindow();
  void DestroyWindow();

private:
  Display* m_pDisplay;
  Window m_lWindow;

  GLXContext m_pGLContext;

  bool m_bIsRunning;
  int m_iWidth;
  int m_iHeight;

  core::IRender* m_pRender;
};

}
}
}
