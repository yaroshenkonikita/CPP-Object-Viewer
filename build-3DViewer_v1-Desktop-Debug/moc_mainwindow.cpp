/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../src/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    const uint offsetsAndSize[40];
    char stringdata0[456];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 10), // "MainWindow"
QT_MOC_LITERAL(11, 24), // "on_actionClose_triggered"
QT_MOC_LITERAL(36, 0), // ""
QT_MOC_LITERAL(37, 27), // "on_button_open_path_clicked"
QT_MOC_LITERAL(65, 22), // "on_button_jpeg_clicked"
QT_MOC_LITERAL(88, 21), // "on_button_bmp_clicked"
QT_MOC_LITERAL(110, 21), // "on_button_gif_clicked"
QT_MOC_LITERAL(132, 9), // "takeFrame"
QT_MOC_LITERAL(142, 25), // "on_rotate_x_returnPressed"
QT_MOC_LITERAL(168, 25), // "on_rotate_y_returnPressed"
QT_MOC_LITERAL(194, 25), // "on_rotate_z_returnPressed"
QT_MOC_LITERAL(220, 28), // "on_translate_x_returnPressed"
QT_MOC_LITERAL(249, 28), // "on_translate_y_returnPressed"
QT_MOC_LITERAL(278, 28), // "on_translate_z_returnPressed"
QT_MOC_LITERAL(307, 30), // "on_scaleLineEdit_returnPressed"
QT_MOC_LITERAL(338, 24), // "on_button_Rotate_pressed"
QT_MOC_LITERAL(363, 27), // "on_button_Translate_pressed"
QT_MOC_LITERAL(391, 24), // "on_scalingButton_pressed"
QT_MOC_LITERAL(416, 25), // "on_button_setting_clicked"
QT_MOC_LITERAL(442, 13) // "load_Settings"

    },
    "MainWindow\0on_actionClose_triggered\0"
    "\0on_button_open_path_clicked\0"
    "on_button_jpeg_clicked\0on_button_bmp_clicked\0"
    "on_button_gif_clicked\0takeFrame\0"
    "on_rotate_x_returnPressed\0"
    "on_rotate_y_returnPressed\0"
    "on_rotate_z_returnPressed\0"
    "on_translate_x_returnPressed\0"
    "on_translate_y_returnPressed\0"
    "on_translate_z_returnPressed\0"
    "on_scaleLineEdit_returnPressed\0"
    "on_button_Rotate_pressed\0"
    "on_button_Translate_pressed\0"
    "on_scalingButton_pressed\0"
    "on_button_setting_clicked\0load_Settings"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  122,    2, 0x08,    1 /* Private */,
       3,    0,  123,    2, 0x08,    2 /* Private */,
       4,    0,  124,    2, 0x08,    3 /* Private */,
       5,    0,  125,    2, 0x08,    4 /* Private */,
       6,    0,  126,    2, 0x08,    5 /* Private */,
       7,    0,  127,    2, 0x08,    6 /* Private */,
       8,    0,  128,    2, 0x08,    7 /* Private */,
       9,    0,  129,    2, 0x08,    8 /* Private */,
      10,    0,  130,    2, 0x08,    9 /* Private */,
      11,    0,  131,    2, 0x08,   10 /* Private */,
      12,    0,  132,    2, 0x08,   11 /* Private */,
      13,    0,  133,    2, 0x08,   12 /* Private */,
      14,    0,  134,    2, 0x08,   13 /* Private */,
      15,    0,  135,    2, 0x08,   14 /* Private */,
      16,    0,  136,    2, 0x08,   15 /* Private */,
      17,    0,  137,    2, 0x08,   16 /* Private */,
      18,    0,  138,    2, 0x08,   17 /* Private */,
      19,    0,  139,    2, 0x08,   18 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_actionClose_triggered(); break;
        case 1: _t->on_button_open_path_clicked(); break;
        case 2: _t->on_button_jpeg_clicked(); break;
        case 3: _t->on_button_bmp_clicked(); break;
        case 4: _t->on_button_gif_clicked(); break;
        case 5: _t->takeFrame(); break;
        case 6: _t->on_rotate_x_returnPressed(); break;
        case 7: _t->on_rotate_y_returnPressed(); break;
        case 8: _t->on_rotate_z_returnPressed(); break;
        case 9: _t->on_translate_x_returnPressed(); break;
        case 10: _t->on_translate_y_returnPressed(); break;
        case 11: _t->on_translate_z_returnPressed(); break;
        case 12: _t->on_scaleLineEdit_returnPressed(); break;
        case 13: _t->on_button_Rotate_pressed(); break;
        case 14: _t->on_button_Translate_pressed(); break;
        case 15: _t->on_scalingButton_pressed(); break;
        case 16: _t->on_button_setting_clicked(); break;
        case 17: _t->load_Settings(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.offsetsAndSize,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_MainWindow_t
, QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 18;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
