/***************************************************************************
                          mp3lyrics.cpp  -  description
                             -------------------
    begin                : Mon May 6 2002
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

#include "mp3lyrics.h"

QString mp3lyrics_table = "MP3USLT";

MP3Lyrics::MP3Lyrics(){
	description=lang=lyrics="";
}

MP3Lyrics::~MP3Lyrics(){
}

int MP3Lyrics::addRow(MysqlConnection * curConn, int fileid) {
  try {
		MysqlQuery query = curConn->query();
		ostrstream strbuf;
    strbuf.clear();

		strbuf << "INSERT INTO " << mp3lyrics_table << " VALUES ("
				<< fileid << ","
				<< norm (lyrics) << ","
				<< norm (description) << ","
				<< norm (lang) << ");" << ends;

//cout << strbuf.str() << endl;
				query.exec(strbuf.str());
	} catch (MysqlBadQuery er) { // handle any connection or
                          // query errors that may come up
    ShowError::display("MP3Lyrics::addRow():\n" + QString(er.what())
//			+ " " + toString());
		);
    return -1;
  } catch (exception er) {
    ShowError::display("MP3Lyrics::addRow():\n" + QString(er.what()));
    return -1;
  }

	return 0;	
}
