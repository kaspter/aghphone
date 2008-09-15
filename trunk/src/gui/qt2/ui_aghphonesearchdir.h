/********************************************************************************
** Form generated from reading ui file 'aghphonesearchdir.ui'
**
** Created: Fri Sep 12 18:29:52 2008
**      by: Qt User Interface Compiler version 4.4.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_AGHPHONESEARCHDIR_H
#define UI_AGHPHONESEARCHDIR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SearchDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *aliasEdit;
    QPushButton *searchButton;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QListWidget *resultList;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SearchDialog)
    {
    if (SearchDialog->objectName().isEmpty())
        SearchDialog->setObjectName(QString::fromUtf8("SearchDialog"));
    SearchDialog->resize(516, 428);
    verticalLayout_2 = new QVBoxLayout(SearchDialog);
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    groupBox_2 = new QGroupBox(SearchDialog);
    groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
    QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
    groupBox_2->setSizePolicy(sizePolicy);
    horizontalLayout_2 = new QHBoxLayout(groupBox_2);
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    label = new QLabel(groupBox_2);
    label->setObjectName(QString::fromUtf8("label"));

    horizontalLayout->addWidget(label);

    aliasEdit = new QLineEdit(groupBox_2);
    aliasEdit->setObjectName(QString::fromUtf8("aliasEdit"));

    horizontalLayout->addWidget(aliasEdit);


    horizontalLayout_2->addLayout(horizontalLayout);

    searchButton = new QPushButton(groupBox_2);
    searchButton->setObjectName(QString::fromUtf8("searchButton"));

    horizontalLayout_2->addWidget(searchButton);


    verticalLayout_2->addWidget(groupBox_2);

    groupBox = new QGroupBox(SearchDialog);
    groupBox->setObjectName(QString::fromUtf8("groupBox"));
    sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
    groupBox->setSizePolicy(sizePolicy);
    verticalLayout = new QVBoxLayout(groupBox);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    resultList = new QListWidget(groupBox);
    resultList->setObjectName(QString::fromUtf8("resultList"));
    QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(resultList->sizePolicy().hasHeightForWidth());
    resultList->setSizePolicy(sizePolicy1);

    verticalLayout->addWidget(resultList);


    verticalLayout_2->addWidget(groupBox);

    buttonBox = new QDialogButtonBox(SearchDialog);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

    verticalLayout_2->addWidget(buttonBox);


    retranslateUi(SearchDialog);
    QObject::connect(buttonBox, SIGNAL(accepted()), SearchDialog, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), SearchDialog, SLOT(reject()));

    QMetaObject::connectSlotsByName(SearchDialog);
    } // setupUi

    void retranslateUi(QDialog *SearchDialog)
    {
    SearchDialog->setWindowTitle(QApplication::translate("SearchDialog", "Dialog", 0, QApplication::UnicodeUTF8));
    groupBox_2->setTitle(QApplication::translate("SearchDialog", "Search criteria", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("SearchDialog", "Terminal alias:", 0, QApplication::UnicodeUTF8));
    searchButton->setText(QApplication::translate("SearchDialog", "Search", 0, QApplication::UnicodeUTF8));
    groupBox->setTitle(QApplication::translate("SearchDialog", "Search result", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(SearchDialog);
    } // retranslateUi

};

namespace Ui {
    class SearchDialog: public Ui_SearchDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AGHPHONESEARCHDIR_H
