#pragma once

#include "common.h"

#include "base.h"

namespace c4g{
namespace core{

class IScene;

class IRender
{
public:
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

struct Glyph
{
  float l;
  float r;
  float t;
  float b;
  unsigned int id;

  Glyph() : l(0), r(0), t(0), b(0), id(0) { ; }
};

class ITransform
{
public:
  virtual ~ITransform() { ; }

public:
  virtual void Translate(const float& rfX, const float& rfY, const float& rfZ = 0.0f) = 0;
  virtual void Scale(const float& rfX, const float& rfY, const float& rfZ = 1.0f) = 0;
  virtual void Rotate(const float& rfAngle, const float& rfX, const float& rfY, const float& rfZ, const float& rfAX = 0.0f, const float& rfAY = 0.0f, const float& rfAZ = 0.0f) = 0;
  /// must have four vertex, means the array have 4 * 3 float
  /// and the indices is { 0, 1, 2, 2, 1, 3 };
  virtual void Free(float* const& rpfData) = 0;
};

class IProcess
{
public:
  virtual ~IProcess() { ; }

public:
  virtual bool IsCustom() const { return false; }
  virtual void Begin(const Glyph& rGlyph) = 0;
  virtual bool Do(ITransform* const& rpTransform) = 0;
  virtual void End() = 0;
};

inline bool IsProcessCustom(IProcess* const& rpProcess)
{
  return ((NULL == rpProcess) ? false : rpProcess->IsCustom());
}

class ICanvas
{
public:
  virtual ~ICanvas() { ; }

public:
  virtual void DrawGlyph(const Glyph& rGlyph, IProcess* const& rpProcess = NULL) = 0;
  virtual void DrawGlyph(const Glyph& rGlyph, const float& rfWidth, const float& rfHeight, IProcess* const& rpProcess = NULL) = 0;
};

}
}

FUNC_API_DECLARE(CreateRender, c4g::core::IRender, const c4g::base::Config);
FUNC_API_DECLARE(DestroyRender, c4g::core::IRender, const c4g::base::Config);
