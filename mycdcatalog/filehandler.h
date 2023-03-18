/***************************************************************************
                          filehandler.h  -  description
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

#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <qvector.h>

#include "file.h"
#include "filetype.h"

#define MYSQL_NO_SHORT_NAMES
#include <sqlplus.hh>

/**This is an abstract class, represents a general File Handler.
  *@author Rory Vidal
  */

class FileHandler {
public: 
	FileHandler();
	virtual ~FileHandler();

  /** demands if this class can handle a file type,
	* file type represented by a FileType object. */
//  virtual bool canHandleThis(FileType *) = 0;

  /** Handles a file, it uses a MySQLConnection objet to fill related tables. */
  virtual void handleIt(File *, MysqlConnection *) = 0;

  /** Returns a list of keys for this filehandler. */
  virtual QVector<QString> * getKeys() = 0;

protected: // Protected attributes
  /** keys */
  QVector<QString> * keys;
  /** handled file. */
  File * curFile;
  /** connection to a mysql server to use. */
  MysqlConnection * curConn;
};

#endif
