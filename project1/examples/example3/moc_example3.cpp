/****************************************************************************
** Meta object code from reading C++ file 'example3.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "example3.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'example3.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MyApp[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,    6,    7,    6, 0x0a,
      40,    6,    7,    6, 0x0a,
      71,    6,    7,    6, 0x0a,
     104,    6,    7,    6, 0x0a,
     135,    6,    7,    6, 0x0a,
     166,    6,    7,    6, 0x0a,
     193,    6,    7,    6, 0x0a,
     222,    6,    7,    6, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MyApp[] = {
    "MyApp\0\0bool\0Menu_Palette_Negate(Image&)\0"
    "Menu_Palette_Grayscale(Image&)\0"
    "Menu_Palette_MyGrayscale(Image&)\0"
    "Menu_Histogram_Display(Image&)\0"
    "Menu_Histogram_Stretch(Image&)\0"
    "Menu_Filter_Smooth(Image&)\0"
    "Menu_Filter_MySmooth(Image&)\0"
    "Menu_Filter_Sharpen(Image&)\0"
};

void MyApp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MyApp *_t = static_cast<MyApp *>(_o);
        switch (_id) {
        case 0: { bool _r = _t->Menu_Palette_Negate((*reinterpret_cast< Image(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 1: { bool _r = _t->Menu_Palette_Grayscale((*reinterpret_cast< Image(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: { bool _r = _t->Menu_Palette_MyGrayscale((*reinterpret_cast< Image(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: { bool _r = _t->Menu_Histogram_Display((*reinterpret_cast< Image(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: { bool _r = _t->Menu_Histogram_Stretch((*reinterpret_cast< Image(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: { bool _r = _t->Menu_Filter_Smooth((*reinterpret_cast< Image(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 6: { bool _r = _t->Menu_Filter_MySmooth((*reinterpret_cast< Image(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 7: { bool _r = _t->Menu_Filter_Sharpen((*reinterpret_cast< Image(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MyApp::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MyApp::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MyApp,
      qt_meta_data_MyApp, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MyApp::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MyApp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MyApp::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyApp))
        return static_cast<void*>(const_cast< MyApp*>(this));
    return QObject::qt_metacast(_clname);
}

int MyApp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
