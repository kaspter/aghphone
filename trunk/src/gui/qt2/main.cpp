#include <QApplication>
#include <QDialog>
#include <vector>
// #include "aghphonepref.h"
#include "aghphonedialog.h"
#include "codecfactory.h"

using namespace std;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    AghPhoneDialog* dialog = new AghPhoneDialog();
    dialog->show();
    return app.exec();
}

