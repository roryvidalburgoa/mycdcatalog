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

#ifndef FILE_H
#define FILE_H

#include "dirfile.h"
#include "filetype.h"

class File: public DirFile {

  public:

  /** table name in mysql db */
  static const char * table_name;

  /** The type. */
  FileType * filetype;

  // Operations
public: // Public methods
  /** Constructor */
   File(const QFileInfo &);

  /** Constructor */
   File();
};

#endif
