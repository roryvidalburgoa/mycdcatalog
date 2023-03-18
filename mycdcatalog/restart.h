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

#ifndef RESTART_H
#define RESTART_H

#include "initform.h"
#include "traverser.h"
#include "resultsview.h"
#include "results.h"

class ReStart {
  // Associations
   InitForm * displayed;
  // Attributes
  // Operations
  public:
		void run (ResultsView *, Traverser *, Results *);

  /** Constructor */
		ReStart();
  /** Destructor */
		~ReStart();
};

#endif
