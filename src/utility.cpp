#include "utility.h"
#include <QDir>
#include <QInputDialog>

Utility::Utility()
{
}

QString Utility::selectFile(QWidget * parent, QString dir, QString ext, QString msg1, QString msg2)
{
    QString   x = "";
    QDir workdir(dir);
    QStringList filter;
    filter << ext;
    workdir.setNameFilters(filter);
    QStringList list = workdir.entryList(filter, QDir::Files, QDir::Name);

    if( list.size() > 0 ){
        bool ok;
        QString item = QInputDialog::getItem(parent, msg1, msg2, list, 0, false, &ok);
        if (ok && !item.isEmpty()){
            x = item;
        }
    }
    return x;
}
