/****************************************************************************
** Meta object code from reading C++ file 'sensors.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../inc/sensors.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sensors.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PulseSensor_t {
    QByteArrayData data[3];
    char stringdata0[33];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PulseSensor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PulseSensor_t qt_meta_stringdata_PulseSensor = {
    {
QT_MOC_LITERAL(0, 0, 11), // "PulseSensor"
QT_MOC_LITERAL(1, 12, 19), // "update_distribution"
QT_MOC_LITERAL(2, 32, 0) // ""

    },
    "PulseSensor\0update_distribution\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PulseSensor[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void PulseSensor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PulseSensor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->update_distribution(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject PulseSensor::staticMetaObject = { {
    &Device::staticMetaObject,
    qt_meta_stringdata_PulseSensor.data,
    qt_meta_data_PulseSensor,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PulseSensor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PulseSensor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PulseSensor.stringdata0))
        return static_cast<void*>(this);
    return Device::qt_metacast(_clname);
}

int PulseSensor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Device::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_Oximeter_t {
    QByteArrayData data[3];
    char stringdata0[30];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Oximeter_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Oximeter_t qt_meta_stringdata_Oximeter = {
    {
QT_MOC_LITERAL(0, 0, 8), // "Oximeter"
QT_MOC_LITERAL(1, 9, 19), // "update_distribution"
QT_MOC_LITERAL(2, 29, 0) // ""

    },
    "Oximeter\0update_distribution\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Oximeter[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void Oximeter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Oximeter *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->update_distribution(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject Oximeter::staticMetaObject = { {
    &Device::staticMetaObject,
    qt_meta_stringdata_Oximeter.data,
    qt_meta_data_Oximeter,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Oximeter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Oximeter::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Oximeter.stringdata0))
        return static_cast<void*>(this);
    return Device::qt_metacast(_clname);
}

int Oximeter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Device::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_Thermometer_t {
    QByteArrayData data[3];
    char stringdata0[33];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Thermometer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Thermometer_t qt_meta_stringdata_Thermometer = {
    {
QT_MOC_LITERAL(0, 0, 11), // "Thermometer"
QT_MOC_LITERAL(1, 12, 19), // "update_distribution"
QT_MOC_LITERAL(2, 32, 0) // ""

    },
    "Thermometer\0update_distribution\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Thermometer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void Thermometer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Thermometer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->update_distribution(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject Thermometer::staticMetaObject = { {
    &Device::staticMetaObject,
    qt_meta_stringdata_Thermometer.data,
    qt_meta_data_Thermometer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Thermometer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Thermometer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Thermometer.stringdata0))
        return static_cast<void*>(this);
    return Device::qt_metacast(_clname);
}

int Thermometer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Device::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
