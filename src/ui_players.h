/********************************************************************************
** Form generated from reading UI file 'players.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYERS_H
#define UI_PLAYERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_players
{
public:
    QGridLayout *gridLayout;
    QSlider *time_slider;
    QPushButton *bt_field2;
    QPushButton *bt_field3;
    QPushButton *bt_field4;
    QPushButton *bt_field5;
    QSpinBox *in_minutes;
    QSpinBox *in_seconds;
    QPushButton *bt_close;
    QPushButton *bt_field1;
    QLabel *lb_spiega;
    QPushButton *bt_res_10;
    QPushButton *bt_res_09;
    QPushButton *bt_res_08;
    QPushButton *bt_res_07;
    QPushButton *bt_change;
    QPushButton *bt_res_06;
    QPushButton *bt_res_05;
    QPushButton *bt_res_04;
    QPushButton *bt_res_03;
    QPushButton *bt_res_02;
    QPushButton *bt_res_01;
    QPushButton *bt_my_timeout;
    QPushButton *bt_oth_tmout;
    QPushButton *bt_f_none;
    QPushButton *bt_f_coach;
    QPushButton *bt_f_bench;

    void setupUi(QDialog *players)
    {
        if (players->objectName().isEmpty())
            players->setObjectName(QStringLiteral("players"));
        players->resize(360, 600);
        gridLayout = new QGridLayout(players);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        time_slider = new QSlider(players);
        time_slider->setObjectName(QStringLiteral("time_slider"));
        time_slider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(time_slider, 21, 0, 1, 3);

        bt_field2 = new QPushButton(players);
        bt_field2->setObjectName(QStringLiteral("bt_field2"));
        bt_field2->setStyleSheet(QLatin1String("selection-background-color: rgb(85, 255, 0);\n"
"selection-color: rgb(255, 0, 0);"));
        bt_field2->setCheckable(false);

        gridLayout->addWidget(bt_field2, 12, 0, 1, 1);

        bt_field3 = new QPushButton(players);
        bt_field3->setObjectName(QStringLiteral("bt_field3"));
        bt_field3->setStyleSheet(QLatin1String("selection-background-color: rgb(85, 255, 0);\n"
"selection-color: rgb(255, 0, 0);"));
        bt_field3->setCheckable(false);

        gridLayout->addWidget(bt_field3, 14, 0, 1, 1);

        bt_field4 = new QPushButton(players);
        bt_field4->setObjectName(QStringLiteral("bt_field4"));
        bt_field4->setStyleSheet(QLatin1String("selection-background-color: rgb(85, 255, 0);\n"
"selection-color: rgb(255, 0, 0);"));
        bt_field4->setCheckable(false);

        gridLayout->addWidget(bt_field4, 15, 0, 1, 1);

        bt_field5 = new QPushButton(players);
        bt_field5->setObjectName(QStringLiteral("bt_field5"));
        bt_field5->setStyleSheet(QLatin1String("selection-background-color: rgb(85, 255, 0);\n"
"selection-color: rgb(255, 0, 0);"));
        bt_field5->setCheckable(false);

        gridLayout->addWidget(bt_field5, 16, 0, 1, 1);

        in_minutes = new QSpinBox(players);
        in_minutes->setObjectName(QStringLiteral("in_minutes"));
        QFont font;
        font.setPointSize(10);
        in_minutes->setFont(font);
        in_minutes->setMaximum(12);

        gridLayout->addWidget(in_minutes, 18, 0, 1, 1);

        in_seconds = new QSpinBox(players);
        in_seconds->setObjectName(QStringLiteral("in_seconds"));
        QFont font1;
        font1.setPointSize(8);
        in_seconds->setFont(font1);
        in_seconds->setMaximum(59);
        in_seconds->setSingleStep(1);

        gridLayout->addWidget(in_seconds, 18, 1, 1, 1);

        bt_close = new QPushButton(players);
        bt_close->setObjectName(QStringLiteral("bt_close"));
        bt_close->setStyleSheet(QStringLiteral("background-color: rgb(255, 0, 0);"));

        gridLayout->addWidget(bt_close, 23, 0, 1, 1);

        bt_field1 = new QPushButton(players);
        bt_field1->setObjectName(QStringLiteral("bt_field1"));
        bt_field1->setStyleSheet(QLatin1String("selection-background-color: rgb(85, 255, 0);\n"
"selection-color: rgb(255, 0, 0);"));
        bt_field1->setCheckable(false);
        bt_field1->setChecked(false);

        gridLayout->addWidget(bt_field1, 11, 0, 1, 1);

        lb_spiega = new QLabel(players);
        lb_spiega->setObjectName(QStringLiteral("lb_spiega"));
        QFont font2;
        font2.setFamily(QStringLiteral("Lucida Console"));
        lb_spiega->setFont(font2);

        gridLayout->addWidget(lb_spiega, 6, 0, 1, 3);

        bt_res_10 = new QPushButton(players);
        bt_res_10->setObjectName(QStringLiteral("bt_res_10"));
        bt_res_10->setCheckable(false);

        gridLayout->addWidget(bt_res_10, 16, 1, 1, 1);

        bt_res_09 = new QPushButton(players);
        bt_res_09->setObjectName(QStringLiteral("bt_res_09"));
        bt_res_09->setCheckable(false);

        gridLayout->addWidget(bt_res_09, 15, 1, 1, 1);

        bt_res_08 = new QPushButton(players);
        bt_res_08->setObjectName(QStringLiteral("bt_res_08"));
        bt_res_08->setCheckable(false);

        gridLayout->addWidget(bt_res_08, 14, 1, 1, 1);

        bt_res_07 = new QPushButton(players);
        bt_res_07->setObjectName(QStringLiteral("bt_res_07"));
        bt_res_07->setCheckable(true);

        gridLayout->addWidget(bt_res_07, 12, 1, 1, 1);

        bt_change = new QPushButton(players);
        bt_change->setObjectName(QStringLiteral("bt_change"));
        bt_change->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 0);\n"
"color: rgb(0, 0, 255);"));

        gridLayout->addWidget(bt_change, 11, 1, 1, 1);

        bt_res_06 = new QPushButton(players);
        bt_res_06->setObjectName(QStringLiteral("bt_res_06"));
        bt_res_06->setCheckable(false);

        gridLayout->addWidget(bt_res_06, 18, 2, 1, 1);

        bt_res_05 = new QPushButton(players);
        bt_res_05->setObjectName(QStringLiteral("bt_res_05"));
        bt_res_05->setStyleSheet(QLatin1String("selection-background-color: rgb(85, 255, 0);\n"
"selection-color: rgb(255, 0, 0);"));
        bt_res_05->setCheckable(false);

        gridLayout->addWidget(bt_res_05, 16, 2, 1, 1);

        bt_res_04 = new QPushButton(players);
        bt_res_04->setObjectName(QStringLiteral("bt_res_04"));
        bt_res_04->setStyleSheet(QLatin1String("selection-background-color: rgb(85, 255, 0);\n"
"selection-color: rgb(255, 0, 0);"));
        bt_res_04->setCheckable(false);

        gridLayout->addWidget(bt_res_04, 15, 2, 1, 1);

        bt_res_03 = new QPushButton(players);
        bt_res_03->setObjectName(QStringLiteral("bt_res_03"));
        bt_res_03->setStyleSheet(QLatin1String("selection-background-color: rgb(85, 255, 0);\n"
"selection-color: rgb(255, 0, 0);"));
        bt_res_03->setCheckable(false);

        gridLayout->addWidget(bt_res_03, 14, 2, 1, 1);

        bt_res_02 = new QPushButton(players);
        bt_res_02->setObjectName(QStringLiteral("bt_res_02"));
        bt_res_02->setStyleSheet(QLatin1String("selection-background-color: rgb(85, 255, 0);\n"
"selection-color: rgb(255, 0, 0);"));
        bt_res_02->setCheckable(false);

        gridLayout->addWidget(bt_res_02, 12, 2, 1, 1);

        bt_res_01 = new QPushButton(players);
        bt_res_01->setObjectName(QStringLiteral("bt_res_01"));
        bt_res_01->setStyleSheet(QLatin1String("selection-background-color: rgb(85, 255, 0);\n"
"selection-color: rgb(255, 0, 0);"));
        bt_res_01->setCheckable(false);

        gridLayout->addWidget(bt_res_01, 11, 2, 1, 1);

        bt_my_timeout = new QPushButton(players);
        bt_my_timeout->setObjectName(QStringLiteral("bt_my_timeout"));

        gridLayout->addWidget(bt_my_timeout, 23, 1, 1, 1);

        bt_oth_tmout = new QPushButton(players);
        bt_oth_tmout->setObjectName(QStringLiteral("bt_oth_tmout"));

        gridLayout->addWidget(bt_oth_tmout, 23, 2, 1, 1);

        bt_f_none = new QPushButton(players);
        bt_f_none->setObjectName(QStringLiteral("bt_f_none"));

        gridLayout->addWidget(bt_f_none, 22, 0, 1, 1);

        bt_f_coach = new QPushButton(players);
        bt_f_coach->setObjectName(QStringLiteral("bt_f_coach"));

        gridLayout->addWidget(bt_f_coach, 22, 1, 1, 1);

        bt_f_bench = new QPushButton(players);
        bt_f_bench->setObjectName(QStringLiteral("bt_f_bench"));

        gridLayout->addWidget(bt_f_bench, 22, 2, 1, 1);


        retranslateUi(players);

        QMetaObject::connectSlotsByName(players);
    } // setupUi

    void retranslateUi(QDialog *players)
    {
        players->setWindowTitle(QApplication::translate("players", "Dialog", 0));
        bt_field2->setText(QApplication::translate("players", "-", 0));
        bt_field3->setText(QApplication::translate("players", "-", 0));
        bt_field4->setText(QApplication::translate("players", "-", 0));
        bt_field5->setText(QApplication::translate("players", "-", 0));
        bt_close->setText(QApplication::translate("players", "close", 0));
        bt_field1->setText(QApplication::translate("players", "-", 0));
        lb_spiega->setText(QApplication::translate("players", "-", 0));
        bt_res_10->setText(QApplication::translate("players", "-", 0));
        bt_res_09->setText(QApplication::translate("players", "-", 0));
        bt_res_08->setText(QApplication::translate("players", "-", 0));
        bt_res_07->setText(QApplication::translate("players", "-", 0));
        bt_change->setText(QApplication::translate("players", "<->", 0));
        bt_res_06->setText(QApplication::translate("players", "-", 0));
        bt_res_05->setText(QApplication::translate("players", "-", 0));
        bt_res_04->setText(QApplication::translate("players", "-", 0));
        bt_res_03->setText(QApplication::translate("players", "-", 0));
        bt_res_02->setText(QApplication::translate("players", "-", 0));
        bt_res_01->setText(QApplication::translate("players", "-", 0));
        bt_my_timeout->setText(QApplication::translate("players", "TO my", 0));
        bt_oth_tmout->setText(QApplication::translate("players", "TO oth", 0));
        bt_f_none->setText(QApplication::translate("players", "Nobody", 0));
        bt_f_coach->setText(QApplication::translate("players", "Coach", 0));
        bt_f_bench->setText(QApplication::translate("players", "Bench", 0));
    } // retranslateUi

};

namespace Ui {
    class players: public Ui_players {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYERS_H
