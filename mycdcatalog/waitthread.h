/***************************************************************************
                          WaitThread.h  -  description
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

#ifndef WAITTHREAD_H
#define WAITTHREAD_H

#include <qthread.h>
#include "results.h"
#include "traverser.h"
#include "session.h"

/**just do tr.wait()
  *@author Rory Vidal
  */

class WaitThread : public QThread  {
public: // Public attributes
  /** a results */
  Results * aRes;

  /** traverser */
  Traverser * tr;

	/** session */
	Session * s;
public:
	WaitThread();
	~WaitThread();

protected:
  /** exec thread */
  void run();
};

#endif
