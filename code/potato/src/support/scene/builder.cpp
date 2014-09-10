#include "builder.h"

#include "scene_base.h"
#include "asset.h"

namespace c4g {
namespace scene {

// construct the static instance about builder
CBuilderManager CBuilderManager::instance;
CGlyphBuilder CGlyphBuilder::instance;
CRectFBuilder CRectFBuilder::instance;
CWidgetBuilder CWidgetBuilder::instance;
CFileBuilder CFileBuilder::instance;



IBuilder::IBuilder(const std::string& rsName)
  : name(rsName)
{
  // register self to the manager
  CBuilderManager::instance.Set(rsName, this);
}



CGlyphBuilder::CGlyphBuilder()
  : TBuilder<render::Glyph>("glyph")
{
  ;
}

bool CGlyphBuilder::Do(core::IAsset* const& rpAsset, const rapidjson::Value& roConfig, render::Glyph& rGlyph) const
{
  const rapidjson::Value& jleft = roConfig["l"];
  assert(jleft.IsDouble());
  if (!jleft.IsDouble()) return false;
  const rapidjson::Value& jtop = roConfig["t"];
  assert(jtop.IsDouble());
  if (!jtop.IsDouble()) return false;
  const rapidjson::Value& jright = roConfig["r"];
  assert(jright.IsDouble());
  if (!jright.IsDouble()) return false;
  const rapidjson::Value& jbottom = roConfig["b"];
  assert(jbottom.IsDouble());
  if (!jbottom.IsDouble()) return false;
  const rapidjson::Value& jid = roConfig["id"];
  assert(jid.IsString());
  if (!jid.IsString()) return false;

  int width = 0;
  int height = 0;
  int id = 0;
  if (!rpAsset->FindImageInfo(jid.GetString(), width, height, id)) return false;

  rGlyph.l = static_cast<float>(jleft.GetDouble() / (width * 1.0f));
  rGlyph.r = static_cast<float>(jright.GetDouble() / (width * 1.0f));
  rGlyph.t = static_cast<float>(jtop.GetDouble() / (height * 1.0f));
  rGlyph.b = static_cast<float>(jbottom.GetDouble() / (height * 1.0f));
  return true;
}



CRectFBuilder::CRectFBuilder()
  : TBuilder<RectF>("rectf")
{
  ;
}

bool CRectFBuilder::Do(core::IAsset* const& rpAsset, const rapidjson::Value& roConfig, RectF& rRectF) const
{
  const rapidjson::Value& jleft = roConfig["l"];
  assert(jleft.IsDouble());
  if (!jleft.IsDouble()) return false;
  const rapidjson::Value& jtop = roConfig["t"];
  assert(jtop.IsDouble());
  if (!jtop.IsDouble()) return false;
  const rapidjson::Value& jright = roConfig["r"];
  assert(jright.IsDouble());
  if (!jright.IsDouble()) return false;
  const rapidjson::Value& jbottom = roConfig["b"];
  assert(jbottom.IsDouble());
  if (!jbottom.IsDouble()) return false;

  rRectF.l = static_cast<float>(jleft.GetDouble());
  rRectF.t = static_cast<float>(jtop.GetDouble());
  rRectF.r = static_cast<float>(jright.GetDouble());
  rRectF.b = static_cast<float>(jbottom.GetDouble());
  rRectF();
  return true;
}



CWidgetBuilder::CWidgetBuilder()
  : TBuilder<IWidget* const>("widget")
{
  ;
}

bool CWidgetBuilder::Do(core::IAsset* const& rpAsset, const rapidjson::Value& roConfig, IWidget* const& rpWidget) const
{
  const rapidjson::Value& jid = roConfig["id"];
  assert(jid.IsString());
  if (!jid.IsString()) return false;
  const rapidjson::Value& jrect = roConfig["dst"];
  assert(jrect.IsObject());
  if (!jrect.IsObject()) return false;
  const rapidjson::Value& jlayer = roConfig["layer"];
  assert(jlayer.IsInt());
  if (!jlayer.IsInt()) return false;
  const rapidjson::Value& jvisible = roConfig["visible"];
  assert(jvisible.IsBool());
  if (!jvisible.IsBool()) return false;

  rpWidget->id = jid.GetString();
  CRectFBuilder::instance.Do(rpAsset, jrect, rpWidget->dst);
  rpWidget->layer = jlayer.GetInt();
  rpWidget->visible = jvisible.GetBool();
  return true;
}



CFileBuilder::CFileBuilder()
  : TBuilder<rapidjson::Document>("file")
{
  ;
}

bool CFileBuilder::Do(core::IAsset* const& rpAsset, const rapidjson::Value& roConfig, rapidjson::Document& rDoc) const
{
  const rapidjson::Value& jvalue = roConfig["value"];
  assert(jvalue.IsString());
  if (!jvalue.IsString()) return false;

  std::string file_context;
  rpAsset->LoadFile(jvalue.GetString(), file_context);
  rDoc.Parse(file_context.c_str());
  return true;
}



CBuilderManager::CBuilderManager()
{
  ;
}

void CBuilderManager::Set(const std::string& rsName, IBuilder* const& rpBuilder)
{
  m_mBuilder.insert(std::make_pair(rsName, rpBuilder));
}

const IBuilder* const CBuilderManager::Get(const std::string& rsName) const
{
  MBuilder::const_iterator cit_find = m_mBuilder.find(rsName);
  if (cit_find == m_mBuilder.end()) return NULL;
  return cit_find->second;
}

}
}
