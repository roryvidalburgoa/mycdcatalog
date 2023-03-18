/***************************************************************************
                          traverser.h  -  description
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

#ifndef TRAVERSER_H
#define TRAVERSER_H

#include <qthread.h>


#include "cfg.h"
#include "results.h"
#include "volume.h"
#include "sqlmanager.h"

/**Thread that travers the CDROM three, when it finds
a file it saves their info into mysql db, same thing for
directories.
  *@author Rory Vidal
  */

class Traverser : public QThread  {

public: // Public attributes
  /** Takes control of the execution thread (Read) if unlocked */
  QMutex * mutex;

  /** default result */
  Results * aRes;

  /** represents cdrom volume */
  Volume * cdrom;

  /** a sql manager */
  SQLManager * requested;

  /** number of threads to wait for */
//  int nbThreads;

  // Public services
	Traverser();
	~Traverser();

  void stop (  );
  void cancel (  );
  void resume (  );

  void putResult(Results *);

private:
  // Attributes
  /** 1 then cancel Reader execution, 0 continue execution. */
	bool cancel_exec;

  /** default config */
  CFG * defCFG;

  // Private methods
  /** travers CD structure, read dir and files and store information into mysql db */
  int readCD();

protected:
	// implements start()
  void run (  );
};

#endif
