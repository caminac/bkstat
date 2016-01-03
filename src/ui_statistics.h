/********************************************************************************
** Form generated from reading UI file 'statistics.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATISTICS_H
#define UI_STATISTICS_H

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

class Ui_statistics
{
public:
    QGridLayout *gridLayout;
    QLabel *lb_player;
    QPushButton *bt_close;
    QPushButton *bt_next;
    QPushButton *bt_prev;
    QLabel *lb_t1;
    QLabel *lb_t2;
    QLabel *lb_t3;
    QLabel *lb_rimb;
    QLabel *lb_steal_to;
    QLabel *lb_fouls;
    QLabel *lb_stopp;
    QLabel *lb_asst;
    QLabel *lb_points;
    QLabel *lb_val;
    QLabel *lb_min;
    QLabel *lb_plusminus;

    void setupUi(QDialog *statistics)
    {
        if (statistics->objectName().isEmpty())
            statistics->setObjectName(QStringLiteral("statistics"));
        statistics->resize(360, 600);
        gridLayout = new QGridLayout(statistics);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lb_player = new QLabel(statistics);
        lb_player->setObjectName(QStringLiteral("lb_player"));

        gridLayout->addWidget(lb_player, 0, 0, 1, 2);

        bt_close = new QPushButton(statistics);
        bt_close->setObjectName(QStringLiteral("bt_close"));

        gridLayout->addWidget(bt_close, 9, 1, 1, 1);

        bt_next = new QPushButton(statistics);
        bt_next->setObjectName(QStringLiteral("bt_next"));

        gridLayout->addWidget(bt_next, 9, 2, 1, 1);

        bt_prev = new QPushButton(statistics);
        bt_prev->setObjectName(QStringLiteral("bt_prev"));

        gridLayout->addWidget(bt_prev, 9, 0, 1, 1);

        lb_t1 = new QLabel(statistics);
        lb_t1->setObjectName(QStringLiteral("lb_t1"));

        gridLayout->addWidget(lb_t1, 2, 0, 1, 3);

        lb_t2 = new QLabel(statistics);
        lb_t2->setObjectName(QStringLiteral("lb_t2"));

        gridLayout->addWidget(lb_t2, 3, 0, 1, 3);

        lb_t3 = new QLabel(statistics);
        lb_t3->setObjectName(QStringLiteral("lb_t3"));

        gridLayout->addWidget(lb_t3, 4, 0, 1, 3);

        lb_rimb = new QLabel(statistics);
        lb_rimb->setObjectName(QStringLiteral("lb_rimb"));

        gridLayout->addWidget(lb_rimb, 5, 0, 1, 3);

        lb_steal_to = new QLabel(statistics);
        lb_steal_to->setObjectName(QStringLiteral("lb_steal_to"));

        gridLayout->addWidget(lb_steal_to, 6, 0, 1, 3);

        lb_fouls = new QLabel(statistics);
        lb_fouls->setObjectName(QStringLiteral("lb_fouls"));

        gridLayout->addWidget(lb_fouls, 7, 0, 1, 3);

        lb_stopp = new QLabel(statistics);
        lb_stopp->setObjectName(QStringLiteral("lb_stopp"));

        gridLayout->addWidget(lb_stopp, 8, 0, 1, 2);

        lb_asst = new QLabel(statistics);
        lb_asst->setObjectName(QStringLiteral("lb_asst"));

        gridLayout->addWidget(lb_asst, 8, 2, 1, 1);

        lb_points = new QLabel(statistics);
        lb_points->setObjectName(QStringLiteral("lb_points"));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        lb_points->setFont(font);

        gridLayout->addWidget(lb_points, 1, 0, 1, 1);

        lb_val = new QLabel(statistics);
        lb_val->setObjectName(QStringLiteral("lb_val"));

        gridLayout->addWidget(lb_val, 1, 1, 1, 1);

        lb_min = new QLabel(statistics);
        lb_min->setObjectName(QStringLiteral("lb_min"));

        gridLayout->addWidget(lb_min, 1, 2, 1, 1);

        lb_plusminus = new QLabel(statistics);
        lb_plusminus->setObjectName(QStringLiteral("lb_plusminus"));

        gridLayout->addWidget(lb_plusminus, 0, 2, 1, 1);


        retranslateUi(statistics);

        QMetaObject::connectSlotsByName(statistics);
    } // setupUi

    void retranslateUi(QDialog *statistics)
    {
        statistics->setWindowTitle(QApplication::translate("statistics", "Dialog", 0));
        lb_player->setText(QApplication::translate("statistics", "-", 0));
        bt_close->setText(QApplication::translate("statistics", "close", 0));
        bt_next->setText(QApplication::translate("statistics", ">>", 0));
        bt_prev->setText(QApplication::translate("statistics", "<<", 0));
        lb_t1->setText(QApplication::translate("statistics", "-", 0));
        lb_t2->setText(QApplication::translate("statistics", "-", 0));
        lb_t3->setText(QApplication::translate("statistics", "-", 0));
        lb_rimb->setText(QApplication::translate("statistics", "-", 0));
        lb_steal_to->setText(QApplication::translate("statistics", "-", 0));
        lb_fouls->setText(QApplication::translate("statistics", "-", 0));
        lb_stopp->setText(QApplication::translate("statistics", "-", 0));
        lb_asst->setText(QApplication::translate("statistics", "-", 0));
        lb_points->setText(QApplication::translate("statistics", "-", 0));
        lb_val->setText(QApplication::translate("statistics", "-", 0));
        lb_min->setText(QApplication::translate("statistics", "-", 0));
        lb_plusminus->setText(QApplication::translate("statistics", "-", 0));
    } // retranslateUi

};

namespace Ui {
    class statistics: public Ui_statistics {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATISTICS_H
