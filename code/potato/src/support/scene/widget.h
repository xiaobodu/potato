#pragma once

#include "scene_base.h"
#include "builder.h"

#include <script.h>

namespace c4g {
namespace scene {

template<typename TBase>
class TWidget : public TBase, public script::AHandler
{
public:
  explicit TWidget(ISceneWithScript* const& rpScene, IWidget* const& rpParent)
    : TBase(rpScene, rpParent)
  {
    rpScene->BindScript(this);
  }
  virtual ~TWidget()
  {
    Clear();
  }

public:
  virtual void Add(IWidget* const& rpWidget)
  {
    rpWidget->parent = this;
    m_vpWidget.push_back(rpWidget);
  }
  virtual void Remove(const std::string& rsId, IDeal* const& rpDeal)
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
      rpDeal->On(widget_ptr);
      break;
    }
  }
  virtual void Clear()
  {
    if (0 >= m_vpWidget.size()) return;

    VWidgetPtr::iterator it = m_vpWidget.begin();
    VWidgetPtr::iterator it_end = m_vpWidget.end();
    for (; it != it_end; ++it)
    {
      IWidget*& widget_ref = *it;
      delete widget_ref;
    }
    m_vpWidget.clear();
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
  VWidgetPtr m_vpWidget;

public:
  template<typename TFuncPtr>
  TFuncPtr CallScript(const std::string& rsFuncName, TFuncPtr pFuncDefault)
  {
    assert(NULL != pFuncDefault);
    void* func_ptr = m_pSubstance->GetSymbol(rsFuncName);
    if (NULL == func_ptr) return pFuncDefault;
    return reinterpret_cast<TFuncPtr>(func_ptr);
  }
};

class CDealDelete : public IDeal
{
public:
  virtual void On(IWidget*& rpWidget) const;

public:
  static CDealDelete instance;
};

}
}
