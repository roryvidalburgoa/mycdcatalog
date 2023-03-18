/***************************************************************************
                          pdfhandler.cpp  -  description
                             -------------------
    begin                : Fri May 3 2002
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

#include "pdfhandler.h"

PDFHandler::PDFHandler(){
 	keys = new QVector<QString> (4);
	keys->insert(0, new QString("%PDF-"));
	keys->insert(1, new QString("PDF"));
	keys->insert(2, new QString("PDF\\"));
	keys->insert(3, new QString("PDF document"));
}

PDFHandler::~PDFHandler(){
}

/** true if can handle a file type. */
bool PDFHandler::canHandleThis(FileType * ft){
	if (
		(ft->code == "%PDF-") ||
		(ft->code == "PDF" ) ||
		(ft->code == "PDF\\") ||
		(ft->description == "PDF document")
			) return true;
	else return false;
}

/** Handle a PDF file. */
void PDFHandler::handleIt(File * aFile, MysqlConnection * aConn){
	cout << "A PDF Document" << endl;
}

/** Returns keys for a mp3 file handler. */
QVector<QString> * PDFHandler::getKeys(){
	return keys;
}
