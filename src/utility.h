#ifndef UTILITY_H
#define UTILITY_H

#include <QWidget>
#include <QString>

#define IMPORT_WILDCHAR ("*.tm")
#define IMPORT_EXTENSION (".tm")
#define IMPORT_EXPORT_DIR ("C:/Data/")

class Utility
{
public:
    Utility();
    static QString selectFile(QWidget * parent, QString dir, QString ext, QString msg1, QString msg2);
};

#endif // UTILITY_H
