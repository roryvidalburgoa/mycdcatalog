/***************************************************************************
                          mp3apic.cpp  -  description
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

#include "mp3apic.h"

QString mp3apic_table = "MP3APIC";

MP3APIC::MP3APIC(){
	format=description=mimeType="";
	picSize=picType=0;
	picture=0;
}

MP3APIC::~MP3APIC(){
	delete [] picture;
}

int MP3APIC::addRow(MysqlConnection * curConn, int fileid) {
  try {
		MysqlQuery query = curConn->query();
		ostrstream strbuf;
    strbuf.clear();

		strbuf << "INSERT INTO " << mp3apic_table << " VALUES (NULL, "
				<< fileid << ","
				<< norm( mimeType ) << ","
				<< norm( format ) << ","
				<< norm( picType ) << ","
				<< norm( description ) << ","
				<< picSize << ", \"" <<
				mysql_escape << *(picture) << "\" );" << ends;

//cout << strbuf.str() << endl;
				query.exec(strbuf.str());
	} catch (MysqlBadQuery er) { // handle any connection or
                          // query errors that may come up
    ShowError::display("MP3APIC::addRow():\n" + QString(er.what())
//			+ " " + toString());
		);
    return -1;
  } catch (exception er) {
    ShowError::display("MP3APIC::addRow():\n" + QString(er.what()));
    return -1;
  }

	return 0;	
}
