/********************************************************************************
** Form generated from reading UI file 'teamselection.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEAMSELECTION_H
#define UI_TEAMSELECTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_teamselection
{
public:
    QLabel *label;
    QPushButton *bt_add;
    QPushButton *bt_delete;
    QPushButton *bt_edit;
    QPlainTextEdit *player_name;
    QSpinBox *sb_number;
    QListWidget *list_team;
    QPushButton *bt_close;
    QPushButton *bt_load_file;
    QPushButton *bt_store_file;
    QPushButton *bt_import_file;

    void setupUi(QDialog *teamselection)
    {
        if (teamselection->objectName().isEmpty())
            teamselection->setObjectName(QStringLiteral("teamselection"));
        teamselection->resize(360, 600);
        label = new QLabel(teamselection);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 30, 211, 24));
        QFont font;
        font.setPointSize(8);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        bt_add = new QPushButton(teamselection);
        bt_add->setObjectName(QStringLiteral("bt_add"));
        bt_add->setGeometry(QRect(10, 120, 101, 31));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        bt_add->setFont(font1);
        bt_add->setStyleSheet(QLatin1String("background-color: rgb(0, 255, 0);\n"
"color: rgb(0, 0, 255);"));
        bt_delete = new QPushButton(teamselection);
        bt_delete->setObjectName(QStringLiteral("bt_delete"));
        bt_delete->setGeometry(QRect(269, 120, 71, 31));
        bt_delete->setFont(font1);
        bt_delete->setStyleSheet(QStringLiteral("background-color: rgb(255, 170, 0);"));
        bt_edit = new QPushButton(teamselection);
        bt_edit->setObjectName(QStringLiteral("bt_edit"));
        bt_edit->setEnabled(false);
        bt_edit->setGeometry(QRect(140, 120, 75, 31));
        bt_edit->setFont(font);
        player_name = new QPlainTextEdit(teamselection);
        player_name->setObjectName(QStringLiteral("player_name"));
        player_name->setGeometry(QRect(130, 160, 221, 41));
        QFont font2;
        font2.setPointSize(8);
        font2.setBold(false);
        font2.setWeight(50);
        player_name->setFont(font2);
        player_name->setUndoRedoEnabled(true);
        player_name->setLineWrapMode(QPlainTextEdit::NoWrap);
        player_name->setTextInteractionFlags(Qt::TextEditable);
        sb_number = new QSpinBox(teamselection);
        sb_number->setObjectName(QStringLiteral("sb_number"));
        sb_number->setGeometry(QRect(10, 160, 111, 41));
        sb_number->setFont(font);
        sb_number->setMinimum(4);
        list_team = new QListWidget(teamselection);
        list_team->setObjectName(QStringLiteral("list_team"));
        list_team->setGeometry(QRect(10, 210, 341, 281));
        list_team->setFont(font);
        list_team->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        list_team->setDragDropMode(QAbstractItemView::InternalMove);
        list_team->setAlternatingRowColors(true);
        bt_close = new QPushButton(teamselection);
        bt_close->setObjectName(QStringLiteral("bt_close"));
        bt_close->setGeometry(QRect(239, 23, 101, 31));
        QFont font3;
        font3.setPointSize(9);
        font3.setBold(true);
        font3.setWeight(75);
        bt_close->setFont(font3);
        bt_load_file = new QPushButton(teamselection);
        bt_load_file->setObjectName(QStringLiteral("bt_load_file"));
        bt_load_file->setGeometry(QRect(10, 73, 101, 31));
        bt_load_file->setFont(font3);
        bt_load_file->setStyleSheet(QLatin1String("background-color: rgb(0, 255, 0);\n"
"color: rgb(0, 0, 255);"));
        bt_store_file = new QPushButton(teamselection);
        bt_store_file->setObjectName(QStringLiteral("bt_store_file"));
        bt_store_file->setGeometry(QRect(240, 73, 101, 31));
        bt_store_file->setFont(font);
        bt_import_file = new QPushButton(teamselection);
        bt_import_file->setObjectName(QStringLiteral("bt_import_file"));
        bt_import_file->setGeometry(QRect(124, 72, 111, 31));
        bt_import_file->setFont(font);

        retranslateUi(teamselection);

        QMetaObject::connectSlotsByName(teamselection);
    } // setupUi

    void retranslateUi(QDialog *teamselection)
    {
        teamselection->setWindowTitle(QApplication::translate("teamselection", "Dialog", 0));
        label->setText(QApplication::translate("teamselection", "Add Players", 0));
        bt_add->setText(QApplication::translate("teamselection", "+", 0));
        bt_delete->setText(QApplication::translate("teamselection", "-", 0));
        bt_edit->setText(QApplication::translate("teamselection", "Edit", 0));
        bt_close->setText(QApplication::translate("teamselection", "close", 0));
        bt_load_file->setText(QApplication::translate("teamselection", "Load", 0));
        bt_store_file->setText(QApplication::translate("teamselection", "Store", 0));
        bt_import_file->setText(QApplication::translate("teamselection", "Import", 0));
    } // retranslateUi

};

namespace Ui {
    class teamselection: public Ui_teamselection {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEAMSELECTION_H
