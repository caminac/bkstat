#include "dlg_options.h"
#include "ui_dlg_options.h"
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include <QInputDialog>
#include "utility.h"

dlg_options::dlg_options(QSettings *settings, QString l, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlg_options)
{
    ui->setupUi(this);
    m_settings = settings;
    m_language = l;
    m_export_dir = IMPORT_EXPORT_DIR;
}

dlg_options::~dlg_options()
{
    delete ui;
}

void dlg_options::on_but_export_loc_clicked()
{
#if defined(DEMO_VERSION)
    warnForVersion();
#else
    bool            ok;
    int             i, n;
    QFileInfo       tmp;
    QFileInfoList   list = QDir::drives();
    QStringList     items;
    n = list.size();
    for( i=0; i<n; i++ ){
        tmp = list.at(i);
        if( tmp.isWritable() ){
            items.append(tmp.absoluteFilePath());
        }
    }
    items.append(IMPORT_EXPORT_DIR);
    QString item = QInputDialog::getItem(this, tr("Select export location"),
                                         tr("Drive:"), items, 0, false, &ok);
    if(ok && !item.isEmpty()){
        set_export_dir(item);
        m_export_dir = item;
    }
#endif
}

void dlg_options::set_export_dir(QString dir)
{
    ui->lb_exp_dir->setText(dir);
}

void dlg_options::on_pushButton_clicked()
{
    QLocale loc = QLocale::system();
    QString msg,
            str = QDir::currentPath();
    QString l_str = loc.languageToString (loc.language());

    msg = loc.name() + "\n" + str + "\n" + l_str + "\n" + __DATE__ + "\n" + __TIME__;
    QMessageBox msgBox;
    msgBox.setText(msg);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}

void dlg_options::on_but_set_lang_clicked()
{
    QString    msg1, msg2, msg3;
    QStringList list;
    list.append("en");
    list.append("it");
    list.append("fr");
    list.append("es");
    list.append("ru");

    msg1 = tr("Current language is ") + m_language;
    msg2 = tr("Select new language: ");
    if( list.size() > 0 ){
        bool ok;
        QString item = QInputDialog::getItem(this, msg1, msg2, list, 0, false, &ok);
        if (ok && !item.isEmpty()){
            m_settings->setValue("core/language",item);
            msg3 = tr("New language set to ") + item + tr(" restart to apply");
            QMessageBox msgBox;
            msgBox.setText(msg3);
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.exec();
        }
    }
}
