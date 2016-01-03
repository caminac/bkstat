/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Sun 8. Jul 23:47:49 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      33,   11,   11,   11, 0x08,
      55,   11,   11,   11, 0x08,
      77,   11,   11,   11, 0x08,
      98,   11,   11,   11, 0x08,
     120,   11,   11,   11, 0x08,
     141,   11,   11,   11, 0x08,
     162,   11,   11,   11, 0x08,
     183,   11,   11,   11, 0x08,
     207,   11,   11,   11, 0x08,
     233,   11,   11,   11, 0x08,
     260,   11,   11,   11, 0x08,
     285,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0on_but_new_clicked()\0"
    "on_but_view_clicked()\0on_but_play_clicked()\0"
    "on_bt_team_clicked()\0on_bt_field_clicked()\0"
    "on_bt_help_clicked()\0on_bt_save_clicked()\0"
    "on_bt_load_clicked()\0on_but_export_clicked()\0"
    "on_but_exp_stat_clicked()\0"
    "on_but_del_files_clicked()\0"
    "on_but_options_clicked()\0"
    "on_but_del_dirs_clicked()\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_but_new_clicked(); break;
        case 1: on_but_view_clicked(); break;
        case 2: on_but_play_clicked(); break;
        case 3: on_bt_team_clicked(); break;
        case 4: on_bt_field_clicked(); break;
        case 5: on_bt_help_clicked(); break;
        case 6: on_bt_save_clicked(); break;
        case 7: on_bt_load_clicked(); break;
        case 8: on_but_export_clicked(); break;
        case 9: on_but_exp_stat_clicked(); break;
        case 10: on_but_del_files_clicked(); break;
        case 11: on_but_options_clicked(); break;
        case 12: on_but_del_dirs_clicked(); break;
        default: ;
        }
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
