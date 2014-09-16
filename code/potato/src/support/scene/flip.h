#pragma once

#include "widget.h"

#include <vector>

namespace c4g {
namespace scene {

class CProcess;

class IFlip : public IWidget
{
public:
  std::vector<base::Glyph> srcs;
  int index;
  float speed;

public:
  explicit IFlip(ISceneImpl* const& rpScene, IWidget* const& rpParent)
    : IWidget(rpScene, rpParent)
    , index(0)
    , speed(0.0f)
  {
    ;
  }
  virtual ~IFlip()
  {
    ;
  }

public:
  virtual void Play() = 0;
  virtual void Stop() = 0;
  virtual void Pause() = 0;
  virtual void Continue() = 0;

public:
  static void SetIndex(IFlip* const& rpFlip, const int& riIndex)
  {
    if (0 > riIndex || riIndex >= static_cast<int>(rpFlip->srcs.size())) return;
    rpFlip->index = riIndex;
  }
};

class CFlip : public TWidget<IFlip>
{
public:
  explicit CFlip(ISceneImpl* const& rpScene, IWidget* const& rpParent);
  virtual ~CFlip();

public:
  virtual bool Tick(const float& rfDelta);
  virtual void Draw(const int& riLayer, render::ICanvas* const & rpCanvas);

public:
  virtual void Play();
  virtual void Stop();
  virtual void Pause();
  virtual void Continue();

protected:
  bool NextIndex(const float& rfDelta);

private:
  CProcess* m_pProcess;
  bool m_bPlay;
  float m_fFlipTime;

public:
  class CBuilder : public TBuilder<CFlip* const>
  {
  public:
    explicit CBuilder();

  public:
    virtual bool Do(ISceneImpl* const& rpScene, const rapidjson::Value& roConfig, CFlip* const& rpFlip) const;
  };
  static CBuilder builder;
};

}
}
