#pragma once

#include <rapidjson/document.h>
#include <string>
#include <map>

#include "render.h"
#include "math.h"

namespace c4g {

namespace core {
class IAsset;
}

namespace scene {

class IBuilder
{
public:
  const std::string name;

public:
  explicit IBuilder(const std::string& rsName);

public:
  virtual ~IBuilder() { ; }
};

template<typename TGoods>
class TBuilder : public IBuilder
{
public:
  explicit TBuilder(const std::string& rsName)
    : IBuilder(rsName)
  {
    ;
  }
  virtual ~TBuilder()
  {
    ;
  }

public:
  virtual bool Parser(core::IAsset* const& rpAsset, const rapidjson::Value& roConfig, TGoods& rGoods) const = 0;
};

class CGlyphBuilder : public TBuilder<render::Glyph>
{
private:
  CGlyphBuilder();

public:
  virtual bool Parser(core::IAsset* const& rpAsset, const rapidjson::Value& roConfig, render::Glyph& rGlyph) const;

public:
  static CGlyphBuilder instance;
};

class CRectFBuilder : public TBuilder<RectF>
{
private:
  CRectFBuilder();

public:
  virtual bool Parser(core::IAsset* const& rpAsset, const rapidjson::Value& roConfig, RectF& rRectF) const;

public:
  static CRectFBuilder instance;
};

class IWidget;
class CWidgetBuilder : public TBuilder<IWidget* const>
{
private:
  CWidgetBuilder();

public:
  virtual bool Parser(core::IAsset* const& rpAsset, const rapidjson::Value& roConfig, IWidget* const& rpWidget) const;

public:
  static CWidgetBuilder instance;
};

class CBuilderManager
{
  friend class IBuilder;

private:
  CBuilderManager();

private:
  void Set(const std::string& rsName, IBuilder* const& rpBuilder);

public:
  const IBuilder* const Get(const std::string& rsName) const;
  template<typename TGoods>
  const TBuilder<TGoods>* const operator[](const std::string& rsName) const
  {
    //TODO: check the type by dynamic_cast?
    return reinterpret_cast<const TBuilder<TGoods>* const>(Get(rsName));
  }

private:
  typedef std::map<std::string, IBuilder*> MBuilder;
  MBuilder m_mBuilder;

public:
  static CBuilderManager instance;
};

}
}
