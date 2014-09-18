/********************************************************************************
** Form generated from reading UI file 'sidebarwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef QSIDEBARWIDGET_UI_H
#define QSIDEBARWIDGET_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SideBarWidget
{
public:
    QVBoxLayout *verticalLayout_3;
    QTreeView *tvProject;
    QTabWidget *tabProperty;
    QWidget *tabPropertyMain;
    QVBoxLayout *verticalLayout;

    void setupUi(QWidget *SideBarWidget)
    {
        if (SideBarWidget->objectName().isEmpty())
            SideBarWidget->setObjectName(QStringLiteral("SideBarWidget"));
        SideBarWidget->resize(171, 399);
        verticalLayout_3 = new QVBoxLayout(SideBarWidget);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        tvProject = new QTreeView(SideBarWidget);
        tvProject->setObjectName(QStringLiteral("tvProject"));

        verticalLayout_3->addWidget(tvProject);

        tabProperty = new QTabWidget(SideBarWidget);
        tabProperty->setObjectName(QStringLiteral("tabProperty"));
        tabPropertyMain = new QWidget();
        tabPropertyMain->setObjectName(QStringLiteral("tabPropertyMain"));
        verticalLayout = new QVBoxLayout(tabPropertyMain);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tabProperty->addTab(tabPropertyMain, QString());

        verticalLayout_3->addWidget(tabProperty);


        retranslateUi(SideBarWidget);

        QMetaObject::connectSlotsByName(SideBarWidget);
    } // setupUi

    void retranslateUi(QWidget *SideBarWidget)
    {
        SideBarWidget->setWindowTitle(QApplication::translate("SideBarWidget", "Form", 0));
        tabProperty->setTabText(tabProperty->indexOf(tabPropertyMain), QApplication::translate("SideBarWidget", "Tab 1", 0));
    } // retranslateUi

};

namespace Ui {
    class SideBarWidget: public Ui_SideBarWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // QSIDEBARWIDGET_UI_H
