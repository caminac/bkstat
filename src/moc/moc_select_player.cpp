/****************************************************************************
** Meta object code from reading C++ file 'select_player.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../select_player.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'select_player.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_select_player_t {
    QByteArrayData data[7];
    char stringdata0[105];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_select_player_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_select_player_t qt_meta_stringdata_select_player = {
    {
QT_MOC_LITERAL(0, 0, 13), // "select_player"
QT_MOC_LITERAL(1, 14, 17), // "on_bt_pl1_clicked"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 17), // "on_bt_pl3_clicked"
QT_MOC_LITERAL(4, 51, 17), // "on_bt_pl2_clicked"
QT_MOC_LITERAL(5, 69, 17), // "on_bt_pl4_clicked"
QT_MOC_LITERAL(6, 87, 17) // "on_bt_pl5_clicked"

    },
    "select_player\0on_bt_pl1_clicked\0\0"
    "on_bt_pl3_clicked\0on_bt_pl2_clicked\0"
    "on_bt_pl4_clicked\0on_bt_pl5_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_select_player[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x08 /* Private */,
       3,    0,   40,    2, 0x08 /* Private */,
       4,    0,   41,    2, 0x08 /* Private */,
       5,    0,   42,    2, 0x08 /* Private */,
       6,    0,   43,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void select_player::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        select_player *_t = static_cast<select_player *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_bt_pl1_clicked(); break;
        case 1: _t->on_bt_pl3_clicked(); break;
        case 2: _t->on_bt_pl2_clicked(); break;
        case 3: _t->on_bt_pl4_clicked(); break;
        case 4: _t->on_bt_pl5_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject select_player::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_select_player.data,
      qt_meta_data_select_player,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *select_player::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *select_player::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_select_player.stringdata0))
        return static_cast<void*>(const_cast< select_player*>(this));
    return QDialog::qt_metacast(_clname);
}

int select_player::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
