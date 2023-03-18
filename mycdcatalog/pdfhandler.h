/***************************************************************************
                          pdfhandler.h  -  description
                             -------------------
    begin                : Fri May 3 2002
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

#ifndef PDFHANDLER_H
#define PDFHANDLER_H

#include "filehandler.h"

/**PDF File Handler.
  *@author Rory Vidal
  */

class PDFHandler : public FileHandler  {
public: 
	PDFHandler();
	~PDFHandler();
  /** true if can handle a file type. */
  bool canHandleThis(FileType *);
  /** Handle a PDF file. */
  void handleIt(File *,MysqlConnection *);
  /** Returns keys for a mp3 file handler. */
  QVector<QString> * getKeys();
};

#endif
