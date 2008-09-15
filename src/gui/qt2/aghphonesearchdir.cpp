#include <QtGui>
#include <stdio.h>
#include "aghphonesearchdir.h"

using namespace std;
using namespace agh;

AghPhoneSearchDirDialog::AghPhoneSearchDirDialog(QWidget* parent) : QDialog(parent) {
	setupUi(this);
	connect(searchButton, SIGNAL(clicked()), this, SLOT(searchButtonClicked()));
	selectedTerminal = 0;
}

void AghPhoneSearchDirDialog::setConfiguration(TerminalConfiguration *configuration) {
	this->configuration = configuration;
}

void AghPhoneSearchDirDialog::searchButtonClicked() {
	resultList->clear();
	QString criteria = aliasEdit->text();
	TerminalAddress* terminalAddress;
	
	try {
		Terminals terminals = this->directory->findTerminals(criteria.toLocal8Bit().data());
		
		// add founded address to the list
		for (int i = 0; i < terminals.size(); i++) {
			terminalAddress = new TerminalAddress;
			*terminalAddress = terminals[i];
			putTerminalIntoList(terminalAddress, terminalAddress->name.c_str());
		}
		
	} catch(VoipException) {
		QMessageBox::critical( this, this->windowTitle(), 
				"Unable to retrieve terminal address!");
		return;
	}
}

void AghPhoneSearchDirDialog::putTerminalIntoList(TerminalAddress *terminal, QString alias) {
	if (terminal == NULL) {
		return;
	}
	// check whether exists
	QList<QListWidgetItem *> tmpList = resultList->findItems(alias, Qt::MatchExactly);
	if ( tmpList.count() > 0)
		return;
	
	QListWidgetItem *tmpItem = new QListWidgetItem(alias);
	tmpItem->setData(Qt::UserRole, QVariant(QMetaType::VoidStar, &terminal) );
	
	resultList->addItem ( tmpItem );
}

TerminalAddress* AghPhoneSearchDirDialog::getSelectedTerminal() {
	return selectedTerminal;
}

void AghPhoneSearchDirDialog::exec() {
	QString errorMessage = this->configuration->validateDirectory().c_str();
	
	if (errorMessage.count() > 0) {
		QMessageBox::critical( this, this->windowTitle(), 
							   errorMessage);
		
	} else {
		// search for directory
		try {
			Ice::CommunicatorPtr ic = Ice::initialize();
			stringstream a;
			a << *(configuration->directoryName) 
					<< ":default -h " << *(configuration->directoryAddress) 
					<< " -p " << *(configuration->directoryPort);
			Ice::ObjectPrx base = ic->stringToProxy ( a.str() );
			directory = DirectoryPrx::checkedCast ( base );
			
			if ( !directory ) {
				QMessageBox::critical( this, this->windowTitle(), 
									   "Connection to directory failed, please check your configuration!");
			} else {
				QDialog::exec();
				int currentRow = resultList->currentRow();
				QListWidgetItem* item = resultList->item(currentRow);
				if ( resultList->isItemSelected(item) ) {
					// get Terminal
					selectedTerminal = reinterpret_cast<TerminalAddress*>(qvariant_cast<void*>(item->data(Qt::UserRole)));
					cout << "XXX1: " << selectedTerminal->name.c_str() << endl;
				} else {
					cout << "BBB\n";
					selectedTerminal = 0;
				}
			}
			
			ic->destroy();
			
		} catch (...) {
			QMessageBox::critical( this, this->windowTitle(), 
								   "Connection to directory failed, please check your configuration!");
			return;
		}
	}
}
