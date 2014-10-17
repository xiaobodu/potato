#pragma once

#include "base.h"

#define MODULE_TYPE_RENDER    "render"

namespace c4g{
namespace core{

class IScene;

class C4G_API IRender : public IModule
{
public:
  explicit IRender()
    : IModule(MODULE_TYPE_RENDER)
  {
    ;
  }
  virtual ~IRender() { ; }

public:
  virtual void Start() = 0;
  virtual bool Resize(const int& riWidth, const int& riHeight) = 0;
  virtual bool Render(const float& rfDeltaTime, IScene* const& rpScene) = 0;
  virtual void End() = 0;

public:
  virtual unsigned int GenerateTexId(const int& riWidth, const int& riHeight, const unsigned char* const& rpBuffer) = 0;
  virtual void DeleteTexId(const int& riCount, const unsigned int* const& rpiTexId) = 0;
};

}

namespace render{

class ITransform
{
public:
  virtual ~ITransform() { ; }

public:
  virtual void Translate(const float& rfX, const float& rfY, const float& rfZ = 0.0f) = 0;
  virtual void Scale(const float& rfX, const float& rfY, const float& rfZ = 1.0f) = 0;
  virtual void Rotate(const float& rfAngle, const float& rfX, const float& rfY, const float& rfZ) = 0;
  /// must have four vertex, means the array have 4 * 3 float
  /// and the indices is { 0, 1, 2, 2, 1, 3 };
  virtual void Free(float* const& rpfData) = 0;
};

class IBlend
{
public:
  virtual ~IBlend() { ; }

public:
  virtual void Add(const base::SColor& rsColor, const base::Color::Flags& rcFlags) = 0;
  virtual void Minus(const base::SColor& rsColor, const base::Color::Flags& rcFlags) = 0;
  virtual void Multiply(const base::SColor& rsColor, const base::Color::Flags& rcFlags) = 0;
};

class IProcess
{
public:
  virtual ~IProcess() { ; }

public:
  virtual void PreDo() = 0;
  virtual bool Do(render::ITransform* const& rpTransform) = 0;
  virtual bool Do(render::IBlend* const& rpBlend) = 0;
  virtual void PostDo() = 0;
};

class ICanvas
{
public:
  virtual ~ICanvas() { ; }

public:
  virtual void EffectBegin(IProcess* const& rpProcess) = 0;
  virtual void EffectEnd(IProcess* const& rpProcess) = 0;
  virtual void DrawGlyph(const base::Glyph& rGlyph, IProcess* const& rpProcess = NULL) = 0;
  virtual void DrawGlyph(const base::Glyph& rGlyph, const float& rfWidth, const float& rfHeight, IProcess* const& rpProcess = NULL) = 0;
};

}
}
