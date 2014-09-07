#pragma once

#include "common.h"

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
  virtual bool Render(const float& rfDeltaTime, IScene* pScene) = 0;
  virtual void End() = 0;
};

}

namespace render{

class Glyph
{
public:
  int x;
  int y;
  int w;
  int h;
  int id;

public:
  Glyph() : x(0), y(0), w(0), h(0), id(0) { ; }
  virtual ~Glyph() { ; }

public:
};

class IProcess
{
public:
  virtual ~IProcess() { ; }

public:
  virtual void Preview() = 0;
  virtual void Post() = 0;
};

class ICanvas
{
public:
  virtual ~ICanvas() { ; }

public:
  virtual void DrawGlyph(core::IScene*& rpScene, const Glyph*& rpGlyph, const IProcess* pProcess = NULL) const = 0;
  virtual void DrawGlyph(core::IScene*& rpScene, const Glyph*& rpGlyph, const float& rfWidth, const float& rfHeight, const IProcess* pProcess = NULL) const = 0;

public:
  template<class ClassProcess> void Draw(core::IScene*& rpScene, const Glyph*& rpGlyph, const IProcess* pProcess = NULL) const
  {
    ClassProcess do_Process;
    DrawGlyph(rpScene, rpGlyph, pProcess);
  }

  template<class ClassProcess> void Draw(core::IScene*& rpScene, const Glyph*& rpGlyph, const float& rfWidth, const float& rfHeight, const IProcess* pProcess = NULL) const
  {
    ClassProcess do_process;
    DrawGlyph(rpScene, rpGlyph, rfWidth, rfHeight, pProcess);
  }
};

}
}

FUNC_API_DECLARE(CreateRender, c4g::core::IRender, const c4g::base::Config);
FUNC_API_DECLARE(DestroyRender, c4g::core::IRender, const c4g::base::Config);
