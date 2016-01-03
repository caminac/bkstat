# Add files and directories to ship with the application 
# by adapting the examples below.
# file1.source = myfile
# dir1.source = mydir
DEPLOYMENTFOLDERS = # file1 dir1

#symbian:TARGET.UID3 = 0x200628E9

# Smart Installer package's UID
# This UID is from the protected range 
# and therefore the package will fail to install if self-signed
# By default qmake uses the unprotected range value if unprotected UID is defined for the application
# and 0x2002CCCF value if protected UID is given to the application
#symbian:DEPLOYMENT.installer_header = 0x2002CCCF

# Allow network access on Symbian
#symbian:TARGET.CAPABILITY +=
#NetworkServices
#INCLUDEPATH += C:\mobile\Qt\Qt5.4.0\5.4\mingw491_32\include\QtWidgets
# If your application uses the Qt Mobility libraries, uncomment
# the following lines and add the respective components to the 
# MOBILITY variable. 
# CONFIG += mobility
# MOBILITY +=
QT += widgets

#DEFINES += DEMO_VERSION=0
SOURCES += main.cpp mainwindow.cpp \
    newgame.cpp \
    scorer.cpp \
    teamselection.cpp \
    playstat.cpp \
    players.cpp \
    faul_menu.cpp \
    statistics.cpp \
    info.cpp \
    dlg_options.cpp \
    gametime.cpp \
    playtimedata.cpp \
    utility.cpp \
    oth_points_menu.cpp
HEADERS += mainwindow.h \
    newgame.h \
    ifStore.h \
    ifViewer.h \
    scorer.h \
    types.h \
    teamselection.h \
    playstat.h \
    players.h \
    faul_menu.h \
    statistics.h \
    info.h \
    dlg_options.h \
    setup.h \
    gametime.h \
    playtimedata.h \
    utility.h \
    oth_points_menu.h
FORMS += mainwindow.ui \
    newgame.ui \
    teamselection.ui \
    playstat.ui \
    players.ui \
    faul_menu.ui \
    statistics.ui \
    dlg_options.ui \
    oth_points_menu.ui
TRANSLATIONS = bkstat_it.ts \
               bkstat_fr.ts \
               bkstat_es.ts \
               bkstat_de.ts \
               bkstat_pt.ts \
               bkstat_ru.ts

#include(mypkgrules.pri)
# Please do not modify the following two lines. Required for deployment.
#include(deploymentfull.pri)
#qtcAddDeployment()

#OTHER_FILES += \
#    android/AndroidManifest.xml \
#    android/res/drawable/icon.png \
#    android/res/drawable/logo.png \
#    android/res/drawable-hdpi/icon.png \
#    android/res/drawable-ldpi/icon.png \
#    android/res/drawable-mdpi/icon.png \
#    android/res/layout/splash.xml \
#    android/res/values/libs.xml \
#    android/res/values/strings.xml \
#    android/res/values-de/strings.xml \
#    android/res/values-el/strings.xml \
#    android/res/values-es/strings.xml \
#    android/res/values-et/strings.xml \
#    android/res/values-fa/strings.xml \
#    android/res/values-fr/strings.xml \
#    android/res/values-id/strings.xml \
#    android/res/values-it/strings.xml \
#    android/res/values-ja/strings.xml \
#    android/res/values-ms/strings.xml \
#    android/res/values-nb/strings.xml \
#    android/res/values-nl/strings.xml \
#    android/res/values-pl/strings.xml \
#    android/res/values-pt-rBR/strings.xml \
#    android/res/values-ro/strings.xml \
#    android/res/values-rs/strings.xml \
#    android/res/values-ru/strings.xml \
#    android/res/values-zh-rCN/strings.xml \
#    android/res/values-zh-rTW/strings.xml \
#    android/src/org/kde/necessitas/ministro/IMinistro.aidl \
#    android/src/org/kde/necessitas/ministro/IMinistroCallback.aidl \
#    android/src/org/kde/necessitas/origo/QtActivity.java \
#    android/src/org/kde/necessitas/origo/QtApplication.java \
#    android/version.xml
