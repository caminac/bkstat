/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionClose;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLabel *lb_main;
    QPushButton *but_new;
    QPushButton *bt_team;
    QPushButton *but_view;
    QPushButton *bt_field;
    QPushButton *bt_save;
    QPushButton *but_play;
    QPushButton *but_export;
    QPushButton *but_exp_stat;
    QPushButton *bt_load;
    QPushButton *but_del_files;
    QPushButton *bt_help;
    QPushButton *but_del_dirs;
    QPushButton *bt_exit;
    QPushButton *but_options;
    QMenuBar *menuBar;
    QMenu *menuXxx;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(360, 600);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        actionClose->setFont(font);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lb_main = new QLabel(centralWidget);
        lb_main->setObjectName(QStringLiteral("lb_main"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lb_main->sizePolicy().hasHeightForWidth());
        lb_main->setSizePolicy(sizePolicy1);
        lb_main->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        lb_main->setWordWrap(true);

        gridLayout->addWidget(lb_main, 0, 0, 1, 1);

        but_new = new QPushButton(centralWidget);
        but_new->setObjectName(QStringLiteral("but_new"));
        QFont font1;
        font1.setPointSize(9);
        font1.setBold(true);
        font1.setWeight(75);
        but_new->setFont(font1);

        gridLayout->addWidget(but_new, 1, 0, 1, 1);

        bt_team = new QPushButton(centralWidget);
        bt_team->setObjectName(QStringLiteral("bt_team"));
        bt_team->setFont(font1);

        gridLayout->addWidget(bt_team, 1, 1, 1, 1);

        but_view = new QPushButton(centralWidget);
        but_view->setObjectName(QStringLiteral("but_view"));
        but_view->setFont(font1);

        gridLayout->addWidget(but_view, 2, 0, 1, 1);

        bt_field = new QPushButton(centralWidget);
        bt_field->setObjectName(QStringLiteral("bt_field"));
        bt_field->setFont(font1);

        gridLayout->addWidget(bt_field, 2, 1, 1, 1);

        bt_save = new QPushButton(centralWidget);
        bt_save->setObjectName(QStringLiteral("bt_save"));
        bt_save->setFont(font1);

        gridLayout->addWidget(bt_save, 3, 0, 1, 1);

        but_play = new QPushButton(centralWidget);
        but_play->setObjectName(QStringLiteral("but_play"));
        but_play->setFont(font1);
        but_play->setStyleSheet(QStringLiteral("background-color: rgb(255, 170, 0);"));

        gridLayout->addWidget(but_play, 3, 1, 1, 1);

        but_export = new QPushButton(centralWidget);
        but_export->setObjectName(QStringLiteral("but_export"));
        but_export->setFont(font1);

        gridLayout->addWidget(but_export, 4, 0, 1, 1);

        but_exp_stat = new QPushButton(centralWidget);
        but_exp_stat->setObjectName(QStringLiteral("but_exp_stat"));
        but_exp_stat->setEnabled(false);
        but_exp_stat->setFont(font1);

        gridLayout->addWidget(but_exp_stat, 4, 1, 1, 1);

        bt_load = new QPushButton(centralWidget);
        bt_load->setObjectName(QStringLiteral("bt_load"));
        bt_load->setFont(font1);

        gridLayout->addWidget(bt_load, 5, 0, 1, 1);

        but_del_files = new QPushButton(centralWidget);
        but_del_files->setObjectName(QStringLiteral("but_del_files"));

        gridLayout->addWidget(but_del_files, 5, 1, 1, 1);

        bt_help = new QPushButton(centralWidget);
        bt_help->setObjectName(QStringLiteral("bt_help"));
        bt_help->setFont(font1);

        gridLayout->addWidget(bt_help, 6, 0, 1, 1);

        but_del_dirs = new QPushButton(centralWidget);
        but_del_dirs->setObjectName(QStringLiteral("but_del_dirs"));
        but_del_dirs->setEnabled(false);

        gridLayout->addWidget(but_del_dirs, 6, 1, 1, 1);

        bt_exit = new QPushButton(centralWidget);
        bt_exit->setObjectName(QStringLiteral("bt_exit"));
        bt_exit->setFont(font1);

        gridLayout->addWidget(bt_exit, 7, 0, 1, 1);

        but_options = new QPushButton(centralWidget);
        but_options->setObjectName(QStringLiteral("but_options"));
        but_options->setEnabled(true);
        QFont font2;
        font2.setBold(false);
        font2.setWeight(50);
        but_options->setFont(font2);

        gridLayout->addWidget(but_options, 7, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 360, 20));
        menuXxx = new QMenu(menuBar);
        menuXxx->setObjectName(QStringLiteral("menuXxx"));
        MainWindow->setMenuBar(menuBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menuBar->addAction(menuXxx->menuAction());

        retranslateUi(MainWindow);
        // ? error on 5.5.1
        // QObject::connect(actionClose, SIGNAL(activated()), MainWindow, SLOT(close()));
        QObject::connect(bt_exit, SIGNAL(clicked()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionClose->setText(QApplication::translate("MainWindow", "Close", 0));
        lb_main->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        but_new->setText(QApplication::translate("MainWindow", "start", 0));
        bt_team->setText(QApplication::translate("MainWindow", "team", 0));
        but_view->setText(QApplication::translate("MainWindow", "view", 0));
        bt_field->setText(QApplication::translate("MainWindow", "Field", 0));
        bt_save->setText(QApplication::translate("MainWindow", "Save", 0));
        but_play->setText(QApplication::translate("MainWindow", "play", 0));
        but_export->setText(QApplication::translate("MainWindow", "export", 0));
        but_exp_stat->setText(QString());
        bt_load->setText(QApplication::translate("MainWindow", "Load", 0));
        but_del_files->setText(QApplication::translate("MainWindow", "Maintenance", 0));
        bt_help->setText(QApplication::translate("MainWindow", "Help", 0));
        but_del_dirs->setText(QString());
        bt_exit->setText(QApplication::translate("MainWindow", "exit", 0));
        but_options->setText(QApplication::translate("MainWindow", "Options", 0));
        menuXxx->setTitle(QApplication::translate("MainWindow", "File", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
