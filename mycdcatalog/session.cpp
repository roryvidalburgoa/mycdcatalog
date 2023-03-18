/***************************************************************************
                          session.cpp  -  description
                             -------------------
    begin                : Mon Apr 22 2002
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

#include "session.h"

#include "initform.h"
#include "resultsview.h"
#include "mounter.h"
#include "cdreader.h"
#include "waitthread.h"
#include "showerror.h"
#include "closer.h"

#include <iostream.h>

Session::Session(){
	cdrom=0;
	aRes=0;
	defCFG=0;
	requested=0;
}

Session::~Session(){
	delete cdrom;
	delete requested;
	delete aRes;
}

/** Starts a session */
int Session::run(CFG * aCFG){
	if (aCFG) defCFG = aCFG;

	if (openCDROM() < 0) {
		delete cdrom;
		return -1;
	}

	if (initSQLConnection() < 0) {
		Mounter::tounmount(defCFG->getMntPoint());
		delete cdrom;
		////requested->close();
		delete requested;
		return -1;
	}

	if (requested->addRow(cdrom) < 0) {
		Mounter::tounmount(defCFG->getMntPoint());
		delete cdrom;
		requested->close();
		delete requested;
		return -1;
	}

	if (readMagic() < 0) return -1;

	Traverser * traverser = new Traverser();
	WaitThread * wt = new WaitThread();

	aRes = new Results();
	aRes->aVol = cdrom;

	wt->aRes = aRes;
	traverser->aRes = aRes;
	traverser->cdrom = cdrom;
	traverser->requested = requested;

	ResultsView * rview = ResultsView::getInstance();
	rview->setTraverser(traverser);

	wt->tr = traverser;
	wt->s = this;

	// Creating and displaying the ResultsView
	aRes->display();

	traverser->start();
	wt->start();
	
	InitForm::getInstance()->hide();
	return 0;
}

/** Start connection to a mysql server */
int Session::initSQLConnection(){
	int res;

//	defCFG->print();
	if (!defCFG)
		if (!(defCFG=CFG::getInstance())) return -1;
//	defCFG->print();

	requested = new SQLManager();
	if (defCFG->remote) {
		QString srv;
		short unsigned int port;

		QString server_port = defCFG->getSocket();
		short int pos = server_port.find(':');

		if (pos < 0) {
			srv = server_port;
			port = CFG::defPort;
    } else {
			srv = server_port.left(pos);
			port = server_port.right(server_port.length() - pos -1).toUShort();
		}

		res = requested->connect (defCFG->database.latin1(),srv.latin1(),port,
			defCFG->getUser().latin1(),	defCFG->password.latin1());
	}
	else res = requested->connect (defCFG->database.latin1(),
		defCFG->getSocket().latin1(),
		defCFG->getUser().latin1(),
		defCFG->password.latin1());

	return res;
}

/** open CDROM, takes their info and mounts it. */
int Session::openCDROM(){
//	cerr << "Session::openCDROM()" << endl;

	CDReader * cdr = new CDReader();
	cdrom = cdr->readCDInfo(defCFG->getDevice());

  if (cdrom == 0)
		return -1;
	return Mounter::tomount(defCFG->getMntPoint(),defCFG->getDevice());
}

/** close mysql connection. */
void Session::finishSQLConnection(){
	requested->close();
	delete requested;
}

/** Reading MAGIC file. */
int Session::readMagic(){
 	FileType * ft = new FileType();
	KApplication * kApp = KApplication::kApplication();
	if (ft->readMagic() < 0) {
		kApp->lock();
		ShowError::display("Can't read magic file!: " + QString(MAGIC) + "\nClosing Application");
		kApp->unlock();

		Closer * cl = new Closer();
		cl->not_mounted = false;
		cl->run(defCFG); // closing application .
		return -1;	// kApp->quit() doesn't return immediately
	}
	delete ft;
}

/** Testing with some files. */
int Session::test(CFG *aCFG){
	defCFG = aCFG;
//	defCFG->print();
	initSQLConnection();
	return readMagic();
}

/** returns requested. */
SQLManager * Session::getSQL(){
	return requested;
}
