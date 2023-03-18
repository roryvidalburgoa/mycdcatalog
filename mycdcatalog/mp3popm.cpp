/***************************************************************************
                          mp3popm.cpp  -  description
                             -------------------
    begin                : Sun May 5 2002
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

#include "mp3popm.h"

/** POPM's table */
QString mp3popm_table = "MP3POPM";

MP3POPM::MP3POPM(){
 email="";
 counter=rating=0;
}

MP3POPM::~MP3POPM(){
}

/** Store a popularimeter into DB. */
int MP3POPM::addRow(MysqlConnection* curConn, int fileid){
//cerr << "addRow(MP3POPM*)" << endl;
  try {
		MysqlQuery query = curConn->query();

		query << "INSERT INTO " << mp3popm_table << " VALUES ("
				<< fileid << "," << norm( email ) << ","
				<< rating << "," << counter
				<< ");" << ends;

				query.execute();
	} catch (MysqlBadQuery er) { // handle any connection or
                          // query errors that may come up
    ShowError::display("MP3POPM::addRow():\n" + QString(er.what())
//			+ " " + eobj->toString());
		);
    return -1;
  } catch (exception er) {
    ShowError::display("MP3POPM::addRow():\n" + QString(er.what()));
    return -1;
  }

	return 0;	
}
