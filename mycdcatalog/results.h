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

#ifndef RESULTS_H
#define RESULTS_H

#include <qobject.h>
#include <qstring.h>
#include "volume.h"

class Results : public QObject
    {
  Q_OBJECT
  // Associations
  // Attributes
	private:
    int curSize;
    QString curDirFile;

		double curRate;
  /** curSize / aVol->size */
//  unsigned int percent;

  public:
//    int nbFiles;
//    int nbDirs;
    int totalSize;
		Volume * aVol;

  // Operations
  public:
	//Constructors
	Results();
	//Destructors
	~Results();


  void display (  );

  /** set curSize */
  void setCurSize(int);

  void setCurRate(double);

  /** print a results object */
  void print();

  /** set current directory or file read */
  void setCurDirFile(const QString &);

  /** get current directory or file. */
  QString getCurDirFile();

  /** String representation of a results */
  QString toString();

signals: // Signals
  /** signal that changes a QLabel text */
  void setCurDirFile_signal(const QString &);

  /** Change the value of curSize and emit a signal with
		* the actual percentage of work */
  void setCurSize_signal(int);

  void setCurRate_signal(double);
};

#endif
