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

#include "closer.h"
#include "mounter.h"

#include <iostream.h>

#include <kapp.h>

/** Constructor */
Closer::Closer(){
	not_mounted = true;
}

/** Destructor */
Closer::~Closer(){
}

void Closer::run (CFG * defCFG){

  if (defCFG) {
		if (not_mounted);
		else Mounter::tounmount(defCFG->getMntPoint());

		if (defCFG->eject)
			Mounter::toeject(defCFG->getDevice());

		if (defCFG->changed) {
			cfgwriter = new CFGManager();
			cfgwriter->writeFile(defCFG);
		}
   }

	cout << "Closing application\n";
	KApplication::kApplication()->quit();
}
