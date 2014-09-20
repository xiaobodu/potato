#pragma once

#include "qbasicpropertywidget_ui.h"

#include <QtWidgets/QWidget>

namespace c4g {
namespace scene {
class IWidget;
}
namespace qt {

class QBasicPropertyWidget : public QWidget
{
  Q_OBJECT

public:
  QBasicPropertyWidget(const QString& rsTitle, QWidget* pParent = 0);
  virtual ~QBasicPropertyWidget();

public:
  const QString& GetTitle() const;
  void UpdateWidget(c4g::scene::IWidget* const& rpWidget);

private:
  Ui::BasicPropertyWidget m_oUi;
  QString m_sTitle;
};


}
}
