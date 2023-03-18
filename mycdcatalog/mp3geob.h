/***************************************************************************
                          mp3geob.h  -  description
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

#ifndef MP3GEOB_H
#define MP3GEOB_H

#include <qstring.h>
#include <string>

#include "sqlmanager.h"

/**In this frame any type of file can be encapsulated. After the header, 'Frame size' and 'Encoding' follows 'MIME type' represented as as a terminated string encoded with ISO-8859-1. The filename is case sensitive and is encoded as 'Encoding'. Then follows a content description as terminated string, encoded as 'Encoding'. The last thing in the frame is the actual object. The first two strings may be omitted, leaving only their terminations. There may be more than one "GEOB" frame in each tag, but only one with the same content descriptor.
  *@author Rory Vidal
  */

class MP3GEOB {
public: 
	MP3GEOB();
	~MP3GEOB();
  /** to string */
  char * toString();
public: // Public attributes
  /** MIME type. */
  QString mimeType;
  /** Description of general encapsulated object. */
  QString description;
  /** Filename. */
  QString fileName;
  /** Size of Encapsulated object. */
  uint dataSize;
  /** Encapsulated object <binary data>. */
  string * eobject;

  /** Keep an general encapsulated object into DB. */
  int addRow(MysqlConnection*, int);
};

#endif
