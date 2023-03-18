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

#ifndef INITFORM_H
#define INITFORM_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <kapp.h>
#include <klocale.h>

#include <qbuttongroup.h>
#include <qcheckbox.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qradiobutton.h>
#include <qlayout.h>
#include <qvariant.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

#include "cfg.h"
#include "SInitForm.h"

class InitForm : public SInitForm {
  // Associations

  // Attributes
  private:
	static InitForm * instance;

  /** Option variable */
  bool remote;

  /** config to display */
  CFG * defCFG;

  private: // Operations
  /** constructor */
  InitForm();

  /** Check if given config is complete. */
  bool no_config();

  /** if config chaged from widget then put "cfg-> changed = true" */
  void update_config_if_changed();

  public:
  /** destructor */
  ~InitForm();

    void openOn ( CFG * );
/** For implement singleton pattern */
  static InitForm * getInstance();

	public slots:
	/** Overriding inherited methods */
	void local_slot();
	void read_slot();
	void remote_slot();
  void closer_slot();
};

#endif
