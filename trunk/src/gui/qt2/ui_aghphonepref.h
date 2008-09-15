/********************************************************************************
** Form generated from reading ui file 'aghphonepref.ui'
**
** Created: Fri Sep 12 18:29:52 2008
**      by: Qt User Interface Compiler version 4.4.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_AGHPHONEPREF_H
#define UI_AGHPHONEPREF_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *directoryAddressEdit;
    QLabel *label_2;
    QLineEdit *directoryPortEdit;
    QLabel *label_5;
    QLineEdit *directoryAliasEdit;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *label_3;
    QLineEdit *localPortEdit;
    QLabel *label_4;
    QLineEdit *prefferedRTPPortEdit;
    QSpacerItem *verticalSpacer;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout;
    QListWidget *incomingCodecsList;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_2;
    QPushButton *incomingUpButton;
    QPushButton *incomingDownButton;
    QSpacerItem *verticalSpacer_3;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_2;
    QListWidget *outgoingCodecsList;
    QVBoxLayout *verticalLayout_4;
    QSpacerItem *verticalSpacer_21;
    QPushButton *outgoingUpButton;
    QPushButton *outgoingDownButton;
    QSpacerItem *verticalSpacer_31;
    QWidget *tab_3;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Dialog)
    {
    if (Dialog->objectName().isEmpty())
        Dialog->setObjectName(QString::fromUtf8("Dialog"));
    Dialog->resize(538, 538);
    verticalLayout_2 = new QVBoxLayout(Dialog);
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    tabWidget = new QTabWidget(Dialog);
    tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
    tab = new QWidget();
    tab->setObjectName(QString::fromUtf8("tab"));
    tab->setGeometry(QRect(0, 0, 518, 454));
    verticalLayout = new QVBoxLayout(tab);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    groupBox = new QGroupBox(tab);
    groupBox->setObjectName(QString::fromUtf8("groupBox"));
    gridLayout = new QGridLayout(groupBox);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    label = new QLabel(groupBox);
    label->setObjectName(QString::fromUtf8("label"));

    gridLayout->addWidget(label, 0, 0, 1, 1);

    directoryAddressEdit = new QLineEdit(groupBox);
    directoryAddressEdit->setObjectName(QString::fromUtf8("directoryAddressEdit"));

    gridLayout->addWidget(directoryAddressEdit, 0, 1, 1, 1);

    label_2 = new QLabel(groupBox);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    gridLayout->addWidget(label_2, 1, 0, 1, 1);

    directoryPortEdit = new QLineEdit(groupBox);
    directoryPortEdit->setObjectName(QString::fromUtf8("directoryPortEdit"));

    gridLayout->addWidget(directoryPortEdit, 1, 1, 1, 1);

    label_5 = new QLabel(groupBox);
    label_5->setObjectName(QString::fromUtf8("label_5"));

    gridLayout->addWidget(label_5, 2, 0, 1, 1);

    directoryAliasEdit = new QLineEdit(groupBox);
    directoryAliasEdit->setObjectName(QString::fromUtf8("directoryAliasEdit"));

    gridLayout->addWidget(directoryAliasEdit, 2, 1, 1, 1);


    verticalLayout->addWidget(groupBox);

    groupBox_2 = new QGroupBox(tab);
    groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
    gridLayout_2 = new QGridLayout(groupBox_2);
    gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
    label_3 = new QLabel(groupBox_2);
    label_3->setObjectName(QString::fromUtf8("label_3"));

    gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

    localPortEdit = new QLineEdit(groupBox_2);
    localPortEdit->setObjectName(QString::fromUtf8("localPortEdit"));

    gridLayout_2->addWidget(localPortEdit, 0, 1, 1, 1);

    label_4 = new QLabel(groupBox_2);
    label_4->setObjectName(QString::fromUtf8("label_4"));

    gridLayout_2->addWidget(label_4, 1, 0, 1, 1);

    prefferedRTPPortEdit = new QLineEdit(groupBox_2);
    prefferedRTPPortEdit->setObjectName(QString::fromUtf8("prefferedRTPPortEdit"));

    gridLayout_2->addWidget(prefferedRTPPortEdit, 1, 1, 1, 1);


    verticalLayout->addWidget(groupBox_2);

    verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout->addItem(verticalSpacer);

    tabWidget->addTab(tab, QString());
    tab_2 = new QWidget();
    tab_2->setObjectName(QString::fromUtf8("tab_2"));
    tab_2->setGeometry(QRect(0, 0, 518, 454));
    verticalLayout_5 = new QVBoxLayout(tab_2);
    verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
    groupBox_3 = new QGroupBox(tab_2);
    groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
    horizontalLayout = new QHBoxLayout(groupBox_3);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    incomingCodecsList = new QListWidget(groupBox_3);
    incomingCodecsList->setObjectName(QString::fromUtf8("incomingCodecsList"));

    horizontalLayout->addWidget(incomingCodecsList);

    verticalLayout_3 = new QVBoxLayout();
    verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
    verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout_3->addItem(verticalSpacer_2);

    incomingUpButton = new QPushButton(groupBox_3);
    incomingUpButton->setObjectName(QString::fromUtf8("incomingUpButton"));

    verticalLayout_3->addWidget(incomingUpButton);

    incomingDownButton = new QPushButton(groupBox_3);
    incomingDownButton->setObjectName(QString::fromUtf8("incomingDownButton"));

    verticalLayout_3->addWidget(incomingDownButton);

    verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout_3->addItem(verticalSpacer_3);


    horizontalLayout->addLayout(verticalLayout_3);


    verticalLayout_5->addWidget(groupBox_3);

    groupBox_4 = new QGroupBox(tab_2);
    groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
    horizontalLayout_2 = new QHBoxLayout(groupBox_4);
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    outgoingCodecsList = new QListWidget(groupBox_4);
    outgoingCodecsList->setObjectName(QString::fromUtf8("outgoingCodecsList"));

    horizontalLayout_2->addWidget(outgoingCodecsList);

    verticalLayout_4 = new QVBoxLayout();
    verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
    verticalSpacer_21 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout_4->addItem(verticalSpacer_21);

    outgoingUpButton = new QPushButton(groupBox_4);
    outgoingUpButton->setObjectName(QString::fromUtf8("outgoingUpButton"));

    verticalLayout_4->addWidget(outgoingUpButton);

    outgoingDownButton = new QPushButton(groupBox_4);
    outgoingDownButton->setObjectName(QString::fromUtf8("outgoingDownButton"));

    verticalLayout_4->addWidget(outgoingDownButton);

    verticalSpacer_31 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout_4->addItem(verticalSpacer_31);


    horizontalLayout_2->addLayout(verticalLayout_4);


    verticalLayout_5->addWidget(groupBox_4);

    tabWidget->addTab(tab_2, QString());
    tab_3 = new QWidget();
    tab_3->setObjectName(QString::fromUtf8("tab_3"));
    tab_3->setGeometry(QRect(0, 0, 518, 454));
    tabWidget->addTab(tab_3, QString());

    verticalLayout_2->addWidget(tabWidget);

    buttonBox = new QDialogButtonBox(Dialog);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

    verticalLayout_2->addWidget(buttonBox);


    retranslateUi(Dialog);
    QObject::connect(buttonBox, SIGNAL(accepted()), Dialog, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), Dialog, SLOT(reject()));

    tabWidget->setCurrentIndex(0);


    QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
    Dialog->setWindowTitle(QApplication::translate("Dialog", "Preferences", 0, QApplication::UnicodeUTF8));
    groupBox->setTitle(QApplication::translate("Dialog", "Directory:", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("Dialog", "Address:", 0, QApplication::UnicodeUTF8));
    directoryAddressEdit->setInputMask(QString());
    directoryAddressEdit->setText(QApplication::translate("Dialog", "127.0.0.1", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("Dialog", "Port:", 0, QApplication::UnicodeUTF8));
    directoryPortEdit->setInputMask(QString());
    directoryPortEdit->setText(QApplication::translate("Dialog", "12345", 0, QApplication::UnicodeUTF8));
    label_5->setText(QApplication::translate("Dialog", "User alias:", 0, QApplication::UnicodeUTF8));
    groupBox_2->setTitle(QApplication::translate("Dialog", "Connection:", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("Dialog", "Local port:", 0, QApplication::UnicodeUTF8));
    localPortEdit->setInputMask(QString());
    localPortEdit->setText(QString());
    label_4->setText(QApplication::translate("Dialog", "Preffered RTP port:", 0, QApplication::UnicodeUTF8));
    prefferedRTPPortEdit->setInputMask(QString());
    prefferedRTPPortEdit->setText(QString());
    tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Dialog", "General", 0, QApplication::UnicodeUTF8));
    groupBox_3->setTitle(QApplication::translate("Dialog", "Preffered incoming audio codecs", 0, QApplication::UnicodeUTF8));
    incomingUpButton->setText(QApplication::translate("Dialog", "Up", 0, QApplication::UnicodeUTF8));
    incomingDownButton->setText(QApplication::translate("Dialog", "Down", 0, QApplication::UnicodeUTF8));
    groupBox_4->setTitle(QApplication::translate("Dialog", "Preffered outgoing audio codecs", 0, QApplication::UnicodeUTF8));
    outgoingUpButton->setText(QApplication::translate("Dialog", "Up", 0, QApplication::UnicodeUTF8));
    outgoingDownButton->setText(QApplication::translate("Dialog", "Down", 0, QApplication::UnicodeUTF8));
    tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Dialog", "Audio", 0, QApplication::UnicodeUTF8));
    tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("Dialog", "Conferences", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(Dialog);
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AGHPHONEPREF_H
