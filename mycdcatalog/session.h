/***************************************************************************
                          session.h  -  description
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

#ifndef SESSION_H
#define SESSION_H

#include "cfg.h"
#include "volume.h"
#include "sqlmanager.h"
#include "results.h"

/**Starts a newly reading CDROM session
  *@author Rory Vidal
  */

class Session {
// Associations
private:
   Volume * cdrom;
   SQLManager * requested;
   Results * aRes;
   CFG * defCFG;

public:
	Session();
	~Session();

  /** Starts a session */
  int run(CFG *);

  /** close mysql connection. */
  void finishSQLConnection();
  /** Testing with some files. */
  int test(CFG *aCFG);
  /** returns requested. */
  SQLManager * getSQL();

private:
/** Start connection to a mysql server */
	int initSQLConnection();

  /** open CDROM, takes their info and mounts it. */
  int openCDROM();
  /** reading magic file. */
  int readMagic();

};

#endif
