/****************************************************************************
** Meta object code from reading C++ file 'main_window.hpp'
**
** Created: Mon May 27 21:20:07 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "main_window.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'main_window.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GUI__MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      23,   17,   16,   16, 0x0a,
      57,   17,   16,   16, 0x0a,
      91,   17,   16,   16, 0x0a,
     124,   16,   16,   16, 0x0a,
     136,   16,   16,   16, 0x0a,
     151,   16,   16,   16, 0x0a,
     168,   16,   16,   16, 0x0a,
     187,   16,   16,   16, 0x0a,
     206,   16,   16,   16, 0x0a,
     232,  226,   16,   16, 0x0a,
     263,   16,   16,   16, 0x0a,
     287,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GUI__MainWindow[] = {
    "GUI::MainWindow\0\0check\0"
    "on_pushButton_pause_clicked(bool)\0"
    "on_pushButton_start_clicked(bool)\0"
    "on_pushButton_stop_clicked(bool)\0"
    "updateOEE()\0updateUpTime()\0OrderCountdown()\0"
    "updateSystemTime()\0updateSystemDate()\0"
    "updateTotalOrders()\0state\0"
    "updateSystemState(std::string)\0"
    "updateorderCountdowns()\0updateOrderNeeds()\0"
};

void GUI::MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->on_pushButton_pause_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->on_pushButton_start_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->on_pushButton_stop_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->updateOEE(); break;
        case 4: _t->updateUpTime(); break;
        case 5: _t->OrderCountdown(); break;
        case 6: _t->updateSystemTime(); break;
        case 7: _t->updateSystemDate(); break;
        case 8: _t->updateTotalOrders(); break;
        case 9: _t->updateSystemState((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 10: _t->updateorderCountdowns(); break;
        case 11: _t->updateOrderNeeds(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GUI::MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GUI::MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_GUI__MainWindow,
      qt_meta_data_GUI__MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GUI::MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GUI::MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GUI::MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GUI__MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int GUI::MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
