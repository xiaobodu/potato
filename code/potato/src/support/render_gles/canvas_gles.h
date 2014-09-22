#pragma once

#include "render.h"

#if defined(CXX_GNU)
#include <GLES/gl.h>
#elif defined(CXX_MSVC)
#include <Windows.h>
#include <GL/gl.h>
#endif

#define RECT_VERTEX_NUM              4
#define RECT_VERTEX_FLOAT_NUM        3
#define RECT_TEXCOORD_FLOAT_NUM      2
#define RECT_INDICE_INT_NUM          6
#define RECT_INDICE_LINE_INT_NUM     4

namespace c4g{
namespace render {
namespace gles {

class CCanvas : public ICanvas
{
public:
  CCanvas();
  virtual ~CCanvas();

public:
  virtual void EffectBegin(IProcess* const& rpProcess);
  virtual void EffectEnd(IProcess* const& rpProcess);
  virtual void DrawGlyph(const base::Glyph& rGlyph, IProcess* const& rpProcess = NULL);
  virtual void DrawGlyph(const base::Glyph& rGlyph, const float& rfWidth, const float& rfHeight, IProcess* const& rpProcess = NULL);

private:
  GLfloat m_aVertex[RECT_VERTEX_NUM * RECT_VERTEX_FLOAT_NUM];
  GLfloat m_aTexCoord[RECT_VERTEX_NUM * RECT_TEXCOORD_FLOAT_NUM];
  GLubyte m_aIndice[RECT_INDICE_INT_NUM];
  GLfloat m_aVertexLine[RECT_VERTEX_NUM * RECT_VERTEX_FLOAT_NUM];
  GLubyte m_aIndiceLine[RECT_INDICE_LINE_INT_NUM];
};

}
}
}
