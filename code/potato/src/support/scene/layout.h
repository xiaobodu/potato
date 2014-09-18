#pragma once

#include "scene_base.h"
#include "builder.h"

namespace c4g {
namespace scene {

enum ELayoutType
{
  ELayoutType_None,
  ELayoutType_Scale,
  ELayoutType_FitIn,
  ELayoutType_FitOut,
};

class ILayout
{
public:
  ELayoutType type;

public:
  ILayout()
    : type(ELayoutType_None)
  {
    ;
  }
  virtual ~ILayout()
  {
    ;
  }

public:
  virtual void Resize(const RectF& roConfig, const RectF& roResized, IWidget* const& rpWidget) const = 0;
};

class CLayout : public ILayout
{
public:
  CLayout();
  virtual ~CLayout();

public:
  virtual void Resize(const RectF& roConfig, const RectF& roResized, IWidget* const& rpWidget) const;

public:
  static void Resize(const ELayoutType& reType, const RectF& roConfig, const RectF& roResized, IWidget* const& rpWidget);

public:
  class CBuilder : public TBuilder<ILayout* const>
  {
  public:
    CBuilder() : TBuilder<ILayout* const>("layout") { ; }
  public:
    virtual bool Do(ISceneImpl* const& rpScene, const rapidjson::Value& roConfig, ILayout* const & rpLayout) const;

  protected:
    ELayoutType Convert(const std::string& rsType) const;
  };
  static CBuilder builder;
};

}
}
