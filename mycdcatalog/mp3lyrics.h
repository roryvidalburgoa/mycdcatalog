/***************************************************************************
                          mp3lyrics.h  -  description
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

#ifndef MP3LYRICS_H
#define MP3LYRICS_H

#include <qstring.h>

#include "sqlmanager.h"

/**This frame contains the lyrics of the song or a text transcription of other vocal activities.
  *@author Rory Vidal
  */

class MP3Lyrics {
public: 
	MP3Lyrics();
	~MP3Lyrics();
public: // Public attributes
  /** Unsychronised lyrics/text transcription.
		* Lyrics/text <full text string according to encoding>
		*/
  QString lyrics;
  /** Content descriptor <text string according to encoding> $00 (00) */
  QString description;
  /** Language $xx xx xx */
  QString lang;

public: // Public methods
  /** Keep a MP3Lyrics into DB. */
  int addRow(MysqlConnection *, int);

private:
};

#endif
