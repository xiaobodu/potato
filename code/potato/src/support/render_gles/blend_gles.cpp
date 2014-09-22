#include "blend_gles.h"

#if defined(CXX_GNU)
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
  glColor4ub(rstColor.r, rstColor.g, rstColor.b, rstColor.a);
}

}
}
}
