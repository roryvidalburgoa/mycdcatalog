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

#ifndef INITIALIZER_H
#define INITIALIZER_H

#include "cfgmanager.h"

#include <kcmdlineargs.h>
#include <qvector.h>

class Initializer {
  // Associations
   CFGManager * acfgmanager;
  // Attributes

  // Operations
  public:
    void run ();

		void testMode (KCmdLineArgs *);

	private:
		void processFiles(QVector<QString> *);
};

#endif
