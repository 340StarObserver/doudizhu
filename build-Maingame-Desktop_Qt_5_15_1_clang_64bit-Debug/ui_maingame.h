/********************************************************************************
** Form generated from reading UI file 'maingame.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINGAME_H
#define UI_MAINGAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_Maingame
{
public:

    void setupUi(QDialog *Maingame)
    {
        if (Maingame->objectName().isEmpty())
            Maingame->setObjectName(QString::fromUtf8("Maingame"));
        Maingame->resize(1000, 600);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(231, 231, 231, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        Maingame->setPalette(palette);

        retranslateUi(Maingame);

        QMetaObject::connectSlotsByName(Maingame);
    } // setupUi

    void retranslateUi(QDialog *Maingame)
    {
        Maingame->setWindowTitle(QCoreApplication::translate("Maingame", "Maingame", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Maingame: public Ui_Maingame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINGAME_H
