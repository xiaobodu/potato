#pragma once

#include "scene_base.h"

#include "qrectfpropertywidget_ui.h"

#include <QtWidgets/QWidget>

namespace c4g {
namespace qt {

class QRectFPropertyWidget : public QWidget
{
  Q_OBJECT

public:
  QRectFPropertyWidget(const QString& rsTitle, QWidget* pParent = 0);
  virtual ~QRectFPropertyWidget();

public:
  QString GetTitle() const;
  void UpdateRectF(const c4g::scene::RectF& rRectF);

private:
  Ui::RectFPropertyWidget m_oUi;
  QString m_sTitle;
  c4g::scene::RectF m_Data;
};

}
}
