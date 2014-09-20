#include "qbasicpropertywidget.h"

#include "scene_base.h"

namespace c4g {
namespace qt {

QBasicPropertyWidget::QBasicPropertyWidget(const QString& rsTitle, QWidget* pParent /*= 0*/)
  : QWidget(pParent)
  , m_sTitle(rsTitle)
{
  m_oUi.setupUi(this);
}

QBasicPropertyWidget::~QBasicPropertyWidget()
{
  ;
}

const QString& QBasicPropertyWidget::GetTitle() const
{
  return m_sTitle;
}

void QBasicPropertyWidget::UpdateWidget(c4g::scene::IWidget* const& rpWidget)
{
  m_oUi.leId->setText(rpWidget->id.c_str());
  m_oUi.leClass->setText(rpWidget->class_name.c_str());
  m_oUi.sbLayer->setValue(rpWidget->layer);
  m_oUi.cbVisible->setChecked(rpWidget->visible);
  m_oUi.cbResize->setChecked(rpWidget->resize);
  m_oUi.cbAlwayTick->setChecked(rpWidget->always_tick);
  m_oUi.cbInput->setChecked(rpWidget->input);
  m_oUi.cbSensor->setChecked(rpWidget->sensor);
}

}
}
