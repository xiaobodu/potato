#pragma once

#include "common.h"

#include "display.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/glx.h>

namespace c4g {
namespace core {
class IRender;
class IScene;
}
namespace utility{
class CSharedLibraryManager;
}

namespace display {
namespace linux_gl{

class CDisplay: public core::IDisplay
{
public:
  CDisplay(const base::Config& roConfig);
  virtual ~CDisplay();

public:
  virtual void Run(core::IScene* const& rpScene);

protected:
  void CreateWindow();
  void DestroyWindow();

private:
  Display* m_pDisplay;
  Window m_lWindow;

  GLXContext m_pGLContext;

  bool m_bIsRunning;

  std::string m_sTitle;
  int m_iWidth;
  int m_iHeight;

  base::Config          m_oConfigRender;
  core::IRender*        m_pRender;
  utility::CSharedLibraryManager* m_pLibraryManager;
};

}
}
}
