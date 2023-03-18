/***************************************************************************
                          filetype.h  -  description
                             -------------------
    begin                : Thu Apr 25 2002
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

#ifndef FILETYPE_H
#define FILETYPE_H

#include <qstring.h>

/**
  *Uses file functions in order to find the type of a file
  *@author Rory Vidal
  */

#ifndef MAGIC
# define MAGIC "/usr/share/magic"
#endif

class FileType {
public: 
	FileType();
	~FileType();
public: // Public attributes
  /** code of filetype */
  QString code;
  /** description of filetype. */
  QString description;
  /** Name of types table */
  static QString types_table;
  /** extension : .ext */
  QString extension;
  /** find the filetype of aFile. */
  int findType(QString);
  /** read magic file. */
  int readMagic();
private: // Private attributes
  /** true if apprentice was used over MAGIC file.
default = false. */
  static bool magic_read;
};

#endif
