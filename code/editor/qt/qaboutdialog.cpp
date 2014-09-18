#include "qaboutdialog.h"

void QAboutDialog::ShowDialog(QWidget *parent /*= 0*/)
{
  QAboutDialog(parent).exec();
}

QAboutDialog::QAboutDialog(QWidget* pParent /*= 0*/, Qt::WindowFlags oFlags /*= 0*/)
  : QDialog(pParent, oFlags)
{
  m_oUi.setupUi(this);
}

QAboutDialog::~QAboutDialog()
{
  ;
}
