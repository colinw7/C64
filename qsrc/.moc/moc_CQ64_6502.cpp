/****************************************************************************
** Meta object code from reading C++ file 'CQ64_6502.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qinclude/CQ64_6502.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CQ64_6502.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CQ64_6502_t {
    QByteArrayData data[8];
    char stringdata0[125];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CQ64_6502_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CQ64_6502_t qt_meta_stringdata_CQ64_6502 = {
    {
QT_MOC_LITERAL(0, 0, 9), // "CQ64_6502"
QT_MOC_LITERAL(1, 10, 15), // "pcChangedSignal"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 16), // "memChangedSignal"
QT_MOC_LITERAL(4, 44, 17), // "handleBreakSignal"
QT_MOC_LITERAL(5, 62, 19), // "breakpointHitSignal"
QT_MOC_LITERAL(6, 82, 17), // "illegalJumpSignal"
QT_MOC_LITERAL(7, 100, 24) // "breakpointsChangedSignal"

    },
    "CQ64_6502\0pcChangedSignal\0\0memChangedSignal\0"
    "handleBreakSignal\0breakpointHitSignal\0"
    "illegalJumpSignal\0breakpointsChangedSignal"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CQ64_6502[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    0,   45,    2, 0x06 /* Public */,
       4,    0,   46,    2, 0x06 /* Public */,
       5,    0,   47,    2, 0x06 /* Public */,
       6,    0,   48,    2, 0x06 /* Public */,
       7,    0,   49,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CQ64_6502::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CQ64_6502 *_t = static_cast<CQ64_6502 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->pcChangedSignal(); break;
        case 1: _t->memChangedSignal(); break;
        case 2: _t->handleBreakSignal(); break;
        case 3: _t->breakpointHitSignal(); break;
        case 4: _t->illegalJumpSignal(); break;
        case 5: _t->breakpointsChangedSignal(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (CQ64_6502::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CQ64_6502::pcChangedSignal)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CQ64_6502::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CQ64_6502::memChangedSignal)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (CQ64_6502::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CQ64_6502::handleBreakSignal)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (CQ64_6502::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CQ64_6502::breakpointHitSignal)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (CQ64_6502::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CQ64_6502::illegalJumpSignal)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (CQ64_6502::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CQ64_6502::breakpointsChangedSignal)) {
                *result = 5;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject CQ64_6502::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CQ64_6502.data,
      qt_meta_data_CQ64_6502,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CQ64_6502::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CQ64_6502::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CQ64_6502.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "C64_6502"))
        return static_cast< C64_6502*>(this);
    return QObject::qt_metacast(_clname);
}

int CQ64_6502::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void CQ64_6502::pcChangedSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void CQ64_6502::memChangedSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void CQ64_6502::handleBreakSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void CQ64_6502::breakpointHitSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void CQ64_6502::illegalJumpSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void CQ64_6502::breakpointsChangedSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
