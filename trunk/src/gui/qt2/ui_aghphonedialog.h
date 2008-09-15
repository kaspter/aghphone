/********************************************************************************
** Form generated from reading ui file 'aghphonedialog.ui'
**
** Created: Sat Sep 13 13:49:16 2008
**      by: Qt User Interface Compiler version 4.4.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_AGHPHONEDIALOG_H
#define UI_AGHPHONEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionZaloguj;
    QAction *actionLog_out;
    QAction *actionEdit_profile;
    QAction *actionOptions;
    QAction *actionClose;
    QAction *actionAbout;
    QAction *actionHelp;
    QAction *actionLicense;
    QAction *actionSearch_in_directory;
    QAction *actionAbout_QT;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_9;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *hostAddressEdit;
    QLabel *label_2;
    QLineEdit *portEdit;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_8;
    QListWidget *contactsList;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer;
    QPushButton *callButton;
    QPushButton *disengageButton;
    QSpacerItem *horizontalSpacer_2;
    QMenuBar *menubar;
    QMenu *menuDasf;
    QMenu *menuTools;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
    MainWindow->resize(360, 538);
    actionZaloguj = new QAction(MainWindow);
    actionZaloguj->setObjectName(QString::fromUtf8("actionZaloguj"));
    actionLog_out = new QAction(MainWindow);
    actionLog_out->setObjectName(QString::fromUtf8("actionLog_out"));
    actionEdit_profile = new QAction(MainWindow);
    actionEdit_profile->setObjectName(QString::fromUtf8("actionEdit_profile"));
    actionOptions = new QAction(MainWindow);
    actionOptions->setObjectName(QString::fromUtf8("actionOptions"));
    actionClose = new QAction(MainWindow);
    actionClose->setObjectName(QString::fromUtf8("actionClose"));
    actionAbout = new QAction(MainWindow);
    actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
    actionHelp = new QAction(MainWindow);
    actionHelp->setObjectName(QString::fromUtf8("actionHelp"));
    actionLicense = new QAction(MainWindow);
    actionLicense->setObjectName(QString::fromUtf8("actionLicense"));
    actionSearch_in_directory = new QAction(MainWindow);
    actionSearch_in_directory->setObjectName(QString::fromUtf8("actionSearch_in_directory"));
    actionAbout_QT = new QAction(MainWindow);
    actionAbout_QT->setObjectName(QString::fromUtf8("actionAbout_QT"));
    centralwidget = new QWidget(MainWindow);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    centralwidget->setGeometry(QRect(0, 28, 360, 485));
    verticalLayout_9 = new QVBoxLayout(centralwidget);
    verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
    groupBox_2 = new QGroupBox(centralwidget);
    groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
    groupBox_2->setSizePolicy(sizePolicy);
    gridLayout = new QGridLayout(groupBox_2);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    label = new QLabel(groupBox_2);
    label->setObjectName(QString::fromUtf8("label"));

    gridLayout->addWidget(label, 0, 0, 1, 1);

    hostAddressEdit = new QLineEdit(groupBox_2);
    hostAddressEdit->setObjectName(QString::fromUtf8("hostAddressEdit"));

    gridLayout->addWidget(hostAddressEdit, 0, 1, 1, 1);

    label_2 = new QLabel(groupBox_2);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    gridLayout->addWidget(label_2, 1, 0, 1, 1);

    portEdit = new QLineEdit(groupBox_2);
    portEdit->setObjectName(QString::fromUtf8("portEdit"));

    gridLayout->addWidget(portEdit, 1, 1, 1, 1);

    label->raise();
    hostAddressEdit->raise();
    label_2->raise();
    portEdit->raise();

    verticalLayout_9->addWidget(groupBox_2);

    groupBox = new QGroupBox(centralwidget);
    groupBox->setObjectName(QString::fromUtf8("groupBox"));
    QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
    groupBox->setSizePolicy(sizePolicy1);
    verticalLayout_8 = new QVBoxLayout(groupBox);
    verticalLayout_8->setSpacing(0);
    verticalLayout_8->setMargin(0);
    verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
    contactsList = new QListWidget(groupBox);
    contactsList->setObjectName(QString::fromUtf8("contactsList"));

    verticalLayout_8->addWidget(contactsList);

    horizontalLayout_7 = new QHBoxLayout();
    horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_7->addItem(horizontalSpacer);

    callButton = new QPushButton(groupBox);
    callButton->setObjectName(QString::fromUtf8("callButton"));
    callButton->setEnabled(false);
    callButton->setIconSize(QSize(48, 48));

    horizontalLayout_7->addWidget(callButton);

    disengageButton = new QPushButton(groupBox);
    disengageButton->setObjectName(QString::fromUtf8("disengageButton"));
    disengageButton->setEnabled(false);
    disengageButton->setIconSize(QSize(48, 48));

    horizontalLayout_7->addWidget(disengageButton);

    horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_7->addItem(horizontalSpacer_2);


    verticalLayout_8->addLayout(horizontalLayout_7);


    verticalLayout_9->addWidget(groupBox);

    MainWindow->setCentralWidget(centralwidget);
    menubar = new QMenuBar(MainWindow);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 360, 28));
    menuDasf = new QMenu(menubar);
    menuDasf->setObjectName(QString::fromUtf8("menuDasf"));
    menuTools = new QMenu(menubar);
    menuTools->setObjectName(QString::fromUtf8("menuTools"));
    menuHelp = new QMenu(menubar);
    menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
    MainWindow->setMenuBar(menubar);
    statusbar = new QStatusBar(MainWindow);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    statusbar->setGeometry(QRect(0, 513, 360, 25));
    MainWindow->setStatusBar(statusbar);

    menubar->addAction(menuDasf->menuAction());
    menubar->addAction(menuTools->menuAction());
    menubar->addAction(menuHelp->menuAction());
    menuDasf->addAction(actionZaloguj);
    menuDasf->addAction(actionLog_out);
    menuDasf->addSeparator();
    menuDasf->addAction(actionClose);
    menuTools->addAction(actionOptions);
    menuTools->addAction(actionSearch_in_directory);
    menuHelp->addAction(actionHelp);
    menuHelp->addAction(actionLicense);
    menuHelp->addAction(actionAbout);
    menuHelp->addAction(actionAbout_QT);

    retranslateUi(MainWindow);

    QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
    MainWindow->setWindowTitle(QApplication::translate("MainWindow", "AGHPhone", 0, QApplication::UnicodeUTF8));
    actionZaloguj->setText(QApplication::translate("MainWindow", "Log in", 0, QApplication::UnicodeUTF8));
    actionLog_out->setText(QApplication::translate("MainWindow", "Log out", 0, QApplication::UnicodeUTF8));
    actionEdit_profile->setText(QApplication::translate("MainWindow", "Edit profile", 0, QApplication::UnicodeUTF8));
    actionOptions->setText(QApplication::translate("MainWindow", "Preferences", 0, QApplication::UnicodeUTF8));
    actionClose->setText(QApplication::translate("MainWindow", "Close", 0, QApplication::UnicodeUTF8));
    actionAbout->setText(QApplication::translate("MainWindow", "About", 0, QApplication::UnicodeUTF8));
    actionHelp->setText(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
    actionLicense->setText(QApplication::translate("MainWindow", "License", 0, QApplication::UnicodeUTF8));
    actionSearch_in_directory->setText(QApplication::translate("MainWindow", "Search in directory", 0, QApplication::UnicodeUTF8));
    actionAbout_QT->setText(QApplication::translate("MainWindow", "About Qt", 0, QApplication::UnicodeUTF8));
    groupBox_2->setTitle(QApplication::translate("MainWindow", "Direct call:", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("MainWindow", "Host address:", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("MainWindow", "Port:", 0, QApplication::UnicodeUTF8));
    groupBox->setTitle(QApplication::translate("MainWindow", "Recent Contacts:", 0, QApplication::UnicodeUTF8));

#ifndef QT_NO_TOOLTIP
    callButton->setToolTip(QApplication::translate("MainWindow", "Call", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP

    callButton->setText(QApplication::translate("MainWindow", "Call", 0, QApplication::UnicodeUTF8));

#ifndef QT_NO_TOOLTIP
    disengageButton->setToolTip(QApplication::translate("MainWindow", "Disengage", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP

    disengageButton->setText(QApplication::translate("MainWindow", "Disengage", 0, QApplication::UnicodeUTF8));
    menuDasf->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
    menuTools->setTitle(QApplication::translate("MainWindow", "Tools", 0, QApplication::UnicodeUTF8));
    menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AGHPHONEDIALOG_H
