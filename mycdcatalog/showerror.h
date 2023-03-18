/***************************************************************************
                          showerror.h  -  description
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

#ifndef SHOWERROR_H
#define SHOWERROR_H

#include <qstring.h>

/**Show error messages, looking at errno
variable and also user error messages
  *@author Rory Vidal
  */

class ShowError {
public: 
	ShowError();
	~ShowError();

  /** display error messages. */
  static void display(QString);

public: // Public attributes
  /** if true show a message box, if false print to cerr. */
  static bool gui;
};

#endif
