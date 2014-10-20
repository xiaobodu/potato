/********************************************************************************
** Form generated from reading UI file 'sidebarwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef QSIDEBARWIDGET_UI_H
#define QSIDEBARWIDGET_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qpropertywidget.h"
#include "qscenetreewidget.h"

QT_BEGIN_NAMESPACE

class Ui_SideBarWidget
{
public:
    QVBoxLayout *verticalLayout_3;
    c4g::qt::QSceneTreeWidget *twScene;
    QFrame *line;
    c4g::qt::QPropertyWidget *propertyWidget;

    void setupUi(QWidget *SideBarWidget)
    {
        if (SideBarWidget->objectName().isEmpty())
            SideBarWidget->setObjectName(QStringLiteral("SideBarWidget"));
        SideBarWidget->resize(233, 527);
        verticalLayout_3 = new QVBoxLayout(SideBarWidget);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        twScene = new c4g::qt::QSceneTreeWidget(SideBarWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(1, QStringLiteral("2"));
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        twScene->setHeaderItem(__qtreewidgetitem);
        twScene->setObjectName(QStringLiteral("twScene"));
        twScene->setColumnCount(2);

        verticalLayout_3->addWidget(twScene);

        line = new QFrame(SideBarWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line);

        propertyWidget = new c4g::qt::QPropertyWidget(SideBarWidget);
        propertyWidget->setObjectName(QStringLiteral("propertyWidget"));

        verticalLayout_3->addWidget(propertyWidget);


        retranslateUi(SideBarWidget);
        QObject::connect(twScene, SIGNAL(itemClicked(QTreeWidgetItem*,int)), propertyWidget, SLOT(UpdateWidget(QTreeWidgetItem*,int)));

        QMetaObject::connectSlotsByName(SideBarWidget);
    } // setupUi

    void retranslateUi(QWidget *SideBarWidget)
    {
        SideBarWidget->setWindowTitle(QApplication::translate("SideBarWidget", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class SideBarWidget: public Ui_SideBarWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // QSIDEBARWIDGET_UI_H
