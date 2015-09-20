/********************************************************************************
** Form generated from reading UI file 'cardlist.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CARDLIST_H
#define UI_CARDLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CardList
{
public:

    void setupUi(QWidget *CardList)
    {
        if (CardList->objectName().isEmpty())
            CardList->setObjectName(QStringLiteral("CardList"));
        CardList->resize(400, 300);

        retranslateUi(CardList);

        QMetaObject::connectSlotsByName(CardList);
    } // setupUi

    void retranslateUi(QWidget *CardList)
    {
        CardList->setWindowTitle(QApplication::translate("CardList", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class CardList: public Ui_CardList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CARDLIST_H
