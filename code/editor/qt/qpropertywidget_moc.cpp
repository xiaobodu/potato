/****************************************************************************
** Meta object code from reading C++ file 'qpropertywidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qpropertywidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qpropertywidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_c4g__qt__QPropertyWidget_t {
    QByteArrayData data[7];
    char stringdata[81];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_c4g__qt__QPropertyWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_c4g__qt__QPropertyWidget_t qt_meta_stringdata_c4g__qt__QPropertyWidget = {
    {
QT_MOC_LITERAL(0, 0, 24),
QT_MOC_LITERAL(1, 25, 12),
QT_MOC_LITERAL(2, 38, 0),
QT_MOC_LITERAL(3, 39, 16),
QT_MOC_LITERAL(4, 56, 5),
QT_MOC_LITERAL(5, 62, 6),
QT_MOC_LITERAL(6, 69, 10)
    },
    "c4g::qt::QPropertyWidget\0UpdateWidget\0"
    "\0QTreeWidgetItem*\0pItem\0iColum\0"
    "LostWidget\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_c4g__qt__QPropertyWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x0a,
       6,    0,   29,    2, 0x0a,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    5,
    QMetaType::Void,

       0        // eod
};

void c4g::qt::QPropertyWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QPropertyWidget *_t = static_cast<QPropertyWidget *>(_o);
        switch (_id) {
        case 0: _t->UpdateWidget((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->LostWidget(); break;
        default: ;
        }
    }
}

const QMetaObject c4g::qt::QPropertyWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_c4g__qt__QPropertyWidget.data,
      qt_meta_data_c4g__qt__QPropertyWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *c4g::qt::QPropertyWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *c4g::qt::QPropertyWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_c4g__qt__QPropertyWidget.stringdata))
        return static_cast<void*>(const_cast< QPropertyWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int c4g::qt::QPropertyWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
    return _id;
}
QT_END_MOC_NAMESPACE
