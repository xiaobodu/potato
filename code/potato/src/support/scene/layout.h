#pragma once

#include "scene_base.h"
#include "builder.h"

namespace c4g {
namespace scene {

class ILayout
{
public:
  virtual ~ILayout()
  {
    ;
  }

public:
  virtual void Resize(IWidget* const& rpWidget, const int& riWidth, const int& riHeight) = 0;
};

class CLayout : public ILayout
{
public:
  CLayout();
  virtual ~CLayout();

public:
  virtual void Resize(const int& riWidth, const int& riHeight);

public:
  class CBuilder : public TBuilder<CLayout* const>
  {
  public:
    CBuilder() : TBuilder<CLayout* const>("layout") { ; }
  public:
    virtual bool Parser(core::IAsset* const& rpAsset, const rapidjson::Value& roConfig, CLayout* const & rpLayout) const;
  };
  static CBuilder builder;
};

}
}
