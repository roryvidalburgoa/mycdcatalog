/***************************************************************************
                          cdreader.h  -  description
                             -------------------
    begin                : Mon Apr 22 2002
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

#ifndef CDREADER_H
#define CDREADER_H

#include "volume.h"
#include <qstring.h>

/**This is responsible for
check if a device contains a CDROM
check if it's a Data CDROM
check if it's a ISO9660 volume.
In the future will handle other file system volumes
Takes information from volume
  *@author Rory Vidal
  */

class CDReader {
public:
	CDReader();
	~CDReader();

  /** This method reads the CD information, it's the interface with the device and
	 * the main method of the class. */
  Volume * readCDInfo(QString);

private: // Private methods
	char * render_chars (char *,int);
	int	isonum_721	(char *);
	int	isonum_723	(char *);
	int	isonum_731	(char *);
  int isonum_733 (char *);

};

#endif
