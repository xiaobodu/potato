/********************************************************************************
** Form generated from reading UI file 'propertywidget.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
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
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PropertyWidget
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QVBoxLayout *layoutProperty;

    void setupUi(QWidget *PropertyWidget)
    {
        if (PropertyWidget->objectName().isEmpty())
            PropertyWidget->setObjectName(QStringLiteral("PropertyWidget"));
        PropertyWidget->resize(181, 50);
        PropertyWidget->setMinimumSize(QSize(0, 50));
        verticalLayout = new QVBoxLayout(PropertyWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(PropertyWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        layoutProperty = new QVBoxLayout();
        layoutProperty->setObjectName(QStringLiteral("layoutProperty"));

        verticalLayout->addLayout(layoutProperty);


        retranslateUi(PropertyWidget);

        QMetaObject::connectSlotsByName(PropertyWidget);
    } // setupUi

    void retranslateUi(QWidget *PropertyWidget)
    {
        PropertyWidget->setWindowTitle(QApplication::translate("PropertyWidget", "Form", 0));
        label->setText(QApplication::translate("PropertyWidget", "Property", 0));
    } // retranslateUi

};

namespace Ui {
    class PropertyWidget: public Ui_PropertyWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // QPROPERTYWIDGET_UI_H
