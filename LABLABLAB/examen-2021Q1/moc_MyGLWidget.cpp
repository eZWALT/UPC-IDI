/****************************************************************************
** Meta object code from reading C++ file 'MyGLWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "MyGLWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MyGLWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyGLWidget_t {
    QByteArrayData data[7];
    char stringdata0[77];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyGLWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyGLWidget_t qt_meta_stringdata_MyGLWidget = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MyGLWidget"
QT_MOC_LITERAL(1, 11, 9), // "reiniciar"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 9), // "ortogonal"
QT_MOC_LITERAL(4, 32, 11), // "perspectiva"
QT_MOC_LITERAL(5, 44, 12), // "cambiar_orto"
QT_MOC_LITERAL(6, 57, 19) // "cambiar_perspectiva"

    },
    "MyGLWidget\0reiniciar\0\0ortogonal\0"
    "perspectiva\0cambiar_orto\0cambiar_perspectiva"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyGLWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    0,   40,    2, 0x06 /* Public */,
       4,    0,   41,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   42,    2, 0x0a /* Public */,
       6,    0,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MyGLWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MyGLWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->reiniciar(); break;
        case 1: _t->ortogonal(); break;
        case 2: _t->perspectiva(); break;
        case 3: _t->cambiar_orto(); break;
        case 4: _t->cambiar_perspectiva(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MyGLWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyGLWidget::reiniciar)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MyGLWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyGLWidget::ortogonal)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MyGLWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyGLWidget::perspectiva)) {
                *result = 2;
                return;
            }
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject MyGLWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<ExamGLWidget::staticMetaObject>(),
    qt_meta_stringdata_MyGLWidget.data,
    qt_meta_data_MyGLWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MyGLWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyGLWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyGLWidget.stringdata0))
        return static_cast<void*>(this);
    return ExamGLWidget::qt_metacast(_clname);
}

int MyGLWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ExamGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void MyGLWidget::reiniciar()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MyGLWidget::ortogonal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MyGLWidget::perspectiva()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
