#pragma once

#include "scene_base.h"
#include "builder.h"

#include "flash.h"
#include "script.h"

namespace c4g {

namespace display {
class IInput;
class ISensor;
}

namespace scene {

class CEffectNone : public flash::IEffect
{
public:
  static CEffectNone instance;

private:
  CEffectNone();
  virtual ~CEffectNone();

public:
  virtual void Play();
  virtual void Stop();
  virtual void Pause();
  virtual void Continue();
  virtual bool Tick(const float& rfDelta);
  virtual void Make(render::ITransform* const& rpTransform);
};

template<typename TBase>
class TWidget : public TBase, public script::AHandler
{
public:
  explicit TWidget(ISceneImpl* const& rpScene, IWidget* const& rpParent)
    : TBase(rpScene, rpParent)
    , m_pCurrentEffect(NULL)
  {
    assert(NULL != rpScene);
    rpScene->BindScript(this);
  }
  virtual ~TWidget()
  {
    Clear();
  }

public:
  virtual void Resize(const float& rfWidth, const float& rfHeight) { ; }
  virtual bool Handle(const int& riLayer, const display::IInput* const& rpInput) { return false; }
  virtual bool Refresh(const int& riLayer, const display::ISensor* const & rpSensor) { return false; }

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

  /// effect
public:
  typedef std::map<std::string, base::TPtrScope<flash::IEffect> > MEffects;
  virtual void PushEffect(const std::string& rsName, flash::IEffect* const& rpEffect)
  {
    ///  check the effect map
    MEffects::const_iterator cit_find = m_mEffect.find(rsName);
    if (cit_find != m_mEffect.end()) return;
    m_mEffect.insert(std::make_pair(rsName, base::TPtrScope<flash::IEffect>()));
    m_mEffect[rsName] = rpEffect;
  }
  virtual flash::IEffect* const CurrentEffect()
  {
    if (NULL == m_pCurrentEffect) return &CEffectNone::instance;
    return m_pCurrentEffect;
  }
  virtual void PlayEffect(const std::string& rsName, const bool& rbForce = false)
  {
    if (!rbForce && NULL != m_pCurrentEffect) return;
    m_pCurrentEffect = NULL;

    MEffects::iterator it_find = m_mEffect.find(rsName);
    if (it_find == m_mEffect.end()) return;
    m_pCurrentEffect = *((*it_find).second);
    if (NULL == m_pCurrentEffect) return;
    m_pCurrentEffect->Play();
  }
  virtual void StopEffect()
  {
    if (NULL == m_pCurrentEffect) return;
    m_pCurrentEffect->Stop();
    m_pCurrentEffect = NULL;
  }
  virtual void PauseEffect()
  {
    if (NULL == m_pCurrentEffect) return;
    m_pCurrentEffect->Pause();
  }
  virtual void ContinueEffect()
  {
    if (NULL == m_pCurrentEffect) return;
    m_pCurrentEffect->Continue();
  }
protected:
  MEffects  m_mEffect;
  flash::IEffect* m_pCurrentEffect;

  /// script
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
