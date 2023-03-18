/***************************************************************************
                            -  description
                             -------------------
    begin                : Fri Apr 12 16:37:10 CEST 2002
    copyright            : (C) 2002 by Rory Vidal
    email                : roryvidal@yahoo.fr
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <klocale.h>

#include <klineedit.h>
#include <knuminput.h>
#include <qbuttongroup.h>
#include <qcheckbox.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qradiobutton.h>
#include <qlayout.h>
#include <qvariant.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

#include <iostream.h>

#include "initform.h"
#include "closer.h"
#include "session.h"
#include "showerror.h"

/** definition of a STATIC member */
InitForm * InitForm::instance = 0;

InitForm::InitForm()
{
	remote = true;
}

InitForm::~InitForm()
{
	instance = 0;
}

void InitForm::openOn ( CFG * aCFG ){
	cerr << "InitForm::openOn" << endl;
	defCFG = aCFG;
	if (!defCFG) return;

//	defCFG->print();

  LE_Device->setText( defCFG->getDevice() );
	LE_MntPoint->setText( defCFG->getMntPoint() );
	LE_Username->setText( defCFG->getUser() );
	LE_Password->setText( defCFG->password );
	LE_Database->setText( defCFG->database );

	if (defCFG->remote) {
		QString server_port = defCFG->getSocket();
		int pos = server_port.find(':');
		if (pos < 0) {
			LE_Server->setText(server_port);
			LE_Port->setValue(CFG::defPort);
			cerr << "':' not found in " << server_port;
    } else {
			LE_Server->setText(server_port.left(pos));
			LE_Port->setValue((server_port.right(server_port.length() - pos -1)).toInt());
		}
  } else {
		LE_Socket->setText(defCFG->getSocket());
		
		Remote->setChecked( FALSE );
		Local->setChecked( TRUE );

		LE_Socket->setEnabled(TRUE);
		LE_Server->setEnabled(FALSE);
		LE_Port->setEnabled(FALSE);
		remote = false;
	}

	show();
	return;
}

/** For implement singleton pattern */
InitForm * InitForm::getInstance(){
	if (!instance) {
//		instance = 1;
		instance = new InitForm();
//		return new InitForm();
	} //else return 0;
	return instance;
}

void InitForm::local_slot()
{
	if (remote) {
		LE_Socket->setEnabled(TRUE);
		LE_Server->setEnabled(FALSE);
		LE_Port->setEnabled(FALSE);
		remote = false;
	}
}

void InitForm::read_slot()
{
	if (no_config()) {
		ShowError::display(
		 "Configuration incomplete!\nPlease fill all entries."
		);
		return;
	}

	update_config_if_changed();

	Session * readsession = new Session();
//	if (readsession->run(defCFG) < 0) delete readsession;
	readsession->run(defCFG);
}

void InitForm::remote_slot()
{
	if (!remote) {
//	qWarning( "InitForm::remote_slot(): Not implemented yet!" );
		LE_Socket->setEnabled(FALSE);
		LE_Server->setEnabled(TRUE);
		LE_Port->setEnabled(TRUE);
		remote = true;
	}
}

void InitForm::closer_slot() {
	Closer * cl = new Closer();
	cl->not_mounted = true;
	cl->run(defCFG);
}

/** Check if given config is complete. */
bool InitForm::no_config() {
	if ((LE_Device->text() == "") || (LE_Device->text() == QString::null)
		||(LE_MntPoint->text() == "") || (LE_MntPoint->text() == QString::null)
		||(LE_Username->text() == "") || (LE_Username->text() == QString::null)
		||(LE_Password->text() == "") || (LE_Password->text() == QString::null)
		||(LE_Database->text() == "") || (LE_Database->text() == QString::null)) return true;

	if (remote) {
		if ((LE_Server->text() == "") || (LE_Server->text() == QString::null)) return true;
//			||(LE_Port->text() == "") || (LE_Port->text() == QString::null)) return true;
	} else
			if ((LE_Socket->text() == "") || (LE_Socket->text() == QString::null)) return true;

	return false;
}

/** if config has changed from widget then put "cfg-> changed = true" */
void InitForm::update_config_if_changed() {
	bool total = false;
	bool tmp = false;

	defCFG->password = LE_Password->text();

	total = total || (tmp = (LE_Device->text() != defCFG->getDevice()));
	if (tmp) defCFG->putDevice(LE_Device->text());

	total = total || (tmp = (LE_MntPoint->text() != defCFG->getMntPoint()));
	if (tmp) defCFG->putMntPoint(LE_MntPoint->text());

	total = total || (tmp = (LE_Username->text() != defCFG->getUser()));
	if (tmp) defCFG->putUser(LE_Username->text());

	total = total || (tmp = (LE_Database->text() != defCFG->database));
	if (tmp) defCFG->database = LE_Database->text();

	QString qs;

	if (remote && (LE_Port->value() !=  0))
		qs = LE_Server->text() + ":" + QString::number(LE_Port->value());
	else { if (remote) qs = LE_Server->text();
				 else qs = LE_Socket->text(); }

	total = total || (tmp = (qs != defCFG->getSocket()));
	if (tmp) defCFG->putSocket(qs);

	total = total || (tmp = (remote != defCFG->remote));
	if (tmp) defCFG->remote = remote;

	total = total || (tmp = (Eject->isChecked() != defCFG->eject));
	if (tmp) defCFG->eject = Eject->isChecked();

	if (total) defCFG->changed = true;

//	cout << "\nupdate_cfg_if_changed: " << endl;
//	defCFG->print();
}
