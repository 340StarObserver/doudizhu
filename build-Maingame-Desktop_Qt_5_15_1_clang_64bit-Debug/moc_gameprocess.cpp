/****************************************************************************
** Meta object code from reading C++ file 'gameprocess.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Maingame/gameprocess.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gameprocess.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GameProcess_t {
    QByteArrayData data[17];
    char stringdata0[217];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GameProcess_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GameProcess_t qt_meta_stringdata_GameProcess = {
    {
QT_MOC_LITERAL(0, 0, 11), // "GameProcess"
QT_MOC_LITERAL(1, 12, 15), // "TellGameProcess"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 23), // "GameProcess::GameStatus"
QT_MOC_LITERAL(4, 53, 16), // "TellPlayerStatus"
QT_MOC_LITERAL(5, 70, 7), // "Player*"
QT_MOC_LITERAL(6, 78, 6), // "player"
QT_MOC_LITERAL(7, 85, 20), // "Player::PlayerStatus"
QT_MOC_LITERAL(8, 106, 6), // "status"
QT_MOC_LITERAL(9, 113, 18), // "TellPlayerPlayHand"
QT_MOC_LITERAL(10, 132, 11), // "QList<card>"
QT_MOC_LITERAL(11, 144, 5), // "cards"
QT_MOC_LITERAL(12, 150, 18), // "TellPlayerCallLord"
QT_MOC_LITERAL(13, 169, 3), // "bet"
QT_MOC_LITERAL(14, 173, 13), // "TellHitPlayer"
QT_MOC_LITERAL(15, 187, 14), // "PlayerCallLord"
QT_MOC_LITERAL(16, 202, 14) // "PlayerPlayHand"

    },
    "GameProcess\0TellGameProcess\0\0"
    "GameProcess::GameStatus\0TellPlayerStatus\0"
    "Player*\0player\0Player::PlayerStatus\0"
    "status\0TellPlayerPlayHand\0QList<card>\0"
    "cards\0TellPlayerCallLord\0bet\0TellHitPlayer\0"
    "PlayerCallLord\0PlayerPlayHand"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GameProcess[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       4,    2,   52,    2, 0x06 /* Public */,
       9,    2,   57,    2, 0x06 /* Public */,
      12,    2,   62,    2, 0x06 /* Public */,
      14,    2,   67,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      15,    2,   72,    2, 0x0a /* Public */,
      16,    2,   77,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 7,    6,    8,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 10,    6,   11,
    QMetaType::Void, 0x80000000 | 5, QMetaType::Int,    6,   13,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 10,    6,   11,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5, QMetaType::Int,    6,   13,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 10,    6,   11,

       0        // eod
};

void GameProcess::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GameProcess *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->TellGameProcess((*reinterpret_cast< GameProcess::GameStatus(*)>(_a[1]))); break;
        case 1: _t->TellPlayerStatus((*reinterpret_cast< Player*(*)>(_a[1])),(*reinterpret_cast< Player::PlayerStatus(*)>(_a[2]))); break;
        case 2: _t->TellPlayerPlayHand((*reinterpret_cast< Player*(*)>(_a[1])),(*reinterpret_cast< QList<card>(*)>(_a[2]))); break;
        case 3: _t->TellPlayerCallLord((*reinterpret_cast< Player*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->TellHitPlayer((*reinterpret_cast< Player*(*)>(_a[1])),(*reinterpret_cast< QList<card>(*)>(_a[2]))); break;
        case 5: _t->PlayerCallLord((*reinterpret_cast< Player*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->PlayerPlayHand((*reinterpret_cast< Player*(*)>(_a[1])),(*reinterpret_cast< QList<card>(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Player* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Player* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Player* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Player* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Player* >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Player* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GameProcess::*)(GameProcess::GameStatus );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameProcess::TellGameProcess)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GameProcess::*)(Player * , Player::PlayerStatus );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameProcess::TellPlayerStatus)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (GameProcess::*)(Player * , QList<card> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameProcess::TellPlayerPlayHand)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (GameProcess::*)(Player * , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameProcess::TellPlayerCallLord)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (GameProcess::*)(Player * , QList<card> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameProcess::TellHitPlayer)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GameProcess::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_GameProcess.data,
    qt_meta_data_GameProcess,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GameProcess::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GameProcess::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GameProcess.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int GameProcess::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void GameProcess::TellGameProcess(GameProcess::GameStatus _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GameProcess::TellPlayerStatus(Player * _t1, Player::PlayerStatus _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GameProcess::TellPlayerPlayHand(Player * _t1, QList<card> _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void GameProcess::TellPlayerCallLord(Player * _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void GameProcess::TellHitPlayer(Player * _t1, QList<card> _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
