/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[16];
    char stringdata0[304];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 18), // "on_but_new_clicked"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 19), // "on_but_view_clicked"
QT_MOC_LITERAL(4, 51, 19), // "on_but_play_clicked"
QT_MOC_LITERAL(5, 71, 18), // "on_bt_team_clicked"
QT_MOC_LITERAL(6, 90, 19), // "on_bt_field_clicked"
QT_MOC_LITERAL(7, 110, 18), // "on_bt_help_clicked"
QT_MOC_LITERAL(8, 129, 18), // "on_bt_save_clicked"
QT_MOC_LITERAL(9, 148, 18), // "on_bt_load_clicked"
QT_MOC_LITERAL(10, 167, 21), // "on_but_export_clicked"
QT_MOC_LITERAL(11, 189, 23), // "on_but_exp_stat_clicked"
QT_MOC_LITERAL(12, 213, 24), // "on_but_del_files_clicked"
QT_MOC_LITERAL(13, 238, 22), // "on_but_options_clicked"
QT_MOC_LITERAL(14, 261, 23), // "on_but_del_dirs_clicked"
QT_MOC_LITERAL(15, 285, 18) // "on_bt_exit_clicked"

    },
    "MainWindow\0on_but_new_clicked\0\0"
    "on_but_view_clicked\0on_but_play_clicked\0"
    "on_bt_team_clicked\0on_bt_field_clicked\0"
    "on_bt_help_clicked\0on_bt_save_clicked\0"
    "on_bt_load_clicked\0on_but_export_clicked\0"
    "on_but_exp_stat_clicked\0"
    "on_but_del_files_clicked\0"
    "on_but_options_clicked\0on_but_del_dirs_clicked\0"
    "on_bt_exit_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    0,   85,    2, 0x08 /* Private */,
       4,    0,   86,    2, 0x08 /* Private */,
       5,    0,   87,    2, 0x08 /* Private */,
       6,    0,   88,    2, 0x08 /* Private */,
       7,    0,   89,    2, 0x08 /* Private */,
       8,    0,   90,    2, 0x08 /* Private */,
       9,    0,   91,    2, 0x08 /* Private */,
      10,    0,   92,    2, 0x08 /* Private */,
      11,    0,   93,    2, 0x08 /* Private */,
      12,    0,   94,    2, 0x08 /* Private */,
      13,    0,   95,    2, 0x08 /* Private */,
      14,    0,   96,    2, 0x08 /* Private */,
      15,    0,   97,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_but_new_clicked(); break;
        case 1: _t->on_but_view_clicked(); break;
        case 2: _t->on_but_play_clicked(); break;
        case 3: _t->on_bt_team_clicked(); break;
        case 4: _t->on_bt_field_clicked(); break;
        case 5: _t->on_bt_help_clicked(); break;
        case 6: _t->on_bt_save_clicked(); break;
        case 7: _t->on_bt_load_clicked(); break;
        case 8: _t->on_but_export_clicked(); break;
        case 9: _t->on_but_exp_stat_clicked(); break;
        case 10: _t->on_but_del_files_clicked(); break;
        case 11: _t->on_but_options_clicked(); break;
        case 12: _t->on_but_del_dirs_clicked(); break;
        case 13: _t->on_bt_exit_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
