/***************************************************************************
                          filehandlerfactory.h  -  description
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

#ifndef FILEHANDLERFACTORY_H
#define FILEHANDLERFACTORY_H

#include "filehandler.h"
#include "filetype.h"
#include <qdict.h>

/**This class return a File Handler for a file type.
  *@author Rory Vidal
  */

class FileHandlerFactory {
public: 
	FileHandlerFactory();
	~FileHandlerFactory();
  /** returns appropriate file handler for the file type. */
  FileHandler * getFileHandler(FileType *);
private: // Private attributes
  /** Default filehandler. */
  FileHandler * fh;
	/** QDict don't use unique keys!!! */
	QDict<FileHandler> * map_handlers;
	QVector<FileHandler> * all_handlers;
};

#endif
