/***************************************************************************
                          showerror.cpp  -  description
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

#include "showerror.h"

#include <string.h>		// strerror
#include <errno.h>		// error number

#include <kmessagebox.h>
#include <kapp.h>

#include <iostream>

//extern "C" {
//#include <unistd.h>
//}

bool ShowError::gui = true;

ShowError::ShowError(){
}

ShowError::~ShowError(){
}

/** display error messages. */
void ShowError::display(QString errmsg){
	QString msg;
	KApplication * kApp = KApplication::kApplication();
	QWidget * main = kApp->mainWidget();

	if (errno) msg = errmsg + ": " + QString(strerror(errno));
	else msg = errmsg;

	if (gui) {
		kApp->lock();
		KMessageBox::sorry(main, msg, "Error");
		kApp->unlock();
	}
	else
		cerr << msg << endl;
}
