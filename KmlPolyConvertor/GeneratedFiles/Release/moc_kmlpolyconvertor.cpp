/****************************************************************************
** Meta object code from reading C++ file 'kmlpolyconvertor.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../kmlpolyconvertor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'kmlpolyconvertor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_KmlPolyConvertor[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x08,
      38,   31,   17,   17, 0x08,
      62,   17,   17,   17, 0x08,
      79,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_KmlPolyConvertor[] = {
    "KmlPolyConvertor\0\0_slotBegin()\0status\0"
    "_slotSetStatus(QString)\0_slotRunThread()\0"
    "_delKmlClass()\0"
};

void KmlPolyConvertor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        KmlPolyConvertor *_t = static_cast<KmlPolyConvertor *>(_o);
        switch (_id) {
        case 0: _t->_slotBegin(); break;
        case 1: _t->_slotSetStatus((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->_slotRunThread(); break;
        case 3: _t->_delKmlClass(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData KmlPolyConvertor::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject KmlPolyConvertor::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_KmlPolyConvertor,
      qt_meta_data_KmlPolyConvertor, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &KmlPolyConvertor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *KmlPolyConvertor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *KmlPolyConvertor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_KmlPolyConvertor))
        return static_cast<void*>(const_cast< KmlPolyConvertor*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int KmlPolyConvertor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
