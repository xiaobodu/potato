/********************************************************************************
** Form generated from reading UI file 'basicpropertywidget.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef QBASICPROPERTYWIDGET_UI_H
#define QBASICPROPERTYWIDGET_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BasicPropertyWidget
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *leId;
    QLabel *label_2;
    QLineEdit *leClass;
    QLabel *label_3;
    QSpinBox *sbLayer;
    QGridLayout *gridLayout;
    QCheckBox *cbVisible;
    QCheckBox *cbResize;
    QCheckBox *cbAlwayTick;
    QCheckBox *cbInput;
    QCheckBox *cbSensor;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *BasicPropertyWidget)
    {
        if (BasicPropertyWidget->objectName().isEmpty())
            BasicPropertyWidget->setObjectName(QStringLiteral("BasicPropertyWidget"));
        BasicPropertyWidget->resize(258, 160);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(BasicPropertyWidget->sizePolicy().hasHeightForWidth());
        BasicPropertyWidget->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(BasicPropertyWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(BasicPropertyWidget);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        leId = new QLineEdit(BasicPropertyWidget);
        leId->setObjectName(QStringLiteral("leId"));

        formLayout->setWidget(0, QFormLayout::FieldRole, leId);

        label_2 = new QLabel(BasicPropertyWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        leClass = new QLineEdit(BasicPropertyWidget);
        leClass->setObjectName(QStringLiteral("leClass"));

        formLayout->setWidget(1, QFormLayout::FieldRole, leClass);

        label_3 = new QLabel(BasicPropertyWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        sbLayer = new QSpinBox(BasicPropertyWidget);
        sbLayer->setObjectName(QStringLiteral("sbLayer"));

        formLayout->setWidget(2, QFormLayout::FieldRole, sbLayer);


        verticalLayout->addLayout(formLayout);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        cbVisible = new QCheckBox(BasicPropertyWidget);
        cbVisible->setObjectName(QStringLiteral("cbVisible"));

        gridLayout->addWidget(cbVisible, 0, 0, 1, 1);

        cbResize = new QCheckBox(BasicPropertyWidget);
        cbResize->setObjectName(QStringLiteral("cbResize"));

        gridLayout->addWidget(cbResize, 0, 1, 1, 1);

        cbAlwayTick = new QCheckBox(BasicPropertyWidget);
        cbAlwayTick->setObjectName(QStringLiteral("cbAlwayTick"));

        gridLayout->addWidget(cbAlwayTick, 0, 2, 1, 1);

        cbInput = new QCheckBox(BasicPropertyWidget);
        cbInput->setObjectName(QStringLiteral("cbInput"));

        gridLayout->addWidget(cbInput, 1, 0, 1, 1);

        cbSensor = new QCheckBox(BasicPropertyWidget);
        cbSensor->setObjectName(QStringLiteral("cbSensor"));

        gridLayout->addWidget(cbSensor, 1, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(BasicPropertyWidget);

        QMetaObject::connectSlotsByName(BasicPropertyWidget);
    } // setupUi

    void retranslateUi(QWidget *BasicPropertyWidget)
    {
        BasicPropertyWidget->setWindowTitle(QApplication::translate("BasicPropertyWidget", "Form", 0));
        label->setText(QApplication::translate("BasicPropertyWidget", "ID", 0));
        label_2->setText(QApplication::translate("BasicPropertyWidget", "Class", 0));
        label_3->setText(QApplication::translate("BasicPropertyWidget", "Layer", 0));
        cbVisible->setText(QApplication::translate("BasicPropertyWidget", "Visible", 0));
        cbResize->setText(QApplication::translate("BasicPropertyWidget", "Resize", 0));
        cbAlwayTick->setText(QApplication::translate("BasicPropertyWidget", "Alway Tick", 0));
        cbInput->setText(QApplication::translate("BasicPropertyWidget", "Input", 0));
        cbSensor->setText(QApplication::translate("BasicPropertyWidget", "Sensor", 0));
    } // retranslateUi

};

namespace Ui {
    class BasicPropertyWidget: public Ui_BasicPropertyWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // QBASICPROPERTYWIDGET_UI_H
