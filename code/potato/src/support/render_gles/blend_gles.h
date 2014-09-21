#pragma once

#include "render.h"

namespace c4g{
namespace render {
namespace gles {

class CBlend : public IBlend
{
public:
  static CBlend& Instance();

private:
  CBlend();
  virtual ~CBlend();

public:
  virtual void Add(const base::SColor& rsColor, const base::Color::Flags& rcFlags);
  virtual void Minus(const base::SColor& rsColor, const base::Color::Flags& rcFlags);
  virtual void Multiply(const base::SColor& rsColor, const base::Color::Flags& rcFlags);

private:
};

}
}
}
