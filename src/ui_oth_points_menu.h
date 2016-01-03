/********************************************************************************
** Form generated from reading UI file 'oth_points_menu.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OTH_POINTS_MENU_H
#define UI_OTH_POINTS_MENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_oth_points_menu
{
public:
    QFormLayout *formLayout;
    QLabel *label_title;
    QRadioButton *rb_1;
    QRadioButton *rb_2;
    QRadioButton *rb_3;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *oth_points_menu)
    {
        if (oth_points_menu->objectName().isEmpty())
            oth_points_menu->setObjectName(QStringLiteral("oth_points_menu"));
        oth_points_menu->resize(360, 600);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(oth_points_menu->sizePolicy().hasHeightForWidth());
        oth_points_menu->setSizePolicy(sizePolicy);
        formLayout = new QFormLayout(oth_points_menu);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label_title = new QLabel(oth_points_menu);
        label_title->setObjectName(QStringLiteral("label_title"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_title);

        rb_1 = new QRadioButton(oth_points_menu);
        rb_1->setObjectName(QStringLiteral("rb_1"));
        QFont font;
        font.setPointSize(10);
        rb_1->setFont(font);
        rb_1->setText(QStringLiteral("1"));

        formLayout->setWidget(1, QFormLayout::LabelRole, rb_1);

        rb_2 = new QRadioButton(oth_points_menu);
        rb_2->setObjectName(QStringLiteral("rb_2"));
        rb_2->setFont(font);
        rb_2->setText(QStringLiteral("2"));

        formLayout->setWidget(2, QFormLayout::LabelRole, rb_2);

        rb_3 = new QRadioButton(oth_points_menu);
        rb_3->setObjectName(QStringLiteral("rb_3"));
        rb_3->setFont(font);
        rb_3->setText(QStringLiteral("3"));

        formLayout->setWidget(3, QFormLayout::LabelRole, rb_3);

        buttonBox = new QDialogButtonBox(oth_points_menu);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        formLayout->setWidget(4, QFormLayout::LabelRole, buttonBox);


        retranslateUi(oth_points_menu);
        QObject::connect(buttonBox, SIGNAL(accepted()), oth_points_menu, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), oth_points_menu, SLOT(reject()));

        QMetaObject::connectSlotsByName(oth_points_menu);
    } // setupUi

    void retranslateUi(QDialog *oth_points_menu)
    {
        oth_points_menu->setWindowTitle(QApplication::translate("oth_points_menu", "Dialog", 0));
        label_title->setText(QApplication::translate("oth_points_menu", "Points for other team:", 0));
    } // retranslateUi

};

namespace Ui {
    class oth_points_menu: public Ui_oth_points_menu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OTH_POINTS_MENU_H
