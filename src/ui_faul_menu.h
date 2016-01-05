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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_faul_menu
{
public:
    QGridLayout *gridLayout;
    QPushButton *bt_ft_ko;
    QPushButton *bt_close;
    QPushButton *bt_change_on_faul;
    QPushButton *bt_foul_done;
    QPushButton *bt_oreb;
    QPushButton *bt_foul_recv;
    QPushButton *bt_ft_ok;
    QLabel *lb_ft_perc;
    QLabel *label;
    QComboBox *cb_MyTeam;
    QComboBox *cb_Faul;
    QComboBox *cb_OthTeam;

    void setupUi(QDialog *faul_menu)
    {
        if (faul_menu->objectName().isEmpty())
            faul_menu->setObjectName(QStringLiteral("faul_menu"));
        faul_menu->resize(360, 600);
        gridLayout = new QGridLayout(faul_menu);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        bt_ft_ko = new QPushButton(faul_menu);
        bt_ft_ko->setObjectName(QStringLiteral("bt_ft_ko"));
        bt_ft_ko->setStyleSheet(QStringLiteral("background-color: rgb(255, 0, 0);"));

        gridLayout->addWidget(bt_ft_ko, 4, 2, 1, 1);

        bt_close = new QPushButton(faul_menu);
        bt_close->setObjectName(QStringLiteral("bt_close"));

        gridLayout->addWidget(bt_close, 5, 0, 1, 1);

        bt_change_on_faul = new QPushButton(faul_menu);
        bt_change_on_faul->setObjectName(QStringLiteral("bt_change_on_faul"));
        bt_change_on_faul->setStyleSheet(QStringLiteral("background-color: rgb(255, 170, 0);"));

        gridLayout->addWidget(bt_change_on_faul, 5, 1, 1, 1);

        bt_foul_done = new QPushButton(faul_menu);
        bt_foul_done->setObjectName(QStringLiteral("bt_foul_done"));
        QFont font;
        font.setPointSize(9);
        bt_foul_done->setFont(font);
        bt_foul_done->setStyleSheet(QStringLiteral("background-color: rgb(255, 0, 0);"));

        gridLayout->addWidget(bt_foul_done, 1, 2, 1, 1);

        bt_oreb = new QPushButton(faul_menu);
        bt_oreb->setObjectName(QStringLiteral("bt_oreb"));

        gridLayout->addWidget(bt_oreb, 5, 2, 1, 1);

        bt_foul_recv = new QPushButton(faul_menu);
        bt_foul_recv->setObjectName(QStringLiteral("bt_foul_recv"));
        bt_foul_recv->setFont(font);
        bt_foul_recv->setStyleSheet(QLatin1String("background-color: rgb(170, 255, 127);\n"
"color: rgb(0, 0, 0);"));

        gridLayout->addWidget(bt_foul_recv, 1, 0, 1, 1);

        bt_ft_ok = new QPushButton(faul_menu);
        bt_ft_ok->setObjectName(QStringLiteral("bt_ft_ok"));
        bt_ft_ok->setStyleSheet(QLatin1String("background-color: rgb(170, 255, 127);\n"
"color: rgb(0, 0, 0);"));

        gridLayout->addWidget(bt_ft_ok, 4, 0, 1, 1);

        lb_ft_perc = new QLabel(faul_menu);
        lb_ft_perc->setObjectName(QStringLiteral("lb_ft_perc"));
        lb_ft_perc->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lb_ft_perc, 4, 1, 1, 1);

        label = new QLabel(faul_menu);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 1, 1, 1, 1);

        cb_MyTeam = new QComboBox(faul_menu);
        cb_MyTeam->setObjectName(QStringLiteral("cb_MyTeam"));

        gridLayout->addWidget(cb_MyTeam, 2, 0, 1, 1);

        cb_Faul = new QComboBox(faul_menu);
        cb_Faul->setObjectName(QStringLiteral("cb_Faul"));

        gridLayout->addWidget(cb_Faul, 2, 1, 1, 1);

        cb_OthTeam = new QComboBox(faul_menu);
        cb_OthTeam->setObjectName(QStringLiteral("cb_OthTeam"));

        gridLayout->addWidget(cb_OthTeam, 2, 2, 1, 1);


        retranslateUi(faul_menu);

        QMetaObject::connectSlotsByName(faul_menu);
    } // setupUi

    void retranslateUi(QDialog *faul_menu)
    {
        faul_menu->setWindowTitle(QApplication::translate("faul_menu", "Dialog", 0));
        bt_ft_ko->setText(QApplication::translate("faul_menu", "-", 0));
        bt_close->setText(QApplication::translate("faul_menu", "close", 0));
        bt_change_on_faul->setText(QApplication::translate("faul_menu", "Change", 0));
        bt_foul_done->setText(QApplication::translate("faul_menu", "-", 0));
        bt_oreb->setText(QApplication::translate("faul_menu", "OREB", 0));
        bt_foul_recv->setText(QApplication::translate("faul_menu", "-", 0));
        bt_ft_ok->setText(QApplication::translate("faul_menu", "-", 0));
        lb_ft_perc->setText(QApplication::translate("faul_menu", "FT", 0));
        label->setText(QApplication::translate("faul_menu", "Fouls Rec/Done", 0));
        cb_Faul->clear();
        cb_Faul->insertItems(0, QStringList()
         << QApplication::translate("faul_menu", "P", 0)
         << QApplication::translate("faul_menu", "P1", 0)
         << QApplication::translate("faul_menu", "P2", 0)
         << QApplication::translate("faul_menu", "P3", 0)
         << QApplication::translate("faul_menu", "T1", 0)
         << QApplication::translate("faul_menu", "U2", 0)
         << QApplication::translate("faul_menu", "DG", 0)
         << QApplication::translate("faul_menu", "F", 0)
        );
    } // retranslateUi

};

namespace Ui {
    class faul_menu: public Ui_faul_menu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FAUL_MENU_H
