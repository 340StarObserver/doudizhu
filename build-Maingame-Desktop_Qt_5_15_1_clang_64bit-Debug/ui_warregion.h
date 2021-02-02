/********************************************************************************
** Form generated from reading UI file 'warregion.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WARREGION_H
#define UI_WARREGION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WarRegion
{
public:

    void setupUi(QWidget *WarRegion)
    {
        if (WarRegion->objectName().isEmpty())
            WarRegion->setObjectName(QString::fromUtf8("WarRegion"));
        WarRegion->resize(400, 300);

        retranslateUi(WarRegion);

        QMetaObject::connectSlotsByName(WarRegion);
    } // setupUi

    void retranslateUi(QWidget *WarRegion)
    {
        WarRegion->setWindowTitle(QCoreApplication::translate("WarRegion", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WarRegion: public Ui_WarRegion {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WARREGION_H
