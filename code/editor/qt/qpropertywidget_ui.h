/********************************************************************************
** Form generated from reading UI file 'propertywidget.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef QPROPERTYWIDGET_UI_H
#define QPROPERTYWIDGET_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PropertyWidget
{
public:
    QVBoxLayout *verticalLayout;
    QToolBox *tbPropertyPages;
    QWidget *page;
    QVBoxLayout *verticalLayout_3;

    void setupUi(QWidget *PropertyWidget)
    {
        if (PropertyWidget->objectName().isEmpty())
            PropertyWidget->setObjectName(QStringLiteral("PropertyWidget"));
        PropertyWidget->resize(95, 50);
        PropertyWidget->setMinimumSize(QSize(0, 50));
        verticalLayout = new QVBoxLayout(PropertyWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tbPropertyPages = new QToolBox(PropertyWidget);
        tbPropertyPages->setObjectName(QStringLiteral("tbPropertyPages"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        page->setGeometry(QRect(0, 0, 64, 16));
        verticalLayout_3 = new QVBoxLayout(page);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        tbPropertyPages->addItem(page, QStringLiteral("None"));

        verticalLayout->addWidget(tbPropertyPages);


        retranslateUi(PropertyWidget);

        tbPropertyPages->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PropertyWidget);
    } // setupUi

    void retranslateUi(QWidget *PropertyWidget)
    {
        PropertyWidget->setWindowTitle(QApplication::translate("PropertyWidget", "Form", 0));
        tbPropertyPages->setItemText(tbPropertyPages->indexOf(page), QApplication::translate("PropertyWidget", "None", 0));
    } // retranslateUi

};

namespace Ui {
    class PropertyWidget: public Ui_PropertyWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // QPROPERTYWIDGET_UI_H
