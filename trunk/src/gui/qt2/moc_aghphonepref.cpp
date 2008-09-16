/****************************************************************************
** Meta object code from reading C++ file 'aghphonepref.h'
**
** Created: Tue Sep 16 20:49:05 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "aghphonepref.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'aghphonepref.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AghPhonePrefDialog[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x08,
      46,   19,   19,   19, 0x08,
      74,   19,   19,   19, 0x08,
     100,   19,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AghPhonePrefDialog[] = {
    "AghPhonePrefDialog\0\0incomingUpButtonClicked()\0"
    "incomingDownButtonClicked()\0"
    "outgoingUpButtonClicked()\0"
    "outgoingDownButtonClicked()\0"
};

const QMetaObject AghPhonePrefDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_AghPhonePrefDialog,
      qt_meta_data_AghPhonePrefDialog, 0 }
};

const QMetaObject *AghPhonePrefDialog::metaObject() const
{
    return &staticMetaObject;
}

void *AghPhonePrefDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AghPhonePrefDialog))
	return static_cast<void*>(const_cast< AghPhonePrefDialog*>(this));
    if (!strcmp(_clname, "Ui_Dialog"))
	return static_cast< Ui_Dialog*>(const_cast< AghPhonePrefDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int AghPhonePrefDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: incomingUpButtonClicked(); break;
        case 1: incomingDownButtonClicked(); break;
        case 2: outgoingUpButtonClicked(); break;
        case 3: outgoingDownButtonClicked(); break;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
