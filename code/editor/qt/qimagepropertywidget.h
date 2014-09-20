#pragma once

#include "qimagepropertywidget_ui.h"

#include <QtWidgets/QWidget>

namespace c4g {
namespace scene {
class IImage;
}
namespace qt {

class QImagePropertyWidget : public QWidget
{
  Q_OBJECT

public:
  QImagePropertyWidget(const QString& rsTitle, QWidget* pParent = 0);
  virtual ~QImagePropertyWidget();

public:
  const QString& GetTitle() const;
  void UpdateImage(c4g::scene::IImage* const& rpImage);

private:
  Ui::ImagePropertyWidget m_oUi;
  QString m_sTitle;
};


}
}
