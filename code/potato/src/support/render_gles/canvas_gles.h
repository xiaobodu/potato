#pragma once

#include "render.h"

#include <GLES/gl.h>

#define RECT_VERTEX_NUM              4
#define RECT_VERTEX_FLOAT_NUM        3
#define RECT_TEXCOORD_FLOAT_NUM      2
#define RECT_INDICE_INT_NUM          6

namespace c4g{
namespace render {
namespace gles {

class CCanvas : public ICanvas
{
public:
  CCanvas();
  virtual ~CCanvas();

public:
  virtual void EffectBegin(flash::IEffect* const& rpEffect);
  virtual void EffectEnd(flash::IEffect* const& rpEffect);
  virtual void DrawGlyph(const base::Glyph& rGlyph, flash::IEffect* const& rpEffect = NULL);
  virtual void DrawGlyph(const base::Glyph& rGlyph, const float& rfWidth, const float& rfHeight, flash::IEffect* const& rpEffect = NULL);

private:
  GLfloat m_aVertex[RECT_VERTEX_NUM * RECT_VERTEX_FLOAT_NUM];
  GLfloat m_aTexCoord[RECT_VERTEX_NUM * RECT_TEXCOORD_FLOAT_NUM];
  GLubyte m_aIndice[RECT_INDICE_INT_NUM];
};

}
}
}
