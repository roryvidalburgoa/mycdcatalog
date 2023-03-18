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

#ifndef DIRFILE_H
#define DIRFILE_H

#include <qfileinfo.h>

class DirFile : public QFileInfo {
  public:

  /** last_id generated by AUTO_INCREMENT, LAST_INSERT_ID() */
  unsigned int parent_id; // a directory id

  /** identificator */
  unsigned int id;

  /** if true the directory or file is readable. */
  bool readable;

  // Operations
public: // Public methods
  /** Constructor */
   DirFile(QString);

  /** Constructor */
   DirFile();

  /**	Copy Constructor */
   DirFile(const QFileInfo &);
};

#endif
