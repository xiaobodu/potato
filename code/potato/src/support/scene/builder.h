#pragma once

#include <rapidjson/document.h>
#include <string>
#include <map>
#include <vector>

#include "render.h"
#include "script.h"
#include "utility/mathematics.h"

namespace c4g {
namespace scene {

class ISceneImpl;

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
  virtual bool Do(ISceneImpl* const& rpScene, const rapidjson::Value& roConfig, TGoods& rGoods) const = 0;
};

class CGlyphBuilder : public TBuilder<base::Glyph>
{
private:
  CGlyphBuilder();

public:
  virtual bool Do(ISceneImpl* const& rpScene, const rapidjson::Value& roConfig, base::Glyph& rGlyph) const;

public:
  static CGlyphBuilder instance;
};

class CGlyphListBuilder : public TBuilder<std::vector<base::Glyph> >
{
private:
  CGlyphListBuilder();

public:
  virtual bool Do(ISceneImpl* const& rpScene, const rapidjson::Value& roConfig, std::vector<base::Glyph>& rGlyphList) const;

public:
  static CGlyphListBuilder instance;
};

class CRectFBuilder : public TBuilder<math::RectF>
{
private:
  CRectFBuilder();

public:
  virtual bool Do(ISceneImpl* const& rpScene, const rapidjson::Value& roConfig, math::RectF& rRectF) const;

public:
  static CRectFBuilder instance;
};

class IWidget;
class CWidgetBuilder : public TBuilder<IWidget* const>
{
private:
  CWidgetBuilder();

public:
  virtual bool Do(ISceneImpl* const& rpScene, const rapidjson::Value& roConfig, IWidget* const& rpWidget) const;

public:
  static CWidgetBuilder instance;
};

class CWidgetEffectsBuilder : public TBuilder<IWidget* const>
{
public:
  CWidgetEffectsBuilder();

public:
  virtual bool Do(ISceneImpl* const& rpScene, const rapidjson::Value& roConfig, IWidget* const& rpWidget) const;

public:
  static CWidgetEffectsBuilder instance;
};

class CFileBuilder : public TBuilder<rapidjson::Document>
{
private:
  CFileBuilder();

public:
  virtual bool Do(ISceneImpl* const& rpScene, const rapidjson::Value& roConfig, rapidjson::Document& rDoc) const;

public:
  static CFileBuilder instance;
};

class CAssetsBuilder : public TBuilder<const void* const>
{
private:
  CAssetsBuilder();

public:
  // TODO: break the render
  void BindRender(core::IRender* const& rpRender);

public:
  virtual bool Do(ISceneImpl* const& rpScene, const rapidjson::Value& roConfig, const void* const& rpPtr) const;

private:
  core::IRender* m_pRender;

public:
  static CAssetsBuilder instance;
};

class CAllWidgetBuilder : public TBuilder<IWidget* const>
{
private:
  CAllWidgetBuilder();

public:
  virtual bool Do(ISceneImpl* const& rpScene, const rapidjson::Value& roConfig, IWidget* const& rpWidget) const;

public:
  static CAllWidgetBuilder instance;
};

class CScriptBuilder : public TBuilder<script::ISubstance* const>
{
private:
  CScriptBuilder();

public:
  virtual bool Do(ISceneImpl* const& rpScene, const rapidjson::Value& roConfig, script::ISubstance* const& rpSubstance) const;

public:
  static CScriptBuilder instance;
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
