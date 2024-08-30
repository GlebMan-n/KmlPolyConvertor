/****************************************************************************
** Meta object code from reading C++ file 'KmlClass.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../KmlClass.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'KmlClass.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_KmlClass[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   10,    9,    9, 0x05,
      52,   45,    9,    9, 0x05,
      76,   72,    9,    9, 0x05,
     101,   97,    9,    9, 0x05,
     128,  122,    9,    9, 0x05,
     143,    9,    9,    9, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_KmlClass[] = {
    "KmlClass\0\0vector\0signPosVector(QVector<Pos>)\0"
    "status\0signStatus(QString)\0max\0"
    "signProgressMax(int)\0min\0signProgressMin(int)\0"
    "value\0signValue(int)\0signFinish()\0"
};

void KmlClass::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        KmlClass *_t = static_cast<KmlClass *>(_o);
        switch (_id) {
        case 0: _t->signPosVector((*reinterpret_cast< QVector<Pos>(*)>(_a[1]))); break;
        case 1: _t->signStatus((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->signProgressMax((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->signProgressMin((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->signValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->signFinish(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData KmlClass::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject KmlClass::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_KmlClass,
      qt_meta_data_KmlClass, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &KmlClass::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *KmlClass::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *KmlClass::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_KmlClass))
        return static_cast<void*>(const_cast< KmlClass*>(this));
    return QThread::qt_metacast(_clname);
}

int KmlClass::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void KmlClass::signPosVector(QVector<Pos> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void KmlClass::signStatus(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void KmlClass::signProgressMax(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void KmlClass::signProgressMin(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void KmlClass::signValue(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void KmlClass::signFinish()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}
QT_END_MOC_NAMESPACE
