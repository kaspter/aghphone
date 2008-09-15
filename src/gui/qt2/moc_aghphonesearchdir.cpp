/****************************************************************************
** Meta object code from reading C++ file 'aghphonesearchdir.h'
**
** Created: Fri Sep 12 18:34:00 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "aghphonesearchdir.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'aghphonesearchdir.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AghPhoneSearchDirDialog[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      25,   24,   24,   24, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AghPhoneSearchDirDialog[] = {
    "AghPhoneSearchDirDialog\0\0searchButtonClicked()\0"
};

const QMetaObject AghPhoneSearchDirDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_AghPhoneSearchDirDialog,
      qt_meta_data_AghPhoneSearchDirDialog, 0 }
};

const QMetaObject *AghPhoneSearchDirDialog::metaObject() const
{
    return &staticMetaObject;
}

void *AghPhoneSearchDirDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AghPhoneSearchDirDialog))
	return static_cast<void*>(const_cast< AghPhoneSearchDirDialog*>(this));
    if (!strcmp(_clname, "Ui_SearchDialog"))
	return static_cast< Ui_SearchDialog*>(const_cast< AghPhoneSearchDirDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int AghPhoneSearchDirDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: searchButtonClicked(); break;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
