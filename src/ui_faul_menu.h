/********************************************************************************
** Form generated from reading UI file 'faul_menu.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FAUL_MENU_H
#define UI_FAUL_MENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_faul_menu
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QPushButton *bt_foul_recv;
    QPushButton *bt_ft_ok;
    QPushButton *bt_tech_coach_done;
    QRadioButton *rb_noft;
    QPushButton *bt_ft_ko;
    QPushButton *bt_close;
    QLabel *lb_ft_perc;
    QPushButton *bt_change_on_faul;
    QRadioButton *rb_2FT;
    QPushButton *bt_tech_recv;
    QPushButton *bt_tech_team_done;
    QPushButton *bt_foul_done;
    QRadioButton *rb_1FT;
    QPushButton *bt_oreb;
    QRadioButton *rb_faul_tech;
    QRadioButton *rb_3FT;
    QRadioButton *rb_faul_antisp;
    QRadioButton *rb_Espulsione;

    void setupUi(QDialog *faul_menu)
    {
        if (faul_menu->objectName().isEmpty())
            faul_menu->setObjectName(QStringLiteral("faul_menu"));
        faul_menu->resize(360, 600);
        gridLayout = new QGridLayout(faul_menu);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(faul_menu);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 1, 1, 1, 1);

        bt_foul_recv = new QPushButton(faul_menu);
        bt_foul_recv->setObjectName(QStringLiteral("bt_foul_recv"));
        QFont font;
        font.setPointSize(9);
        bt_foul_recv->setFont(font);
        bt_foul_recv->setStyleSheet(QLatin1String("background-color: rgb(170, 255, 127);\n"
"color: rgb(0, 0, 0);"));

        gridLayout->addWidget(bt_foul_recv, 1, 0, 1, 1);

        bt_ft_ok = new QPushButton(faul_menu);
        bt_ft_ok->setObjectName(QStringLiteral("bt_ft_ok"));
        bt_ft_ok->setStyleSheet(QLatin1String("background-color: rgb(170, 255, 127);\n"
"color: rgb(0, 0, 0);"));

        gridLayout->addWidget(bt_ft_ok, 6, 0, 1, 1);

        bt_tech_coach_done = new QPushButton(faul_menu);
        bt_tech_coach_done->setObjectName(QStringLiteral("bt_tech_coach_done"));
        QFont font1;
        font1.setPointSize(7);
        bt_tech_coach_done->setFont(font1);
        bt_tech_coach_done->setStyleSheet(QStringLiteral("background-color: rgb(255, 0, 0);"));

        gridLayout->addWidget(bt_tech_coach_done, 8, 2, 1, 1);

        rb_noft = new QRadioButton(faul_menu);
        rb_noft->setObjectName(QStringLiteral("rb_noft"));
        rb_noft->setFont(font);
        rb_noft->setText(QStringLiteral("P"));

        gridLayout->addWidget(rb_noft, 2, 0, 1, 1);

        bt_ft_ko = new QPushButton(faul_menu);
        bt_ft_ko->setObjectName(QStringLiteral("bt_ft_ko"));
        bt_ft_ko->setStyleSheet(QStringLiteral("background-color: rgb(255, 0, 0);"));

        gridLayout->addWidget(bt_ft_ko, 6, 2, 1, 1);

        bt_close = new QPushButton(faul_menu);
        bt_close->setObjectName(QStringLiteral("bt_close"));

        gridLayout->addWidget(bt_close, 7, 0, 1, 1);

        lb_ft_perc = new QLabel(faul_menu);
        lb_ft_perc->setObjectName(QStringLiteral("lb_ft_perc"));
        lb_ft_perc->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lb_ft_perc, 6, 1, 1, 1);

        bt_change_on_faul = new QPushButton(faul_menu);
        bt_change_on_faul->setObjectName(QStringLiteral("bt_change_on_faul"));
        bt_change_on_faul->setStyleSheet(QStringLiteral("background-color: rgb(255, 170, 0);"));

        gridLayout->addWidget(bt_change_on_faul, 7, 1, 1, 1);

        rb_2FT = new QRadioButton(faul_menu);
        rb_2FT->setObjectName(QStringLiteral("rb_2FT"));
        rb_2FT->setFont(font);
        rb_2FT->setText(QStringLiteral("P2"));

        gridLayout->addWidget(rb_2FT, 2, 1, 1, 1);

        bt_tech_recv = new QPushButton(faul_menu);
        bt_tech_recv->setObjectName(QStringLiteral("bt_tech_recv"));
        bt_tech_recv->setFont(font1);
        bt_tech_recv->setStyleSheet(QLatin1String("background-color: rgb(170, 255, 127);\n"
"color: rgb(0, 0, 0);"));

        gridLayout->addWidget(bt_tech_recv, 8, 0, 1, 1);

        bt_tech_team_done = new QPushButton(faul_menu);
        bt_tech_team_done->setObjectName(QStringLiteral("bt_tech_team_done"));
        bt_tech_team_done->setFont(font1);
        bt_tech_team_done->setStyleSheet(QStringLiteral("background-color: rgb(255, 0, 0);"));

        gridLayout->addWidget(bt_tech_team_done, 8, 1, 1, 1);

        bt_foul_done = new QPushButton(faul_menu);
        bt_foul_done->setObjectName(QStringLiteral("bt_foul_done"));
        bt_foul_done->setFont(font);
        bt_foul_done->setStyleSheet(QStringLiteral("background-color: rgb(255, 0, 0);"));

        gridLayout->addWidget(bt_foul_done, 1, 2, 1, 1);

        rb_1FT = new QRadioButton(faul_menu);
        rb_1FT->setObjectName(QStringLiteral("rb_1FT"));
        rb_1FT->setFont(font);
        rb_1FT->setText(QStringLiteral("P1"));

        gridLayout->addWidget(rb_1FT, 2, 2, 1, 1);

        bt_oreb = new QPushButton(faul_menu);
        bt_oreb->setObjectName(QStringLiteral("bt_oreb"));

        gridLayout->addWidget(bt_oreb, 7, 2, 1, 1);

        rb_faul_tech = new QRadioButton(faul_menu);
        rb_faul_tech->setObjectName(QStringLiteral("rb_faul_tech"));
        rb_faul_tech->setFont(font);
        rb_faul_tech->setText(QStringLiteral("T1"));

        gridLayout->addWidget(rb_faul_tech, 3, 1, 1, 1);

        rb_3FT = new QRadioButton(faul_menu);
        rb_3FT->setObjectName(QStringLiteral("rb_3FT"));
        rb_3FT->setFont(font);
        rb_3FT->setText(QStringLiteral("P3"));

        gridLayout->addWidget(rb_3FT, 3, 0, 1, 1);

        rb_faul_antisp = new QRadioButton(faul_menu);
        rb_faul_antisp->setObjectName(QStringLiteral("rb_faul_antisp"));
        rb_faul_antisp->setFont(font);
        rb_faul_antisp->setText(QStringLiteral("U2"));

        gridLayout->addWidget(rb_faul_antisp, 3, 2, 1, 1);

        rb_Espulsione = new QRadioButton(faul_menu);
        rb_Espulsione->setObjectName(QStringLiteral("rb_Espulsione"));
        rb_Espulsione->setText(QStringLiteral("DG"));

        gridLayout->addWidget(rb_Espulsione, 4, 0, 1, 1);


        retranslateUi(faul_menu);

        QMetaObject::connectSlotsByName(faul_menu);
    } // setupUi

    void retranslateUi(QDialog *faul_menu)
    {
        faul_menu->setWindowTitle(QApplication::translate("faul_menu", "Dialog", 0));
        label->setText(QApplication::translate("faul_menu", "Fouls Rec/Done", 0));
        bt_foul_recv->setText(QApplication::translate("faul_menu", "-", 0));
        bt_ft_ok->setText(QApplication::translate("faul_menu", "-", 0));
        bt_tech_coach_done->setText(QApplication::translate("faul_menu", "TF Coach", 0));
        bt_ft_ko->setText(QApplication::translate("faul_menu", "-", 0));
        bt_close->setText(QApplication::translate("faul_menu", "close", 0));
        lb_ft_perc->setText(QApplication::translate("faul_menu", "FT", 0));
        bt_change_on_faul->setText(QApplication::translate("faul_menu", "Change", 0));
        bt_tech_recv->setText(QApplication::translate("faul_menu", "TF other", 0));
        bt_tech_team_done->setText(QApplication::translate("faul_menu", "TF Team", 0));
        bt_foul_done->setText(QApplication::translate("faul_menu", "-", 0));
        bt_oreb->setText(QApplication::translate("faul_menu", "OREB", 0));
    } // retranslateUi

};

namespace Ui {
    class faul_menu: public Ui_faul_menu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FAUL_MENU_H
