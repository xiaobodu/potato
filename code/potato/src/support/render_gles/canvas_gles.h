#pragma once

#include "render.h"

namespace c4g{
namespace render {
namespace gles {

class CCanvas : public ICanvas
{
public:
  CCanvas();
  virtual ~CCanvas();

public:
  virtual void Draw(core::IScene*& rpScene, const Glyph*& rpGlyph) const;
  virtual void Draw(core::IScene*& rpScene, const Glyph*& rpGlyph, const float& rfWidth, const float& rfHeight) const;
};

}
}
}
