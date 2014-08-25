#pragma once

#include "common.h"

#include "display/display.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/glx.h>

namespace ac{
namespace core{

class CDisplay : public IDisplay
{
public:
  CDisplay(const ac::base::Config& roConfig);
  virtual ~CDisplay();

public:

private:
  Display*      m_pDisplay;
  int           m_iScreen;
  Window        m_lWindow;
  XVisualInfo*  m_pVisualInfo;
  GLXContext    m_pContext;
};

}

namespace display{



}
}

FUNC_API_DECLARE(CreateDisplay, ac::core::IDisplay, const ac::base::Config);
FUNC_API_DECLARE(DestroyDisplay, ac::core::IDisplay, const ac::base::Config);
