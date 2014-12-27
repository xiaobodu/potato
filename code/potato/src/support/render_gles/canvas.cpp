#include "canvas.h"

#include "base.h"

#include "scene.h"
#include "transform.h"
#include "blend.h"

#include "utility/mathematics.h"

#include <cassert>
#include <memory.h>

namespace c4g{
namespace render {
namespace gles {

class CGlyphProcessScope : public base::TScope<IProcess>
{
public:
  explicit CGlyphProcessScope(const base::Glyph& rGlyph, const float& rfWidth, const float& rfHeight, IProcess* const& rpProcess)
    : base::TScope<IProcess>(rpProcess)
  {
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glPushMatrix();

    if (!!m_pT) m_pT->PreDo();
  }

  ~CGlyphProcessScope()
  {
    if (!!m_pT) m_pT->PostDo();

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisable(GL_BLEND);
  }
};

CCanvas::CCanvas(ICamera* const pCamera)
  : m_pCamera(pCamera)
{
  assert(!!pCamera);

  ::memset(m_aVertex, 0, sizeof(GLfloat) * RECT_VERTEX_NUM * RECT_VERTEX_FLOAT_NUM);
  ::memset(m_aTexCoord, 0, sizeof(GLfloat) * RECT_VERTEX_NUM * RECT_TEXCOORD_FLOAT_NUM);
  //m_aIndice = { 0, 1, 2, 2, 1, 3 };
  m_aIndice[0] = 0;
  m_aIndice[1] = 1;
  m_aIndice[2] = 2;
  m_aIndice[3] = 2;
  m_aIndice[4] = 1;
  m_aIndice[5] = 3;

  ::memset(m_aVertexLine, 0, sizeof(GLfloat) * RECT_VERTEX_NUM * RECT_VERTEX_FLOAT_NUM);
  m_aIndiceLine[0] = 0;
  m_aIndiceLine[1] = 1;
  m_aIndiceLine[2] = 2;
  m_aIndiceLine[3] = 3;
}

CCanvas::~CCanvas()
{
  ;
}

void CCanvas::EffectBegin(IProcess* const& rpProcess)
{
  //glPushMatrix();

  //if (NULL != rpProcess) rpProcess->Do(&CTransform::Instance(m_aVertex));
}

void CCanvas::EffectEnd(IProcess* const& rpProcess)
{
  //glPopMatrix();
}

void CCanvas::DrawGlyph(const base::Glyph& rGlyph, IProcess* const& rpProcess)
{
  DrawGlyph(rGlyph, rGlyph.r - rGlyph.l, rGlyph.b - rGlyph.t, rpProcess);
}

void CCanvas::DrawGlyph(const base::Glyph& rGlyph, const float& rfWidth, const float& rfHeight, IProcess* const& rpProcess)
{
  if (!m_pCamera) return;

  CGlyphProcessScope effect_scope(rGlyph, rfWidth, rfHeight, rpProcess);

  if (!!rpProcess) rpProcess->Do(&CTransform::Instance(m_aVertex));
  if (!!rpProcess) rpProcess->Do(&CBlend::Instance());

  glTranslatef(0.0f, 0.0f, -100.0f);

  // 0  1   2
  // 3  4   5
  // 6  7   8
  // 9  10  11
  m_aVertex[3] = rfWidth;
  m_aVertex[7] = -rfHeight;
  m_aVertex[9] = rfWidth;
  m_aVertex[10] = -rfHeight;

  /*float temp_vertex[C4G_DIM_NUM];
  temp_vertex[0] = m_aVertex[3];
  temp_vertex[1] = m_aVertex[4];
  temp_vertex[2] = m_aVertex[5];
  m_pCamera->MVP(temp_vertex, temp_vertex);*/

  m_aTexCoord[0] = rGlyph.l;
  m_aTexCoord[1] = rGlyph.t;
  m_aTexCoord[2] = rGlyph.r;
  m_aTexCoord[3] = rGlyph.t;
  m_aTexCoord[4] = rGlyph.l;
  m_aTexCoord[5] = rGlyph.b;
  m_aTexCoord[6] = rGlyph.r;
  m_aTexCoord[7] = rGlyph.b;

#if defined(GL_VERSION_ES_CM_1_1)
  //glActiveTexture(GL_TEXTURE0);
  glClientActiveTexture(GL_TEXTURE0);
#endif
  glBindTexture(GL_TEXTURE_2D, rGlyph.id);
  glTexCoordPointer(2, GL_FLOAT, 0, m_aTexCoord);
  glVertexPointer(3, GL_FLOAT, 0, m_aVertex);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, m_aIndice);
}

}
}
}
