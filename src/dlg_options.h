#ifndef DLG_OPTIONS_H
#define DLG_OPTIONS_H

#include <QDialog>
#include <QSettings>

namespace Ui {
    class dlg_options;
}

class dlg_options : public QDialog
{
    Q_OBJECT

public:
    explicit dlg_options(QSettings *settings, QString l = "en", QWidget *parent = 0);
    ~dlg_options();

    void set_export_dir(QString dir);
    QString GetExportDirectory(){return m_export_dir;};

private slots:
    void on_but_export_loc_clicked();

    void on_pushButton_clicked();

    void on_but_set_lang_clicked();

private:
    Ui::dlg_options *ui;

    QSettings *m_settings;
    QString   m_language, m_export_dir;
};

#endif // DLG_OPTIONS_H
