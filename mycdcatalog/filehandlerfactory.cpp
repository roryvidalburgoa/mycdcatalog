/***************************************************************************
                          filehandlerfactory.cpp  -  description
                             -------------------
    begin                : Thu May 2 2002
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

#include "filehandlerfactory.h"

#include "mp3handler.h"
#include "pdfhandler.h"

FileHandlerFactory::FileHandlerFactory(){
	map_handlers = new QDict<FileHandler>;
	map_handlers->setAutoDelete(false);

	all_handlers = new QVector<FileHandler> (2);
	all_handlers->insert(0, new MP3Handler());
	all_handlers->insert(1, new PDFHandler());
	all_handlers->setAutoDelete(true);

	// Inserting known keys.
	for(uint i = 0 ; i < all_handlers->count() ; i++) {
		fh = all_handlers->at(i);

//		if (fh->canHandleThis(ft)) {
		QVector<QString> * keys = fh->getKeys();
		QString * aKey;
		for(uint j = 0 ; j < keys->count() ; j++) {
			aKey = keys->at(j);
			map_handlers->insert(*aKey,fh);
//cerr << "i: " << i << " j: " << j << endl;
		}

//				break;
//			} // if handle

	} // for all_handlers
}

FileHandlerFactory::~FileHandlerFactory(){
//	map_handlers->clear();              // A QT Bug ?
//	delete map_handlers;

	all_handlers->remove(0);
	all_handlers->remove(1);
	delete all_handlers;
}

/** returns appropriate file handler for the file type. */
FileHandler * FileHandlerFactory::getFileHandler(FileType * ft){

	// Get file handler by code, description or extension.
	fh = (*map_handlers)[ft->code];
	if (!fh) fh = (*map_handlers)[ft->description];
	if (!fh) fh = (*map_handlers)[ft->extension];

//	// If no file handler found, then try known file handlers.
//	if (!fh) {
//
//
//	} // if !fh

	return fh;
}

