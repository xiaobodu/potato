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

class IProcess
{
public:
  virtual ~IProcess() { ; }

public:
  virtual bool IsCustom() const { return false; }
  virtual void Begin(const Glyph& rGlyph) = 0;
  virtual void End() = 0;

public:
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
