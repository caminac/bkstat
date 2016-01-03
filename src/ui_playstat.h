/********************************************************************************
** Form generated from reading UI file 'playstat.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYSTAT_H
#define UI_PLAYSTAT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_playstat
{
public:
    QGridLayout *gridLayout;
    QPushButton *bt_oth_points;
    QPushButton *bt_reb_def;
    QLabel *label;
    QLabel *label_4;
    QPushButton *bt_q_indicator;
    QPushButton *bt_asst;
    QLabel *label_my_fauls;
    QPushButton *bt_t3_ok;
    QLabel *label_pts;
    QPushButton *bt_undo;
    QPushButton *bt_t2_ko;
    QLabel *label_oth_fauls;
    QPushButton *bt_blocks;
    QPushButton *bt_t3_ko;
    QLabel *lab_t2;
    QPushButton *bt_t2_ok;
    QPushButton *bt_steal_ok;
    QLabel *label_6;
    QPushButton *bt_change;
    QPushButton *bt_steal_ko;
    QLabel *lb_ft;
    QPushButton *bt_reb_off;
    QPushButton *bt_blk_recv;
    QLabel *lab_t3;
    QLabel *label_3;
    QPushButton *bt_close;
    QPushButton *bt_fauls;

    void setupUi(QDialog *playstat)
    {
        if (playstat->objectName().isEmpty())
            playstat->setObjectName(QStringLiteral("playstat"));
        playstat->setEnabled(true);
        playstat->resize(360, 600);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(playstat->sizePolicy().hasHeightForWidth());
        playstat->setSizePolicy(sizePolicy);
        playstat->setMaximumSize(QSize(360, 16777215));
        gridLayout = new QGridLayout(playstat);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        bt_oth_points = new QPushButton(playstat);
        bt_oth_points->setObjectName(QStringLiteral("bt_oth_points"));

        gridLayout->addWidget(bt_oth_points, 0, 3, 1, 1);

        bt_reb_def = new QPushButton(playstat);
        bt_reb_def->setObjectName(QStringLiteral("bt_reb_def"));
        bt_reb_def->setStyleSheet(QLatin1String("background-color: rgb(170, 255, 127);\n"
"color: rgb(0, 0, 0);"));

        gridLayout->addWidget(bt_reb_def, 7, 0, 1, 1);

        label = new QLabel(playstat);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 7, 1, 1, 1);

        label_4 = new QLabel(playstat);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_4, 6, 1, 1, 1);

        bt_q_indicator = new QPushButton(playstat);
        bt_q_indicator->setObjectName(QStringLiteral("bt_q_indicator"));

        gridLayout->addWidget(bt_q_indicator, 0, 1, 1, 1);

        bt_asst = new QPushButton(playstat);
        bt_asst->setObjectName(QStringLiteral("bt_asst"));
        bt_asst->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 0);\n"
"color: rgb(0, 0, 0);"));

        gridLayout->addWidget(bt_asst, 4, 0, 1, 1);

        label_my_fauls = new QLabel(playstat);
        label_my_fauls->setObjectName(QStringLiteral("label_my_fauls"));
        QFont font;
        font.setPointSize(7);
        label_my_fauls->setFont(font);
        label_my_fauls->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_my_fauls, 1, 0, 1, 1);

        bt_t3_ok = new QPushButton(playstat);
        bt_t3_ok->setObjectName(QStringLiteral("bt_t3_ok"));
        bt_t3_ok->setStyleSheet(QLatin1String("background-color: rgb(170, 255, 127);\n"
"color: rgb(0, 0, 0);"));

        gridLayout->addWidget(bt_t3_ok, 3, 0, 1, 1);

        label_pts = new QLabel(playstat);
        label_pts->setObjectName(QStringLiteral("label_pts"));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        label_pts->setFont(font1);
        label_pts->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_pts, 0, 0, 1, 1);

        bt_undo = new QPushButton(playstat);
        bt_undo->setObjectName(QStringLiteral("bt_undo"));
        bt_undo->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 0);\n"
"color: rgb(0, 0, 0);"));

        gridLayout->addWidget(bt_undo, 8, 0, 1, 1);

        bt_t2_ko = new QPushButton(playstat);
        bt_t2_ko->setObjectName(QStringLiteral("bt_t2_ko"));
        bt_t2_ko->setStyleSheet(QStringLiteral("background-color: rgb(255, 0, 0);"));

        gridLayout->addWidget(bt_t2_ko, 2, 3, 1, 1);

        label_oth_fauls = new QLabel(playstat);
        label_oth_fauls->setObjectName(QStringLiteral("label_oth_fauls"));
        label_oth_fauls->setFont(font);
        label_oth_fauls->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_oth_fauls, 1, 3, 1, 1);

        bt_blocks = new QPushButton(playstat);
        bt_blocks->setObjectName(QStringLiteral("bt_blocks"));
        bt_blocks->setStyleSheet(QLatin1String("background-color: rgb(170, 255, 127);\n"
"color: rgb(0, 0, 127);"));

        gridLayout->addWidget(bt_blocks, 6, 0, 1, 1);

        bt_t3_ko = new QPushButton(playstat);
        bt_t3_ko->setObjectName(QStringLiteral("bt_t3_ko"));
        bt_t3_ko->setStyleSheet(QStringLiteral("background-color: rgb(255, 0, 0);"));

        gridLayout->addWidget(bt_t3_ko, 3, 3, 1, 1);

        lab_t2 = new QLabel(playstat);
        lab_t2->setObjectName(QStringLiteral("lab_t2"));
        lab_t2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lab_t2, 2, 1, 1, 1);

        bt_t2_ok = new QPushButton(playstat);
        bt_t2_ok->setObjectName(QStringLiteral("bt_t2_ok"));
        sizePolicy.setHeightForWidth(bt_t2_ok->sizePolicy().hasHeightForWidth());
        bt_t2_ok->setSizePolicy(sizePolicy);
        bt_t2_ok->setStyleSheet(QLatin1String("background-color: rgb(170, 255, 127);\n"
"color: rgb(0, 0, 0);"));

        gridLayout->addWidget(bt_t2_ok, 2, 0, 1, 1);

        bt_steal_ok = new QPushButton(playstat);
        bt_steal_ok->setObjectName(QStringLiteral("bt_steal_ok"));
        bt_steal_ok->setStyleSheet(QLatin1String("background-color: rgb(170, 255, 127);\n"
"color: rgb(0, 0, 127);"));

        gridLayout->addWidget(bt_steal_ok, 5, 0, 1, 1);

        label_6 = new QLabel(playstat);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_6, 5, 1, 1, 1);

        bt_change = new QPushButton(playstat);
        bt_change->setObjectName(QStringLiteral("bt_change"));
        bt_change->setStyleSheet(QStringLiteral("background-color: rgb(255, 170, 0);"));

        gridLayout->addWidget(bt_change, 1, 1, 1, 1);

        bt_steal_ko = new QPushButton(playstat);
        bt_steal_ko->setObjectName(QStringLiteral("bt_steal_ko"));
        bt_steal_ko->setStyleSheet(QStringLiteral("background-color: rgb(255, 0, 0);"));

        gridLayout->addWidget(bt_steal_ko, 5, 3, 1, 1);

        lb_ft = new QLabel(playstat);
        lb_ft->setObjectName(QStringLiteral("lb_ft"));
        lb_ft->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lb_ft, 8, 1, 1, 1);

        bt_reb_off = new QPushButton(playstat);
        bt_reb_off->setObjectName(QStringLiteral("bt_reb_off"));
        bt_reb_off->setStyleSheet(QLatin1String("background-color: rgb(170, 255, 127);\n"
"color: rgb(0, 0, 0);"));

        gridLayout->addWidget(bt_reb_off, 4, 3, 1, 1);

        bt_blk_recv = new QPushButton(playstat);
        bt_blk_recv->setObjectName(QStringLiteral("bt_blk_recv"));
        bt_blk_recv->setEnabled(true);
        bt_blk_recv->setStyleSheet(QStringLiteral("background-color: rgb(255, 0, 0);"));

        gridLayout->addWidget(bt_blk_recv, 6, 3, 1, 1);

        lab_t3 = new QLabel(playstat);
        lab_t3->setObjectName(QStringLiteral("lab_t3"));
        lab_t3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lab_t3, 3, 1, 1, 1);

        label_3 = new QLabel(playstat);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_3, 4, 1, 1, 1);

        bt_close = new QPushButton(playstat);
        bt_close->setObjectName(QStringLiteral("bt_close"));

        gridLayout->addWidget(bt_close, 8, 3, 1, 1);

        bt_fauls = new QPushButton(playstat);
        bt_fauls->setObjectName(QStringLiteral("bt_fauls"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(bt_fauls->sizePolicy().hasHeightForWidth());
        bt_fauls->setSizePolicy(sizePolicy1);
        bt_fauls->setStyleSheet(QStringLiteral("background-color: rgb(255, 0, 0);"));

        gridLayout->addWidget(bt_fauls, 7, 3, 1, 1);


        retranslateUi(playstat);
        QObject::connect(bt_close, SIGNAL(clicked()), playstat, SLOT(hide()));

        QMetaObject::connectSlotsByName(playstat);
    } // setupUi

    void retranslateUi(QDialog *playstat)
    {
        playstat->setWindowTitle(QApplication::translate("playstat", "Dialog", 0));
        bt_oth_points->setText(QApplication::translate("playstat", "0", 0));
        bt_reb_def->setText(QApplication::translate("playstat", "0", 0));
        label->setText(QApplication::translate("playstat", "DREB", 0));
        label_4->setText(QApplication::translate("playstat", "BLK DONE/RECV", 0));
        bt_q_indicator->setText(QApplication::translate("playstat", "-", 0));
        bt_asst->setText(QApplication::translate("playstat", "0", 0));
        label_my_fauls->setText(QApplication::translate("playstat", "0", 0));
        bt_t3_ok->setText(QApplication::translate("playstat", "0", 0));
        label_pts->setText(QApplication::translate("playstat", "0", 0));
        bt_undo->setText(QApplication::translate("playstat", "Undo", 0));
        bt_t2_ko->setText(QApplication::translate("playstat", "0", 0));
        label_oth_fauls->setText(QApplication::translate("playstat", "0", 0));
        bt_blocks->setText(QApplication::translate("playstat", "0", 0));
        bt_t3_ko->setText(QApplication::translate("playstat", "0", 0));
        lab_t2->setText(QApplication::translate("playstat", "FG2", 0));
        bt_t2_ok->setText(QApplication::translate("playstat", "0", 0));
        bt_steal_ok->setText(QApplication::translate("playstat", "0", 0));
        label_6->setText(QApplication::translate("playstat", "STL / TO", 0));
        bt_change->setText(QApplication::translate("playstat", "Change", 0));
        bt_steal_ko->setText(QApplication::translate("playstat", "0", 0));
        lb_ft->setText(QApplication::translate("playstat", "FT", 0));
        bt_reb_off->setText(QApplication::translate("playstat", "0", 0));
        bt_blk_recv->setText(QApplication::translate("playstat", "0", 0));
        lab_t3->setText(QApplication::translate("playstat", "FG3", 0));
        label_3->setText(QApplication::translate("playstat", "ASST/OREB", 0));
        bt_close->setText(QApplication::translate("playstat", "close", 0));
        bt_fauls->setText(QApplication::translate("playstat", "Fauls", 0));
    } // retranslateUi

};

namespace Ui {
    class playstat: public Ui_playstat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYSTAT_H
