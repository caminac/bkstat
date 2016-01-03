/********************************************************************************
** Form generated from reading UI file 'select_player.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECT_PLAYER_H
#define UI_SELECT_PLAYER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_select_player
{
public:
    QPushButton *bt_pl1;
    QPushButton *bt_pl2;
    QPushButton *bt_pl3;
    QPushButton *bt_pl4;
    QPushButton *bt_pl5;

    void setupUi(QDialog *select_player)
    {
        if (select_player->objectName().isEmpty())
            select_player->setObjectName(QStringLiteral("select_player"));
        select_player->resize(400, 300);
        bt_pl1 = new QPushButton(select_player);
        bt_pl1->setObjectName(QStringLiteral("bt_pl1"));
        bt_pl1->setGeometry(QRect(40, 20, 75, 23));
        bt_pl2 = new QPushButton(select_player);
        bt_pl2->setObjectName(QStringLiteral("bt_pl2"));
        bt_pl2->setGeometry(QRect(280, 20, 75, 23));
        bt_pl3 = new QPushButton(select_player);
        bt_pl3->setObjectName(QStringLiteral("bt_pl3"));
        bt_pl3->setGeometry(QRect(70, 90, 75, 23));
        bt_pl4 = new QPushButton(select_player);
        bt_pl4->setObjectName(QStringLiteral("bt_pl4"));
        bt_pl4->setGeometry(QRect(250, 90, 75, 23));
        bt_pl5 = new QPushButton(select_player);
        bt_pl5->setObjectName(QStringLiteral("bt_pl5"));
        bt_pl5->setGeometry(QRect(160, 140, 75, 23));

        retranslateUi(select_player);

        QMetaObject::connectSlotsByName(select_player);
    } // setupUi

    void retranslateUi(QDialog *select_player)
    {
        select_player->setWindowTitle(QApplication::translate("select_player", "Dialog", 0));
        bt_pl1->setText(QApplication::translate("select_player", "PushButton", 0));
        bt_pl2->setText(QApplication::translate("select_player", "PushButton", 0));
        bt_pl3->setText(QApplication::translate("select_player", "PushButton", 0));
        bt_pl4->setText(QApplication::translate("select_player", "PushButton", 0));
        bt_pl5->setText(QApplication::translate("select_player", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class select_player: public Ui_select_player {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECT_PLAYER_H
