/****************************************************************************
** Meta object code from reading C++ file 'aghphonedialog.h'
**
** Created: Tue Sep 16 21:28:03 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "aghphonedialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'aghphonedialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AghPhoneDialog[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      25,   16,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      43,   15,   15,   15, 0x08,
      63,   15,   15,   15, 0x08,
      88,   15,   15,   15, 0x08,
     113,  106,   15,   15, 0x08,
     142,  135,   15,   15, 0x08,
     173,  166,   15,   15, 0x08,
     222,   16,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AghPhoneDialog[] = {
    "AghPhoneDialog\0\0curState\0stateChanged(int)\0"
    "callButtonClicked()\0disengageButtonClicked()\0"
    "contactSelected()\0string\0contactTyped(QString)\0"
    "action\0menuTriggered(QAction*)\0reason\0"
    "trayActivated(QSystemTrayIcon::ActivationReason)\0"
    "stateTransitionSlot(int)\0"
};

const QMetaObject AghPhoneDialog::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_AghPhoneDialog,
      qt_meta_data_AghPhoneDialog, 0 }
};

const QMetaObject *AghPhoneDialog::metaObject() const
{
    return &staticMetaObject;
}

void *AghPhoneDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AghPhoneDialog))
	return static_cast<void*>(const_cast< AghPhoneDialog*>(this));
    if (!strcmp(_clname, "Ui_MainWindow"))
	return static_cast< Ui_MainWindow*>(const_cast< AghPhoneDialog*>(this));
    if (!strcmp(_clname, "IUICallback"))
	return static_cast< IUICallback*>(const_cast< AghPhoneDialog*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int AghPhoneDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: callButtonClicked(); break;
        case 2: disengageButtonClicked(); break;
        case 3: contactSelected(); break;
        case 4: contactTyped((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: menuTriggered((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 6: trayActivated((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 7: stateTransitionSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        }
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void AghPhoneDialog::stateChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
