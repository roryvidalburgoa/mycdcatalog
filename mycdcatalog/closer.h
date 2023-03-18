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

#ifndef CLOSER_H
#define CLOSER_H

//#include "sqlmanager.h"
#include "cfgmanager.h"

class Closer {
  // Associations
   CFGManager * cfgwriter;
//   SQLManager * sqlcloser;
// Mounter * unmounter;

  // Attributes

  // Operations
  public:
    void run ( CFG * );
  /** Constructors */
	Closer();
	~Closer();

public: // Public attributes
  /** default true */
  bool not_mounted;
};

#endif
