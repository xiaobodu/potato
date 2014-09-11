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
  float width;
  float height;

public:
  ILayout()
    : type(ELayoutType_None)
    , width(0.0f)
    , height(0.0f)
  {
    ;
  }
  virtual ~ILayout()
  {
    ;
  }

public:
  virtual void Resize(IWidget* const& rpWidget, const float& rfWidth, const float& rfHeight) const = 0;
};

class CLayout : public ILayout
{
public:
  CLayout();
  virtual ~CLayout();

public:
  virtual void Resize(IWidget* const& rpWidget, const float& rfWidth, const float& rfHeight) const;

public:
  class CBuilder : public TBuilder<ILayout* const>
  {
  public:
    CBuilder() : TBuilder<ILayout* const>("layout") { ; }
  public:
    virtual bool Do(core::IAsset* const& rpAsset, const rapidjson::Value& roConfig, ILayout* const & rpLayout) const;

  protected:
    ELayoutType Convert(const std::string& rsType) const;
  };
  static CBuilder builder;
};

}
}
