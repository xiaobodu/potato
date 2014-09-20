#include "qpropertywidget.h"

#include "../editor_common.h"
#include "scene_base.h"

#include "qbasicpropertywidget.h"
#include "qrectfpropertywidget.h"

#include <QtWidgets/QLayout>

namespace c4g {
namespace qt {

QPropertyWidget::QPropertyWidget(QWidget* pParent /*= 0*/)
  : QWidget(pParent)
{
  m_oUi.setupUi(this);

  while (m_oUi.tbPropertyPages->count() > 0) m_oUi.tbPropertyPages->removeItem(0);
}

QPropertyWidget::~QPropertyWidget()
{
  ;
}

void QPropertyWidget::UpdateWidget(QTreeWidgetItem* pItem, int iColum)
{
  while (m_oUi.tbPropertyPages->count() > 0) m_oUi.tbPropertyPages->removeItem(0);

  scene::IWidget* widget = (scene::IWidget*)pItem->data(0, Qt::UserRole).value<void*>();
  if (NULL == widget) return;

  QBasicPropertyWidget* basic_widget_ptr = new QBasicPropertyWidget("Basic", this);
  basic_widget_ptr->UpdateWidget(widget);
  m_oUi.tbPropertyPages->addItem(basic_widget_ptr, basic_widget_ptr->GetTitle());
  m_oUi.tbPropertyPages->setItemEnabled(0, true);

  QRectFPropertyWidget* rectf_widget_ptr = new QRectFPropertyWidget("Dst", this);
  rectf_widget_ptr->UpdateRectF(widget->dst_config);
  m_oUi.tbPropertyPages->addItem(rectf_widget_ptr, rectf_widget_ptr->GetTitle());
  m_oUi.tbPropertyPages->setItemEnabled(1, true);
}

void QPropertyWidget::LostWidget()
{
  while (m_oUi.tbPropertyPages->count() > 0) m_oUi.tbPropertyPages->removeItem(0);

  //
}

}
}
