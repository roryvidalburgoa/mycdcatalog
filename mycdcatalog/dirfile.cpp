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

#include "dirfile.h"

/** Constructor */
DirFile::DirFile(QString qs) : QFileInfo(qs){
	id = parent_id = 0;
}

/** Default Constructor */
DirFile::DirFile() : QFileInfo() {
	id = parent_id = 0;
}

/** Copy Constructor */
DirFile::DirFile(const QFileInfo & fi) : QFileInfo(fi){
	id = parent_id = 0;
}
