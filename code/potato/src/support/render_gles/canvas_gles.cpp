#include "canvas_gles.h"

#include "base.h"
#include "scene.h"
#include "transform_gles.h"

#include <cassert>
#include <memory.h>
#include <GLES/gl.h>

namespace c4g{
namespace render {
namespace gles {

class CGlyphProcessScope : public base::TScope<IProcess>
{
public:
  explicit CGlyphProcessScope(const Glyph& rGlyph, const float& rfWidth, const float& rfHeight, IProcess* const& rpProcess)
    : base::TScope<IProcess>(rpProcess)
  {
    if (!IsProcessCustom(m_pT))
    {
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glEnable(GL_TEXTURE_2D);
      glEnableClientState(GL_VERTEX_ARRAY);
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    }

    if (NULL != m_pT) m_pT->Begin(rGlyph);
  }

  ~CGlyphProcessScope()
  {
    if (NULL != m_pT) m_pT->End();

    if (!IsProcessCustom(m_pT))
    {
      glDisable(GL_BLEND);
      glDisable(GL_TEXTURE_2D);
      glDisableClientState(GL_VERTEX_ARRAY);
      glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }
  }
};

CCanvas::CCanvas()
{
  memset(m_aVertex, 0, sizeof(GLfloat) * RECT_VERTEX_NUM * RECT_VERTEX_FLOAT_NUM);
  memset(m_aTexCoord, 0, sizeof(GLfloat) * RECT_VERTEX_NUM * RECT_TEXCOORD_FLOAT_NUM);
  //m_aIndice = { 0, 1, 2, 2, 1, 3 };
  m_aIndice[0] = 0;
  m_aIndice[1] = 1;
  m_aIndice[2] = 2;
  m_aIndice[3] = 2;
  m_aIndice[4] = 1;
  m_aIndice[5] = 3;
}

CCanvas::~CCanvas()
{
  ;
}

void CCanvas::DrawGlyph(const Glyph& rGlyph, IProcess* const& rpProcess)
{
  DrawGlyph(rGlyph, rGlyph.r - rGlyph.l, rGlyph.b - rGlyph.t, rpProcess);
}

void CCanvas::DrawGlyph(const Glyph& rGlyph, const float& rfWidth, const float& rfHeight, IProcess* const& rpProcess)
{
  glPushMatrix();

  CGlyphProcessScope process_scope(rGlyph, rfWidth, rfHeight, rpProcess);

  m_aVertex[3] = rfWidth;
  m_aVertex[7] = -rfHeight;
  m_aVertex[9] = rfWidth;
  m_aVertex[10] = -rfHeight;

  m_aTexCoord[0] = rGlyph.l;
  m_aTexCoord[1] = rGlyph.t;
  m_aTexCoord[2] = rGlyph.r;
  m_aTexCoord[3] = rGlyph.t;
  m_aTexCoord[4] = rGlyph.l;
  m_aTexCoord[5] = rGlyph.b;
  m_aTexCoord[6] = rGlyph.r;
  m_aTexCoord[7] = rGlyph.b;

  if (NULL != rpProcess) rpProcess->Do(&CTransform::Instance(m_aVertex));

  //glActiveTexture(GL_TEXTURE0);
  glClientActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, rGlyph.id);
  glTexCoordPointer(2, GL_FLOAT, 0, m_aTexCoord);
  glVertexPointer(3, GL_FLOAT, 0, m_aVertex);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, m_aIndice);

  /*glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindTexture(GL_TEXTURE_2D, 0);*/

  glPopMatrix();
}

}
}
}
