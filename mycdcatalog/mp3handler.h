/***************************************************************************
                          mp3handler.h  -  description
                             -------------------
    begin                : Fri May 3 2002
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

#ifndef MP3HANDLER_H
#define MP3HANDLER_H

#include "filehandler.h"

#include "mp3_id3.h"
#include "mp3_header.h"

/**MP3 File Handler.
  *@author Rory Vidal
  */

class MP3Handler : public FileHandler  {
public: 
	MP3Handler();
	~MP3Handler();
  /** true if can handle a file type. */
//  bool canHandleThis(FileType *);
  /** Handle a MP3 file. */
  void handleIt(File *,MysqlConnection *);
  /** Returns keys for a pdf file handler. */
  QVector<QString> * getKeys();

private: // Private methods

/** Normalize text to mysql syntaxe */
//	inline QString norm(QString);
//	inline QString norm(uint);
};

#endif
