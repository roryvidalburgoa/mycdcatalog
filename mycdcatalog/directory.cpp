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

#include "directory.h"

/** table name */
const char * Directory::table_name = "Directory";

/** Constructor */
Directory::Directory() : DirFile(){
	NbDirFiles = 0;
}

/** Constructor */
Directory::Directory(const QFileInfo & fi) : DirFile(fi){
	NbDirFiles = 0;
}
