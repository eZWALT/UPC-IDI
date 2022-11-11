/****************************************************************************
** Meta object code from reading C++ file 'MyQButton.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "MyQButton.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MyQButton.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyQButton_t {
    QByteArrayData data[14];
    char stringdata0[86];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyQButton_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyQButton_t qt_meta_stringdata_MyQButton = {
    {
QT_MOC_LITERAL(0, 0, 9), // "MyQButton"
QT_MOC_LITERAL(1, 10, 9), // "SendColor"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 4), // "Trio"
QT_MOC_LITERAL(4, 26, 2), // "c1"
QT_MOC_LITERAL(5, 29, 2), // "c2"
QT_MOC_LITERAL(6, 32, 2), // "c3"
QT_MOC_LITERAL(7, 35, 2), // "xd"
QT_MOC_LITERAL(8, 38, 8), // "QString*"
QT_MOC_LITERAL(9, 47, 5), // "paint"
QT_MOC_LITERAL(10, 53, 9), // "justpaint"
QT_MOC_LITERAL(11, 63, 5), // "color"
QT_MOC_LITERAL(12, 69, 10), // "resetColor"
QT_MOC_LITERAL(13, 80, 5) // "start"

    },
    "MyQButton\0SendColor\0\0Trio\0c1\0c2\0c3\0"
    "xd\0QString*\0paint\0justpaint\0color\0"
    "resetColor\0start"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyQButton[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       3,    0,   67,    2, 0x06 /* Public */,
       4,    1,   68,    2, 0x06 /* Public */,
       5,    1,   71,    2, 0x06 /* Public */,
       6,    1,   74,    2, 0x06 /* Public */,
       7,    1,   77,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   80,    2, 0x0a /* Public */,
      10,    1,   81,    2, 0x0a /* Public */,
      12,    0,   84,    2, 0x0a /* Public */,
      13,    0,   85,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 8,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MyQButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MyQButton *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->SendColor((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->Trio(); break;
        case 2: _t->c1((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->c2((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->c3((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->xd((*reinterpret_cast< QString*(*)>(_a[1]))); break;
        case 6: _t->paint(); break;
        case 7: _t->justpaint((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->resetColor(); break;
        case 9: _t->start(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MyQButton::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyQButton::SendColor)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MyQButton::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyQButton::Trio)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MyQButton::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyQButton::c1)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MyQButton::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyQButton::c2)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MyQButton::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyQButton::c3)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (MyQButton::*)(QString * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyQButton::xd)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MyQButton::staticMetaObject = { {
    QMetaObject::SuperData::link<QPushButton::staticMetaObject>(),
    qt_meta_stringdata_MyQButton.data,
    qt_meta_data_MyQButton,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MyQButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyQButton::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyQButton.stringdata0))
        return static_cast<void*>(this);
    return QPushButton::qt_metacast(_clname);
}

int MyQButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void MyQButton::SendColor(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MyQButton::Trio()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MyQButton::c1(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MyQButton::c2(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MyQButton::c3(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MyQButton::xd(QString * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
