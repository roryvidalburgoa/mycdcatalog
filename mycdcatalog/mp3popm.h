/***************************************************************************
                          mp3popm.h  -  description
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

#ifndef MP3POPM_H
#define MP3POPM_H

#include <qstring.h>

#include "sqlmanager.h"

/**The purpose of this frame is to specify how good an audio file is.
  *@author Rory Vidal
  */

class MP3POPM {
public: 
	MP3POPM();
	~MP3POPM();
public: // Public attributes
  /** Email to user <text string> $00 */
  QString email;
  /** Counter $xx xx xx xx (xx ...) */
  size_t counter;
  /** Rating $xx */
  size_t rating;

  /** Store a popularimeter into DB. */
  int addRow(MysqlConnection*,int);
};

#endif
