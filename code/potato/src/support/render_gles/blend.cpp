#include "blend.h"

#if defined(CXX_GNU) || defined(BUILD_ANDROID)
#include <GLES/gl.h>
#elif defined(CXX_MSVC)
#include <Windows.h>
#include <GL/gl.h>
#endif

namespace c4g{
namespace render {
namespace gles {

CBlend& CBlend::Instance()
{
  static CBlend s_Instance;
  return s_Instance;
}

CBlend::CBlend()
{
  ;
}

CBlend::~CBlend()
{
  ;
}

void CBlend::Add(const base::SColor& rsColor, const base::Color::Flags& rcFlags)
{
  //TODO:
}

void CBlend::Minus(const base::SColor& rsColor, const base::Color::Flags& rcFlags)
{
  //TODO:
  ;
}

void CBlend::Multiply(const base::SColor& rstColor, const base::Color::Flags& rcFlags)
{
  // didn't implement `glColor4ub` in Android Emulator, will report the error if call it
  //glColor4ub(rstColor.r, rstColor.g, rstColor.b, rstColor.a);

  //TODO: change the r/g/b/a of `SColor` to float?
  glColor4f(rstColor.r / (0xFF * 1.0f), rstColor.g / (0xFF * 1.0f), rstColor.b / (0xFF * 1.0f), rstColor.a / (0xFF * 1.0f));
}

}
}
}
