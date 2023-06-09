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

#ifndef VOLUME_H
#define VOLUME_H

#include "directory.h"
#include <qstring.h>

class Volume {
  // Associations
   Directory * root;

  // Attributes
  public:
    char * vol_id;
    char * sys_id;
		char * pub_id;
		char * preparer;
		char * app_id;
    int size;
    int nbDirs;
    int nbFiles;

  /** Table name of this class into db */
  static const char * table_name;

  /** id generated by the mysql_id */
  unsigned int mysql_id;

  /** status of data cd */
  unsigned short int status;

  /** true if reading CDROM was completed */
  bool complete;

  /** unreadable directories */
  unsigned int unreadable_dirs;

  /** Unreadable directories or files */
  unsigned int unreadable_dirfiles;

  /** Sum Size of all readable files in CDROM. */
  uint filesSize;

  // Operations
public: // Public methods
  /** Print a volume object */
  void print();

  /** String representation of a Volume. */
  QString toString();

  /** Constructor */
   Volume();
};

#endif
