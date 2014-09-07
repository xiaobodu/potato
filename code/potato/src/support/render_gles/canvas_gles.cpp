#include "canvas_gles.h"

#include "scene.h"

#include <cassert>
#include <GLES/gl.h>

namespace c4g{
namespace render {
namespace gles {

CCanvas::CCanvas()
{
  ;
}

CCanvas::~CCanvas()
{
  ;
}

void CCanvas::Draw(core::IScene*& rpScene, const Glyph*& rpGlyph) const
{
  Draw(rpScene, rpGlyph, rpGlyph->w, rpGlyph->h);
}

void CCanvas::Draw(core::IScene*& rpScene, const Glyph*& rpGlyph, const float& rfWidth, const float& rfHeight) const
{
  assert(rpScene->Check(rpGlyph));
  if (!rpScene->Check(rpGlyph))
  {
    return;
  }
  glEnable(GL_TEXTURE_2D);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  //

  glDisable(GL_TEXTURE_2D);
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

}
}
}
