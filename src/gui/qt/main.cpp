#include <QApplication>
#include <QDialog>
#include "aghphonedialog.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    AghPhoneDialog* dialog = new AghPhoneDialog;
    dialog->show();
    return app.exec();
}

