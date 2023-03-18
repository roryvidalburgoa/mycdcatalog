/***************************************************************************
                          filetype.cpp  -  description
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

#include "filetype.h"

#include <iostream.h>

#include <qregexp.h>
#include <qfileinfo.h>

extern "C" {
#include "./filetype/file.h"
}

bool FileType::magic_read = false;
QString FileType::types_table = "Types";

FileType::FileType(){
 code=description=extension="";
}

FileType::~FileType(){
}

char acode[32];
char adesc[32];

/** find the filetype of aFile. */
int FileType::findType(QString aFile){
	int ret = process(aFile.latin1(),aFile.length());

	code = QString(acode);
	description = QString(adesc);

/** changes all ocurrences of " by \".
Return changed string. */
	code.replace(QRegExp("\""), "\\\"");
	description.replace(QRegExp("\""), "\\\"");

	acode[0] = 0;
	adesc[0] = 0;
	return ret;
}

/** read magic file. */
int FileType::readMagic(){
	if (!FileType::magic_read) {
//cerr << "Reading magic" << endl;
		FileType::magic_read = true;

		QString magicfile;
		if (QFileInfo(MAGIC).exists())
			magicfile = MAGIC;
		else {
			if (QFileInfo("~/.magic").exists())
					magicfile = "~/.magic";
			else {
				cerr << "No valid magic file found\nTryed: " << MAGIC << "," << "~/.magic" << endl;
				return -1;
			}
		}

		int action = 0;
		int ret = apprentice(magicfile.latin1(), action);
		if (action)
			return ret;
		else return action;
	}
	else return 0;
}
