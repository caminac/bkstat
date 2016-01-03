/********************************************************************************
** Form generated from reading UI file 'newgame.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWGAME_H
#define UI_NEWGAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_newgame
{
public:
    QLabel *label_otherteam;
    QPlainTextEdit *text_team;
    QLabel *lb_current_date;
    QPushButton *bt_ok;
    QComboBox *cb_duration_q;
    QLabel *label_qduration;
    QLabel *label_otduration;
    QComboBox *cb_duration_ot;
    QLabel *label;
    QPlainTextEdit *text_gameid;
    QLabel *label_location;
    QPlainTextEdit *text_location;

    void setupUi(QDialog *newgame)
    {
        if (newgame->objectName().isEmpty())
            newgame->setObjectName(QStringLiteral("newgame"));
        newgame->resize(360, 600);
        label_otherteam = new QLabel(newgame);
        label_otherteam->setObjectName(QStringLiteral("label_otherteam"));
        label_otherteam->setGeometry(QRect(10, 69, 331, 40));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        label_otherteam->setFont(font);
        text_team = new QPlainTextEdit(newgame);
        text_team->setObjectName(QStringLiteral("text_team"));
        text_team->setGeometry(QRect(10, 120, 341, 40));
        QFont font1;
        font1.setPointSize(8);
        font1.setBold(false);
        font1.setWeight(50);
        text_team->setFont(font1);
        text_team->setStyleSheet(QLatin1String("background-color: rgb(85, 170, 255);\n"
"color: rgb(255, 255, 127);"));
        text_team->setFrameShadow(QFrame::Raised);
        text_team->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        text_team->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        text_team->setUndoRedoEnabled(true);
        text_team->setLineWrapMode(QPlainTextEdit::NoWrap);
        text_team->setTextInteractionFlags(Qt::TextEditorInteraction);
        lb_current_date = new QLabel(newgame);
        lb_current_date->setObjectName(QStringLiteral("lb_current_date"));
        lb_current_date->setGeometry(QRect(10, 24, 270, 40));
        QFont font2;
        font2.setPointSize(10);
        lb_current_date->setFont(font2);
        bt_ok = new QPushButton(newgame);
        bt_ok->setObjectName(QStringLiteral("bt_ok"));
        bt_ok->setGeometry(QRect(140, 424, 75, 31));
        bt_ok->setFont(font);
        cb_duration_q = new QComboBox(newgame);
        cb_duration_q->setObjectName(QStringLiteral("cb_duration_q"));
        cb_duration_q->setGeometry(QRect(278, 309, 71, 31));
        cb_duration_q->setFont(font2);
        label_qduration = new QLabel(newgame);
        label_qduration->setObjectName(QStringLiteral("label_qduration"));
        label_qduration->setGeometry(QRect(9, 316, 271, 31));
        QFont font3;
        font3.setPointSize(8);
        label_qduration->setFont(font3);
        label_otduration = new QLabel(newgame);
        label_otduration->setObjectName(QStringLiteral("label_otduration"));
        label_otduration->setGeometry(QRect(10, 364, 271, 31));
        label_otduration->setFont(font3);
        cb_duration_ot = new QComboBox(newgame);
        cb_duration_ot->setObjectName(QStringLiteral("cb_duration_ot"));
        cb_duration_ot->setGeometry(QRect(278, 358, 71, 31));
        cb_duration_ot->setFont(font2);
        label = new QLabel(newgame);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 175, 121, 41));
        text_gameid = new QPlainTextEdit(newgame);
        text_gameid->setObjectName(QStringLiteral("text_gameid"));
        text_gameid->setGeometry(QRect(150, 170, 201, 40));
        text_gameid->setFont(font3);
        text_gameid->setStyleSheet(QLatin1String("background-color: rgb(85, 85, 255);\n"
"color: rgb(255, 255, 0);"));
        text_gameid->setFrameShadow(QFrame::Raised);
        text_gameid->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        text_gameid->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        text_gameid->setLineWrapMode(QPlainTextEdit::NoWrap);
        text_gameid->setTextInteractionFlags(Qt::TextEditorInteraction);
        label_location = new QLabel(newgame);
        label_location->setObjectName(QStringLiteral("label_location"));
        label_location->setGeometry(QRect(10, 225, 131, 41));
        text_location = new QPlainTextEdit(newgame);
        text_location->setObjectName(QStringLiteral("text_location"));
        text_location->setGeometry(QRect(150, 220, 201, 40));
        text_location->setFont(font3);
        text_location->setStyleSheet(QLatin1String("background-color: rgb(85, 85, 255);\n"
"color: rgb(255, 255, 0);"));
        text_location->setFrameShadow(QFrame::Raised);
        text_location->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        text_location->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        text_location->setLineWrapMode(QPlainTextEdit::NoWrap);

        retranslateUi(newgame);
        QObject::connect(bt_ok, SIGNAL(clicked()), newgame, SLOT(close()));

        QMetaObject::connectSlotsByName(newgame);
    } // setupUi

    void retranslateUi(QDialog *newgame)
    {
        newgame->setWindowTitle(QApplication::translate("newgame", "Dialog", 0));
        label_otherteam->setText(QApplication::translate("newgame", "Opponent Team", 0));
        lb_current_date->setText(QApplication::translate("newgame", "-", 0));
        bt_ok->setText(QApplication::translate("newgame", "OK", 0));
        cb_duration_q->clear();
        cb_duration_q->insertItems(0, QStringList()
         << QApplication::translate("newgame", "10", 0)
         << QApplication::translate("newgame", "8", 0)
         << QApplication::translate("newgame", "12", 0)
        );
        label_qduration->setText(QApplication::translate("newgame", "Quarter duration (min)", 0));
        label_otduration->setText(QApplication::translate("newgame", "Overtime duration (min)", 0));
        cb_duration_ot->clear();
        cb_duration_ot->insertItems(0, QStringList()
         << QApplication::translate("newgame", "5", 0)
         << QApplication::translate("newgame", "3", 0)
         << QApplication::translate("newgame", "6", 0)
        );
        label->setText(QApplication::translate("newgame", "Game id", 0));
        label_location->setText(QApplication::translate("newgame", "Location", 0));
    } // retranslateUi

};

namespace Ui {
    class newgame: public Ui_newgame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWGAME_H
