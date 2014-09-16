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

flash::IEffect* CEffectNone::New() const
{
  return NULL;
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
void CEffectNone::Resize(const float& rfWidth, const float& rfHeight, const float& rfDepth)
{
  ;
}
bool CEffectNone::Tick(const float& rfDelta)
{
  return false;
}
void CEffectNone::PreMake()
{
  ;
}
bool CEffectNone::Make(render::ITransform* const & rpTransform)
{
  return false;
}
void CEffectNone::PostMake()
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
