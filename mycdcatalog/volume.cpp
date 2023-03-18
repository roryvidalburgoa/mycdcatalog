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

#include "volume.h"
#include <iostream.h>
#include <qtextstream.h>

/** table name */
const char * Volume::table_name = "Volume";

/** Constructor */
Volume::Volume(){
	unreadable_dirfiles = unreadable_dirs = nbFiles = nbDirs = 0;
	complete = false;
}

/** Print a volume object */
void Volume::print(){
	cout << toString() << endl;
}

/** String representation of a Volume. */
QString Volume::toString(){
	QString str;
	QTextOStream (&str) << "<div align=\"center\"> <table border=\"0\" cellpading=\"1\">"
		<< "<tr> <td align=\"center\" colspan=\"2\" bgcolor=\"#D3DCE3\">" << vol_id << "</td> </tr>"
		<< "<tr> <td align=\"center\" colspan=\"2\" bgcolor=\"#CCCCCC\">CD-ROM is in ISO 9660 format</td> </tr>"
		<< "<tr> <td bgcolor=\"#CCCCCC\">System id:</td> <td align=\"right\" bgcolor=\"#CCCCCC\">" << sys_id << "</td></tr>"
		<< "<tr> <td bgcolor=\"#CCCCCC\">Volume id:</td> <td align=\"right\" bgcolor=\"#CCCCCC\">" << vol_id << "</td></tr>"
		<< "<tr> <td bgcolor=\"#CCCCCC\">Publisher id:</td> <td align=\"right\" bgcolor=\"#CCCCCC\">" << pub_id << "</td></tr>"
		<< "<tr> <td bgcolor=\"#CCCCCC\">Data preparer id:</td> <td align=\"right\" bgcolor=\"#CCCCCC\">" << preparer << "</td></tr>"
		<< "<tr> <td bgcolor=\"#CCCCCC\">Application id:</td> <td align=\"right\" bgcolor=\"#CCCCCC\">" << app_id << "</td></tr>"
//		<< "<tr> <td bgcolor=\"#CCCCCC\">NbDirs:</td> <td bgcolor=\"#CCCCCC\">" << nbDirs << "</td></tr>"
//		<< "<tr> <td bgcolor=\"#CCCCCC\">NbFiles:</td> <td bgcolor=\"#CCCCCC\">" << nbFiles << "</td></tr>"
		<< "<tr> <td bgcolor=\"#CCCCCC\">Size:</td> <td align=\"right\" bgcolor=\"#CCCCCC\">"
		<< size / 1048576.0 << " Mbytes </td> </tr>"
		<< "</table> </div>" << endl;
	return str;
}
