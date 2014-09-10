#pragma once

#include "scene_base.h"
#include "builder.h"

namespace c4g {
namespace scene {

template<typename TBase>
class TWidget : public TBase
{
public:
  explicit TWidget(core::IScene* const& rpScene, IWidget* const& rpParent)
    : TBase()
    , m_pScene(rpScene)
    , m_pParent(rpParent)
  {
    assert(NULL != rpScene);
  }
  virtual ~TWidget()
  {
    ;
  }

public:
  virtual core::IScene* const& Scene()
  {
    return m_pScene;
  }
  virtual const IWidget* const Parent() const
  {
    return m_pParent;
  }

private:
  core::IScene* m_pScene;
  IWidget* m_pParent;

public:
  virtual void Add(IWidget* const& rpWidget)
  {
    m_vpWidget.push_back(rpWidget);
  }
  virtual IWidget* Remove(const std::string& rsId)
  {
    IWidget* widget_ptr = NULL;
    VWidgetPtr::iterator it = m_vpWidget.begin();
    VWidgetPtr::iterator it_end = m_vpWidget.end();
    for (; it != it_end; ++it)
    {
      IWidget*& widget_ref = *it;
      if (widget_ref->id != rsId)
      {
        continue;
      }
      widget_ptr = widget_ref;
      m_vpWidget.erase(it);
      break;
    }
    return widget_ptr;
  }
  virtual int Find(const std::string& rsId) const
  {
    int index = -1;
    VWidgetPtr::const_iterator cit = m_vpWidget.begin();
    VWidgetPtr::const_iterator cit_end = m_vpWidget.end();
    for (; cit != cit_end; ++cit)
    {
      ++index;
      const IWidget* const& widget_ref = *cit;
      if (widget_ref->id != rsId)
      {
        continue;
      }
      return index;
    }
    return -1;
  }
  virtual IWidget* Get(const int& riIndex)
  {
    if (0 > riIndex || riIndex >= static_cast<int>(m_vpWidget.size()))
    {
      return NULL;
    }
    return m_vpWidget.at(riIndex);
  }

public:
  virtual void Visit(IWidget::IVisitor* const& rpVisitor)
  {
    VWidgetPtr::iterator it = m_vpWidget.begin();
    VWidgetPtr::iterator it_end = m_vpWidget.end();
    for (; it != it_end; ++it)
    {
      IWidget*& rpWidget = *it;
      rpVisitor->On(rpWidget);
    }
  }

protected:
  typedef std::vector<IWidget*> VWidgetPtr;
  VWidgetPtr m_vpWidget;

public:
  class CBuilder : public TBuilder<TBase* const>
  {
  public:
    explicit CBuilder(const std::string& rsName) : TBuilder<TBase* const>(rsName) { ; }
    virtual ~CBuilder() { ; }

  public:
    virtual bool Parser(core::IAsset* const& rpAsset, const rapidjson::Value& roConfig, TBase* const& rpWidget) const
    {
      //
      return true;
    }
  };
};

}
}
