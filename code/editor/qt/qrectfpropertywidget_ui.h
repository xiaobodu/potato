/********************************************************************************
** Form generated from reading UI file 'rectfpropertywidget.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef QRECTFPROPERTYWIDGET_UI_H
#define QRECTFPROPERTYWIDGET_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RectFPropertyWidget
{
public:
    QFormLayout *formLayout_2;
    QLabel *label;
    QDoubleSpinBox *dsbLeft;
    QLabel *label_2;
    QDoubleSpinBox *dsbRight;
    QLabel *label_3;
    QDoubleSpinBox *dsbTop;
    QLabel *label_4;
    QDoubleSpinBox *dsbBottom;

    void setupUi(QWidget *RectFPropertyWidget)
    {
        if (RectFPropertyWidget->objectName().isEmpty())
            RectFPropertyWidget->setObjectName(QStringLiteral("RectFPropertyWidget"));
        RectFPropertyWidget->resize(181, 127);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(RectFPropertyWidget->sizePolicy().hasHeightForWidth());
        RectFPropertyWidget->setSizePolicy(sizePolicy);
        formLayout_2 = new QFormLayout(RectFPropertyWidget);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        formLayout_2->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label = new QLabel(RectFPropertyWidget);
        label->setObjectName(QStringLiteral("label"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label);

        dsbLeft = new QDoubleSpinBox(RectFPropertyWidget);
        dsbLeft->setObjectName(QStringLiteral("dsbLeft"));
        dsbLeft->setMinimumSize(QSize(0, 24));
        dsbLeft->setDecimals(5);
        dsbLeft->setMinimum(-10000);
        dsbLeft->setMaximum(10000);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, dsbLeft);

        label_2 = new QLabel(RectFPropertyWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_2);

        dsbRight = new QDoubleSpinBox(RectFPropertyWidget);
        dsbRight->setObjectName(QStringLiteral("dsbRight"));
        dsbRight->setMinimumSize(QSize(0, 24));
        dsbRight->setMinimum(-10000);
        dsbRight->setMaximum(10000);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, dsbRight);

        label_3 = new QLabel(RectFPropertyWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_3);

        dsbTop = new QDoubleSpinBox(RectFPropertyWidget);
        dsbTop->setObjectName(QStringLiteral("dsbTop"));
        dsbTop->setMinimumSize(QSize(0, 24));
        dsbTop->setMinimum(-10000);
        dsbTop->setMaximum(10000);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, dsbTop);

        label_4 = new QLabel(RectFPropertyWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_4);

        dsbBottom = new QDoubleSpinBox(RectFPropertyWidget);
        dsbBottom->setObjectName(QStringLiteral("dsbBottom"));
        dsbBottom->setMinimumSize(QSize(0, 24));
        dsbBottom->setMinimum(-10000);
        dsbBottom->setMaximum(10000);

        formLayout_2->setWidget(3, QFormLayout::FieldRole, dsbBottom);


        retranslateUi(RectFPropertyWidget);

        QMetaObject::connectSlotsByName(RectFPropertyWidget);
    } // setupUi

    void retranslateUi(QWidget *RectFPropertyWidget)
    {
        RectFPropertyWidget->setWindowTitle(QApplication::translate("RectFPropertyWidget", "Form", 0));
        label->setText(QApplication::translate("RectFPropertyWidget", "Left", 0));
        label_2->setText(QApplication::translate("RectFPropertyWidget", "Right", 0));
        label_3->setText(QApplication::translate("RectFPropertyWidget", "Top", 0));
        label_4->setText(QApplication::translate("RectFPropertyWidget", "Bottom", 0));
    } // retranslateUi

};

namespace Ui {
    class RectFPropertyWidget: public Ui_RectFPropertyWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // QRECTFPROPERTYWIDGET_UI_H
