#pragma once

#include "qaboutdialog_ui.h"
#include <QtWidgets/QDialog>

class QAboutDialog : public QDialog
{
    Q_OBJECT

public:
    static void ShowDialog(QWidget* pParent);

protected:
    QAboutDialog(QWidget* pParent = 0, Qt::WindowFlags oFlags = 0);
    virtual ~QAboutDialog();

private:
    Ui::AboutDialog   m_oUi;
};
