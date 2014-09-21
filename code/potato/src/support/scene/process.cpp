#include "process.h"

#include "scene_base.h"
#include "flash.h"

#include <cassert>

namespace c4g {
namespace scene {

CProcess::CProcess(IWidget* const& rpWidget)
  : m_pWidget(rpWidget), m_fX(0.0f), m_fY(0.0f)
{
  assert(NULL != rpWidget);
}
CProcess::~CProcess()
{
  ;
}

void CProcess::SetPos(const float& rfX, const float& rfY)
{
  m_fX = rfX;
  m_fY = rfY;
}

void CProcess::PreDo()
{
  m_pWidget->CurrentEffect()->PreMake();
}

bool CProcess::Do(render::ITransform* const & rpTransform)
{
  rpTransform->Translate(m_fX, m_fY);
  m_pWidget->CurrentEffect()->Make(rpTransform);
  return true;
}

bool CProcess::Do(render::IBlend* const& rpBlend)
{
  m_pWidget->CurrentEffect()->Make(rpBlend);
  return true;
}

void CProcess::PostDo()
{
  m_pWidget->CurrentEffect()->PostMake();
}

}
}
