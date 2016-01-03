#include "setup.h"
#include "info.h"
#include "mainwindow.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QApplication>
#include <QTranslator>
#include <QDir>
#include <QFile>
#include <QLocale>
#include <QSettings>
#include <QDesktopWidget>
#include <QRect>

QString makeTranslationFilename( QString language );

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTranslator translator;
    QLocale     loc = QLocale::system();
    QString     str = QDir::currentPath(), language, forced_language, tmp, transl_file;
    QString     inifile = p_resource_prefix + (".ini");
    QSettings settings(inifile,QSettings::IniFormat);
    // QRect rect = QDesktopWidget.screenGeometry();
    int width,height;

    forced_language = settings.value("core/language","").toString();
    if( forced_language == "" ){
        tmp = loc.name();
        language = tmp.left(2);
    }else{
        language = forced_language;
    }
    transl_file = makeTranslationFilename(language);

    if( language != "en" ){
        if(!QFile::exists(transl_file)){
#ifdef DEBUG_VERSION
            QString msg = QString("can't find ") + transl_file;
            QMessageBox msgBox;
            msgBox.setText(msg);
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.exec();
#endif
        }else{
            bool check = translator.load(transl_file,str);
            if( check ){
                app.installTranslator(&translator);
            }
        }
    }

    //width = rect.width();
    //height = rect.height();
    //if( width == 640 ){
        //QSize size = settings.value("size", QSize(width, height)).toSize();
        //mainWindow.setOrientation(MainWindow::ScreenOrientationLockLandscape);
    //}
    MainWindow w(&settings);
    w.show();
    //mainWindow.resize(size);
    // mainWindow.setOrientation(MainWindow::ScreenOrientationAuto);
    //mainWindow.setOrientation(MainWindow::ScreenOrientationLockPortrait);
    //mainWindow.showExpanded();
    return app.exec();
}

QString makeTranslationFilename( QString language )
{
    QString str = QDir::currentPath();
    QString transl_file;
#ifdef Q_OS_SYMBIAN
    transl_file = QString("C:/resource/apps/") + p_resource_prefix + "_" + language + ".qm";
#else
    transl_file = str + "/" + p_translation_file + "_" + language + ".qm";
#endif
    return transl_file;
}
