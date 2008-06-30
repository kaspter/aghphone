#ifndef AGHPHONEDIALOG_H
#define AGHPHONEDIALOG_H

#include <QDialog>
#include "ui_aghphonedialog.h"
#include <iostream>

class AghPhoneDialog : public QDialog, public Ui::AghPhoneUI {
	Q_OBJECT

	public:
	AghPhoneDialog(QWidget* parent = 0);

	private slots:
	void callSlave();
};

#endif

