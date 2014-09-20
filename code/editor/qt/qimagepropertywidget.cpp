#include "qimagepropertywidget.h"

#include "image.h"

#include <QtWidgets/QGraphicsItem>

namespace c4g {
namespace scene {
class IImage;
}
namespace qt {

QImagePropertyWidget::QImagePropertyWidget(const QString& rsTitle, QWidget* pParent /*= 0*/)
  : QWidget(pParent)
  , m_sTitle(rsTitle)
{
  m_oUi.setupUi(this);

  //m_oUi.graphicsView->render()
}

QImagePropertyWidget::~QImagePropertyWidget()
{
  ;
}

const QString& QImagePropertyWidget::GetTitle() const
{
  return m_sTitle;
}

void QImagePropertyWidget::UpdateImage(c4g::scene::IImage* const& rpImage)
{
  //
  ;
}

}
}
