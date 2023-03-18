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

#ifndef CFGMANAGER_H
#define CFGMANAGER_H

#include "cfg.h"

class CFGManager {
  // Associations
   CFG * managed;

	public:
  // Attributes
	char * config_file;

  // Operations
  public:
		CFGManager();
		~CFGManager();

    CFG * readFile ( const char * );
		CFG * readFile ( char * );
		CFG * readFile ( );
    void showCFG ();
		int writeFile ( CFG * aCFG , const char * );
    int writeFile ( CFG * aCFG, char * );
    int writeFile ( CFG * aCFG );
  /** Returns managed. */


};

#endif
