/********************************************************************************
** Form generated from reading UI file 'infoitem.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFOITEM_H
#define UI_INFOITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InfoItem
{
public:

    void setupUi(QWidget *InfoItem)
    {
        if (InfoItem->objectName().isEmpty())
            InfoItem->setObjectName(QString::fromUtf8("InfoItem"));
        InfoItem->resize(400, 300);

        retranslateUi(InfoItem);

        QMetaObject::connectSlotsByName(InfoItem);
    } // setupUi

    void retranslateUi(QWidget *InfoItem)
    {
        InfoItem->setWindowTitle(QCoreApplication::translate("InfoItem", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InfoItem: public Ui_InfoItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFOITEM_H
