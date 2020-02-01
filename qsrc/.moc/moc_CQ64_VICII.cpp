/****************************************************************************
** Meta object code from reading C++ file 'CQ64_VICII.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qinclude/CQ64_VICII.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CQ64_VICII.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CQ64_VICII_t {
    QByteArrayData data[6];
    char stringdata0[51];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CQ64_VICII_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CQ64_VICII_t qt_meta_stringdata_CQ64_VICII = {
    {
QT_MOC_LITERAL(0, 0, 10), // "CQ64_VICII"
QT_MOC_LITERAL(1, 11, 14), // "memChangedSlot"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 10), // "updateSlot"
QT_MOC_LITERAL(4, 38, 6), // "margin"
QT_MOC_LITERAL(5, 45, 5) // "scale"

    },
    "CQ64_VICII\0memChangedSlot\0\0updateSlot\0"
    "margin\0scale"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CQ64_VICII[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       2,   26, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x0a /* Public */,
       3,    0,   25,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       4, QMetaType::Int, 0x00095103,
       5, QMetaType::Int, 0x00095103,

       0        // eod
};

void CQ64_VICII::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CQ64_VICII *_t = static_cast<CQ64_VICII *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->memChangedSlot(); break;
        case 1: _t->updateSlot(); break;
        default: ;
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        CQ64_VICII *_t = static_cast<CQ64_VICII *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->margin(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->scale(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        CQ64_VICII *_t = static_cast<CQ64_VICII *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setMargin(*reinterpret_cast< int*>(_v)); break;
        case 1: _t->setScale(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_a);
}

const QMetaObject CQ64_VICII::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CQ64_VICII.data,
      qt_meta_data_CQ64_VICII,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CQ64_VICII::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CQ64_VICII::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CQ64_VICII.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "C64_VICII"))
        return static_cast< C64_VICII*>(this);
    return QWidget::qt_metacast(_clname);
}

int CQ64_VICII::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
