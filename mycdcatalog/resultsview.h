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

#ifndef RESULTSVIEW_H
#define RESULTSVIEW_H

#include <qframe.h>
#include <qlabel.h>
#include <qprogressbar.h>
#include <qpushbutton.h>
#include <qtextview.h>
#include <qlayout.h>
#include <qvariant.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

#include "SResView.h"
#include "traverser.h"
#include "results.h"

class ResultsView : public SResView {
	Q_OBJECT
  private:
  // Associations
		Results * defRes;

  // Attributes
		static ResultsView * instance;

  /** Reader thread */
		Traverser * tree_parser;

    /** constructor */
    ResultsView();

  // Operations
  public:
    /** destructor */
    ~ResultsView();

/** For implement singleton pattern */
	  static ResultsView * getInstance();

    void openOn ( Results * );

  /** The reader thread */
  void setTraverser(Traverser *);

  /** Reset internal state */
  void reset();

public slots: // Public slots
  /** Change the QLabel text for currentDirFile */
  void setDirFileText(const QString &);

  /** change progress bar */
  void setSizeProgress(int);

  /** change download time */
  void setDownloadRate(double);

/** Overriding slot methods inherited from SResView */
		void cancel_slot();
    void stop_resume_slot();
};

#endif
