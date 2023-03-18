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

#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "dirfile.h"

class Directory: public DirFile {
  // Associations

/*   DirFile son;*/

  // Attributes
  public:
/*    DirFile * DirFiles;*/
    int NbDirFiles;

  /** table name in mysql db */
  static const char * table_name;

  // Operations
public: // Public methods
  /** Constructor */
   Directory(const QFileInfo &);

  /** Constructor */
   Directory();
};

#endif

