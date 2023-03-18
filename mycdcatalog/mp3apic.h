/***************************************************************************
                          mp3apic.h  -  description
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

#ifndef MP3APIC_H
#define MP3APIC_H

#include <qstring.h>
#include <string>

#include "sqlmanager.h"

/**Attached Picture.
  *@author Rory Vidal
  */

class MP3APIC {
public: 
	MP3APIC();
	~MP3APIC();
public: // Public attributes
  /** MIME type <text string> $00 */
  QString mimeType;
  /** Picture data <binary data> */
  string * picture;
  /** Picture type $xx */
  uint picType;
  /** Description <text string according to encoding> $00 (00) */
  QString description;
  /** Image Format */
  QString format;
  /** picture length in bytes. */
  uint picSize;

public: // Public members
  /** Keep a MP3APIC into DB. */
  int addRow(MysqlConnection *, int);
};

#endif
