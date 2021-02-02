/****************************************************************************
** Meta object code from reading C++ file 'clientsocket.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Maingame/clientsocket.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'clientsocket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ClientSocket_t {
    QByteArrayData data[22];
    char stringdata0[215];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ClientSocket_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ClientSocket_t qt_meta_stringdata_ClientSocket = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ClientSocket"
QT_MOC_LITERAL(1, 13, 18), // "report_LoginResult"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 3), // "res"
QT_MOC_LITERAL(4, 37, 8), // "playerID"
QT_MOC_LITERAL(5, 46, 4), // "head"
QT_MOC_LITERAL(6, 51, 19), // "report_BroadcastNum"
QT_MOC_LITERAL(7, 71, 3), // "num"
QT_MOC_LITERAL(8, 75, 11), // "vector<int>"
QT_MOC_LITERAL(9, 87, 3), // "ids"
QT_MOC_LITERAL(10, 91, 5), // "heads"
QT_MOC_LITERAL(11, 97, 15), // "report_Progress"
QT_MOC_LITERAL(12, 113, 5), // "state"
QT_MOC_LITERAL(13, 119, 8), // "winnerID"
QT_MOC_LITERAL(14, 128, 13), // "report_Origin"
QT_MOC_LITERAL(15, 142, 10), // "landlordID"
QT_MOC_LITERAL(16, 153, 5), // "cards"
QT_MOC_LITERAL(17, 159, 10), // "report_Who"
QT_MOC_LITERAL(18, 170, 3), // "who"
QT_MOC_LITERAL(19, 174, 12), // "report_Cards"
QT_MOC_LITERAL(20, 187, 15), // "report_ActionFd"
QT_MOC_LITERAL(21, 203, 11) // "onReadyRead"

    },
    "ClientSocket\0report_LoginResult\0\0res\0"
    "playerID\0head\0report_BroadcastNum\0num\0"
    "vector<int>\0ids\0heads\0report_Progress\0"
    "state\0winnerID\0report_Origin\0landlordID\0"
    "cards\0report_Who\0who\0report_Cards\0"
    "report_ActionFd\0onReadyRead"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ClientSocket[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   54,    2, 0x06 /* Public */,
       6,    3,   61,    2, 0x06 /* Public */,
      11,    2,   68,    2, 0x06 /* Public */,
      14,    3,   73,    2, 0x06 /* Public */,
      17,    1,   80,    2, 0x06 /* Public */,
      19,    3,   83,    2, 0x06 /* Public */,
      20,    1,   90,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      21,    0,   93,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool, QMetaType::Int, QMetaType::Int,    3,    4,    5,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 8, 0x80000000 | 8,    7,    9,   10,
    QMetaType::Void, QMetaType::Bool, QMetaType::Int,   12,   13,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, 0x80000000 | 8,   15,    7,   16,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, 0x80000000 | 8,    4,    7,   16,
    QMetaType::Void, QMetaType::Bool,    3,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void ClientSocket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ClientSocket *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->report_LoginResult((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->report_BroadcastNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const vector<int>(*)>(_a[2])),(*reinterpret_cast< const vector<int>(*)>(_a[3]))); break;
        case 2: _t->report_Progress((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->report_Origin((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const vector<int>(*)>(_a[3]))); break;
        case 4: _t->report_Who((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->report_Cards((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const vector<int>(*)>(_a[3]))); break;
        case 6: _t->report_ActionFd((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->onReadyRead(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ClientSocket::*)(bool , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientSocket::report_LoginResult)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ClientSocket::*)(int , const vector<int> & , const vector<int> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientSocket::report_BroadcastNum)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ClientSocket::*)(bool , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientSocket::report_Progress)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ClientSocket::*)(int , int , const vector<int> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientSocket::report_Origin)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ClientSocket::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientSocket::report_Who)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ClientSocket::*)(int , int , const vector<int> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientSocket::report_Cards)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (ClientSocket::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientSocket::report_ActionFd)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ClientSocket::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ClientSocket.data,
    qt_meta_data_ClientSocket,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ClientSocket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ClientSocket::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ClientSocket.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ClientSocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void ClientSocket::report_LoginResult(bool _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ClientSocket::report_BroadcastNum(int _t1, const vector<int> & _t2, const vector<int> & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ClientSocket::report_Progress(bool _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ClientSocket::report_Origin(int _t1, int _t2, const vector<int> & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ClientSocket::report_Who(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ClientSocket::report_Cards(int _t1, int _t2, const vector<int> & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ClientSocket::report_ActionFd(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
