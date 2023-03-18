/***************************************************************************
                          mp3handler.cpp  -  description
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

#include "mp3handler.h"
#include "showerror.h"

/** Constructor */
MP3Handler::MP3Handler(){
	keys = new QVector<QString> (3);
	keys->insert(0, new QString("MP"));
	keys->insert(1, new QString("ID3"));
	keys->insert(2, new QString("mp3"));
}

MP3Handler::~MP3Handler(){
	keys->remove(2);
	keys->remove(1);
	keys->remove(0);
	delete keys;
}

/** true if can handle a file type. */
//bool MP3Handler::canHandleThis(FileType * ft){
//	if (
//			(ft->code == "ID3") ||
//			(ft->description == "MP") ||
//			(ft->extension == "mp3")
//			) return true;
//	else return false;
//}

/** Handle a MP3 file. */
void MP3Handler::handleIt(File * aFile,MysqlConnection * aConn){
  MP3_ID3 id3 = MP3_ID3();
	curFile = aFile;
	curConn = aConn;

	int start;
	if ((start = id3.getMP3Info(
				aFile->filePath()
			)
		 ) < 0) {
		cerr << "No file or unreadable file: " << aFile->filePath() << endl;
		return;
	}

	if (id3.nbfr > 0) { // if ID3 tag exists
//		cout << endl;// << "Start pos: " << start << endl;
//		id3.print();
		id3.addRow(curConn,curFile->id);
	}

  if (start > 3102) start = 0;  // ID3 is normally < 3k
	MP3_Header mpeg = MP3_Header((unsigned int) start, id3.has_id3_v1);

	if (mpeg.readHeader(aFile) < 0) {
		cerr << "No mpeg frame, no mp3 file or unreadable file: " << aFile->filePath() << endl;
		return;
	}

//	mpeg.print();  cout << endl;
	mpeg.addRow(curConn,curFile->id);
}

/** Returns keys for a pdf file handler. */
QVector<QString> * MP3Handler::getKeys(){
	return keys;
}
