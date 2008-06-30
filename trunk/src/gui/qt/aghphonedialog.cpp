#include <QtGui>
#include "aghphonedialog.h"

using namespace std;

AghPhoneDialog::AghPhoneDialog(QWidget* parent) : QDialog(parent) {
	setupUi(this);
	connect(callButton, SIGNAL(clicked()), this, SLOT(callSlave()));
}

void AghPhoneDialog::callSlave() {
	cout << "klikles cos tam" << endl;
	QString s = ip_part_1->text();
	QByteArray ba = s.toLatin1();
	const char *c = ba.data();
	printf("%s\n", c);
}
