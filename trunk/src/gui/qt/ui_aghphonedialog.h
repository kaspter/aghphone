/********************************************************************************
** Form generated from reading ui file 'aghphonedialog.ui'
**
** Created: Mon Jun 30 01:59:38 2008
**      by: Qt User Interface Compiler version 4.3.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_AGHPHONEDIALOG_H
#define UI_AGHPHONEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_AghPhoneUI
{
public:
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QLabel *label;
    QLineEdit *ip_part_1;
    QLineEdit *ip_part_2;
    QLineEdit *ip_part_3;
    QLineEdit *ip_part_4;
    QHBoxLayout *hboxLayout1;
    QLabel *label_2;
    QLineEdit *local_port;
    QHBoxLayout *hboxLayout2;
    QLabel *label_3;
    QLineEdit *remote_port;
    QHBoxLayout *hboxLayout3;
    QPushButton *callButton;
    QPushButton *endCallButton;

    void setupUi(QWidget *AghPhoneUI)
    {
    if (AghPhoneUI->objectName().isEmpty())
        AghPhoneUI->setObjectName(QString::fromUtf8("AghPhoneUI"));
    AghPhoneUI->resize(569, 279);
    vboxLayout = new QVBoxLayout(AghPhoneUI);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    hboxLayout = new QHBoxLayout();
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    label = new QLabel(AghPhoneUI);
    label->setObjectName(QString::fromUtf8("label"));

    hboxLayout->addWidget(label);

    ip_part_1 = new QLineEdit(AghPhoneUI);
    ip_part_1->setObjectName(QString::fromUtf8("ip_part_1"));

    hboxLayout->addWidget(ip_part_1);

    ip_part_2 = new QLineEdit(AghPhoneUI);
    ip_part_2->setObjectName(QString::fromUtf8("ip_part_2"));

    hboxLayout->addWidget(ip_part_2);

    ip_part_3 = new QLineEdit(AghPhoneUI);
    ip_part_3->setObjectName(QString::fromUtf8("ip_part_3"));

    hboxLayout->addWidget(ip_part_3);

    ip_part_4 = new QLineEdit(AghPhoneUI);
    ip_part_4->setObjectName(QString::fromUtf8("ip_part_4"));

    hboxLayout->addWidget(ip_part_4);


    vboxLayout->addLayout(hboxLayout);

    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    label_2 = new QLabel(AghPhoneUI);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    hboxLayout1->addWidget(label_2);

    local_port = new QLineEdit(AghPhoneUI);
    local_port->setObjectName(QString::fromUtf8("local_port"));

    hboxLayout1->addWidget(local_port);


    vboxLayout->addLayout(hboxLayout1);

    hboxLayout2 = new QHBoxLayout();
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    label_3 = new QLabel(AghPhoneUI);
    label_3->setObjectName(QString::fromUtf8("label_3"));

    hboxLayout2->addWidget(label_3);

    remote_port = new QLineEdit(AghPhoneUI);
    remote_port->setObjectName(QString::fromUtf8("remote_port"));

    hboxLayout2->addWidget(remote_port);


    vboxLayout->addLayout(hboxLayout2);

    hboxLayout3 = new QHBoxLayout();
    hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
    callButton = new QPushButton(AghPhoneUI);
    callButton->setObjectName(QString::fromUtf8("callButton"));

    hboxLayout3->addWidget(callButton);

    endCallButton = new QPushButton(AghPhoneUI);
    endCallButton->setObjectName(QString::fromUtf8("endCallButton"));

    hboxLayout3->addWidget(endCallButton);


    vboxLayout->addLayout(hboxLayout3);


    retranslateUi(AghPhoneUI);

    QMetaObject::connectSlotsByName(AghPhoneUI);
    } // setupUi

    void retranslateUi(QWidget *AghPhoneUI)
    {
    AghPhoneUI->setWindowTitle(QApplication::translate("AghPhoneUI", "AghPhone", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("AghPhoneUI", "IP", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("AghPhoneUI", "Local port", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("AghPhoneUI", "Remote port", 0, QApplication::UnicodeUTF8));
    callButton->setText(QApplication::translate("AghPhoneUI", "Call", 0, QApplication::UnicodeUTF8));
    endCallButton->setText(QApplication::translate("AghPhoneUI", "End Call", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(AghPhoneUI);
    } // retranslateUi

};

namespace Ui {
    class AghPhoneUI: public Ui_AghPhoneUI {};
} // namespace Ui

#endif // UI_AGHPHONEDIALOG_H
