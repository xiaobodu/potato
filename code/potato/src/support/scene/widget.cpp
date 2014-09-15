#include "widget.h"

namespace c4g {
namespace scene {

CEffectNone CEffectNone::instance;
CDealDelete CDealDelete::instance;

CEffectNone::CEffectNone()
{
  ;
}
CEffectNone::~CEffectNone()
{
  ;
}

void CEffectNone::Play()
{
  ;
}
void CEffectNone::Stop()
{
  ;
}
void CEffectNone::Pause()
{
  ;
}
void CEffectNone::Continue()
{
  ;
}
bool CEffectNone::Tick(const float& rfDelta)
{
  return false;
}
void CEffectNone::Make(render::ITransform* const & rpTransform)
{
  ;
}

void CDealDelete::On(IWidget*& rpWidget) const
{
  delete rpWidget;
  rpWidget = NULL;
}

}
}
