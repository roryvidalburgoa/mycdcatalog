/***************************************************************************
                          mp3geob.cpp  -  description
                             -------------------
    begin                : Sat May 4 2002
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

#include "mp3geob.h"
#include <strstream.h>

QString mp3geob_table = "MP3GEOB";

MP3GEOB::MP3GEOB(){
	dataSize=0;
	description=fileName=mimeType="";
	eobject=0;
}

MP3GEOB::~MP3GEOB(){
}

/** to string */
char * MP3GEOB::toString(){
	ostrstream strbuf;
	strbuf.clear();
	strbuf << "Size: " << dataSize
		<< "\nDescription: " << description
		<< "\nFilename: " << fileName
		<< "\nMimeType: " << mimeType << ends;
	return strbuf.str();
}

/** Keep a general encapsulated object into DB. */
int MP3GEOB::addRow(MysqlConnection * curConn, int fileid){
//cerr << "addRow(MP3GEOB*)" << endl;
  try {
		MysqlQuery query = curConn->query();
		ostrstream strbuf;
    strbuf.clear();

		strbuf << "INSERT INTO " << mp3geob_table << " VALUES ("
				<< fileid << "," << norm( description ) << ","
				<< norm( fileName ) << "," << norm( mimeType ) << ","
				<< dataSize << ", \"" <<
				mysql_escape << *(eobject) << "\" );" << ends;

//cout << strbuf.str() << endl;
				query.exec(strbuf.str());
	} catch (MysqlBadQuery er) { // handle any connection or
                          // query errors that may come up
    ShowError::display("MP3GEOB::addRow():\n" + QString(er.what())
//			+ " " + toString());
		);
    return -1;
  } catch (exception er) {
    ShowError::display("MP3GEOB::addRow():\n" + QString(er.what()));
    return -1;
  }

	return 0;	
}
