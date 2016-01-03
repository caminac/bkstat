/********************************************************************************
** Form generated from reading UI file 'dlg_options.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLG_OPTIONS_H
#define UI_DLG_OPTIONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_dlg_options
{
public:
    QFormLayout *formLayout;
    QPushButton *but_export_loc;
    QLabel *lb_exp_dir;
    QPushButton *pushButton;
    QPushButton *but_set_lang;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *dlg_options)
    {
        if (dlg_options->objectName().isEmpty())
            dlg_options->setObjectName(QStringLiteral("dlg_options"));
        dlg_options->resize(360, 600);
        formLayout = new QFormLayout(dlg_options);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        but_export_loc = new QPushButton(dlg_options);
        but_export_loc->setObjectName(QStringLiteral("but_export_loc"));

        formLayout->setWidget(0, QFormLayout::LabelRole, but_export_loc);

        lb_exp_dir = new QLabel(dlg_options);
        lb_exp_dir->setObjectName(QStringLiteral("lb_exp_dir"));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setBold(true);
        font.setWeight(75);
        lb_exp_dir->setFont(font);

        formLayout->setWidget(1, QFormLayout::LabelRole, lb_exp_dir);

        pushButton = new QPushButton(dlg_options);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        formLayout->setWidget(2, QFormLayout::LabelRole, pushButton);

        but_set_lang = new QPushButton(dlg_options);
        but_set_lang->setObjectName(QStringLiteral("but_set_lang"));

        formLayout->setWidget(5, QFormLayout::LabelRole, but_set_lang);

        buttonBox = new QDialogButtonBox(dlg_options);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        formLayout->setWidget(6, QFormLayout::LabelRole, buttonBox);


        retranslateUi(dlg_options);
        QObject::connect(buttonBox, SIGNAL(accepted()), dlg_options, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), dlg_options, SLOT(reject()));

        QMetaObject::connectSlotsByName(dlg_options);
    } // setupUi

    void retranslateUi(QDialog *dlg_options)
    {
        dlg_options->setWindowTitle(QApplication::translate("dlg_options", "Dialog", 0));
        but_export_loc->setText(QApplication::translate("dlg_options", "set export location", 0));
        lb_exp_dir->setText(QApplication::translate("dlg_options", "-", 0));
        pushButton->setText(QApplication::translate("dlg_options", "info", 0));
        but_set_lang->setText(QApplication::translate("dlg_options", "language", 0));
    } // retranslateUi

};

namespace Ui {
    class dlg_options: public Ui_dlg_options {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLG_OPTIONS_H
