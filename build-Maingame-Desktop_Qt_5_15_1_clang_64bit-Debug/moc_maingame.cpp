/****************************************************************************
** Meta object code from reading C++ file 'maingame.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Maingame/maingame.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'maingame.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Maingame_t {
    QByteArrayData data[27];
    char stringdata0[290];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Maingame_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Maingame_t qt_meta_stringdata_Maingame = {
    {
QT_MOC_LITERAL(0, 0, 8), // "Maingame"
QT_MOC_LITERAL(1, 9, 17), // "hideStartWarLabel"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 19), // "hideActSuccessLabel"
QT_MOC_LITERAL(4, 48, 18), // "hideActFailedLabel"
QT_MOC_LITERAL(5, 67, 15), // "hideOtherChupai"
QT_MOC_LITERAL(6, 83, 8), // "on_timer"
QT_MOC_LITERAL(7, 92, 9), // "on_choose"
QT_MOC_LITERAL(8, 102, 3), // "res"
QT_MOC_LITERAL(9, 106, 11), // "on_continue"
QT_MOC_LITERAL(10, 118, 8), // "playerID"
QT_MOC_LITERAL(11, 127, 4), // "head"
QT_MOC_LITERAL(12, 132, 20), // "receive_BroadCastNum"
QT_MOC_LITERAL(13, 153, 3), // "num"
QT_MOC_LITERAL(14, 157, 11), // "vector<int>"
QT_MOC_LITERAL(15, 169, 3), // "ids"
QT_MOC_LITERAL(16, 173, 5), // "heads"
QT_MOC_LITERAL(17, 179, 16), // "receive_Progress"
QT_MOC_LITERAL(18, 196, 5), // "state"
QT_MOC_LITERAL(19, 202, 8), // "winnerID"
QT_MOC_LITERAL(20, 211, 14), // "receive_Origin"
QT_MOC_LITERAL(21, 226, 10), // "landlordID"
QT_MOC_LITERAL(22, 237, 5), // "cards"
QT_MOC_LITERAL(23, 243, 11), // "receive_Who"
QT_MOC_LITERAL(24, 255, 3), // "who"
QT_MOC_LITERAL(25, 259, 13), // "receive_Cards"
QT_MOC_LITERAL(26, 273, 16) // "receive_ActionFd"

    },
    "Maingame\0hideStartWarLabel\0\0"
    "hideActSuccessLabel\0hideActFailedLabel\0"
    "hideOtherChupai\0on_timer\0on_choose\0"
    "res\0on_continue\0playerID\0head\0"
    "receive_BroadCastNum\0num\0vector<int>\0"
    "ids\0heads\0receive_Progress\0state\0"
    "winnerID\0receive_Origin\0landlordID\0"
    "cards\0receive_Who\0who\0receive_Cards\0"
    "receive_ActionFd"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Maingame[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    0,   80,    2, 0x08 /* Private */,
       4,    0,   81,    2, 0x08 /* Private */,
       5,    0,   82,    2, 0x08 /* Private */,
       6,    0,   83,    2, 0x08 /* Private */,
       7,    1,   84,    2, 0x0a /* Public */,
       9,    3,   87,    2, 0x0a /* Public */,
      12,    3,   94,    2, 0x0a /* Public */,
      17,    2,  101,    2, 0x0a /* Public */,
      20,    3,  106,    2, 0x0a /* Public */,
      23,    1,  113,    2, 0x0a /* Public */,
      25,    3,  116,    2, 0x0a /* Public */,
      26,    1,  123,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::Bool, QMetaType::Int, QMetaType::Int,    8,   10,   11,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 14, 0x80000000 | 14,   13,   15,   16,
    QMetaType::Void, QMetaType::Bool, QMetaType::Int,   18,   19,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, 0x80000000 | 14,   21,   13,   22,
    QMetaType::Void, QMetaType::Int,   24,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, 0x80000000 | 14,   10,   13,   22,
    QMetaType::Void, QMetaType::Bool,    8,

       0        // eod
};

void Maingame::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Maingame *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->hideStartWarLabel(); break;
        case 1: _t->hideActSuccessLabel(); break;
        case 2: _t->hideActFailedLabel(); break;
        case 3: _t->hideOtherChupai(); break;
        case 4: _t->on_timer(); break;
        case 5: _t->on_choose((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->on_continue((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 7: _t->receive_BroadCastNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const vector<int>(*)>(_a[2])),(*reinterpret_cast< const vector<int>(*)>(_a[3]))); break;
        case 8: _t->receive_Progress((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: _t->receive_Origin((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const vector<int>(*)>(_a[3]))); break;
        case 10: _t->receive_Who((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->receive_Cards((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const vector<int>(*)>(_a[3]))); break;
        case 12: _t->receive_ActionFd((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Maingame::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_Maingame.data,
    qt_meta_data_Maingame,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Maingame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Maingame::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Maingame.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Maingame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
