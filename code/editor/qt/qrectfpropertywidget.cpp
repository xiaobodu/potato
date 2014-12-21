#include "qrectfpropertywidget.h"


namespace c4g {
namespace qt {

QRectFPropertyWidget::QRectFPropertyWidget(const QString& rsTitle, QWidget* pParent /*= 0*/)
  : QWidget(pParent)
  , m_sTitle(rsTitle)
  , m_Data(0.0f)
{
  m_oUi.setupUi(this);
}

QRectFPropertyWidget::~QRectFPropertyWidget()
{
  ;
}

QString QRectFPropertyWidget::GetTitle() const
{
  QString str(m_sTitle);
  str.sprintf("%s size(%.2f, %.2f)", m_sTitle.toUtf8().constData(), m_Data.w, m_Data.h);
  return str;
}

void QRectFPropertyWidget::UpdateRectF(const c4g::math::RectF& rRectF)
{
  m_Data = rRectF;

  m_oUi.dsbLeft->setValue(static_cast<float>(m_Data.l));
  m_oUi.dsbRight->setValue(static_cast<float>(m_Data.r));
  m_oUi.dsbTop->setValue(static_cast<float>(m_Data.t));
  m_oUi.dsbBottom->setValue(static_cast<float>(m_Data.b));
}

}
}
