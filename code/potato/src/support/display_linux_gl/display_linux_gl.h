#pragma once

#include "common.h"

#include "display/display.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/glx.h>

namespace ac{
namespace display{

class CDisplay : public core::IDisplay
{
public:
  CDisplay(const ac::base::Config& roConfig);
  virtual ~CDisplay();

public:
  virtual void BindRender(core::IRender*& rpRender);
  virtual void Run();

protected:
  void CreateWindow();
  void DestroyWindow();

private:
  Display*      m_pDisplay;
  Window        m_lWindow;

  GLXContext    m_pGLContext;

  bool          m_bIsRunning;
  int           m_iWidth;
  int           m_iHeight;

  core::IRender*      m_pRender;
};

}
}

FUNC_API_DECLARE(CreateDisplay, ac::core::IDisplay, const ac::base::Config);
FUNC_API_DECLARE(DestroyDisplay, ac::core::IDisplay, const ac::base::Config);
