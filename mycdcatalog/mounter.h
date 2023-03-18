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

#ifndef MOUNTER_H
#define MOUNTER_H

#include <qstring.h>

class Mounter {
  // Associations
  // Attributes
  // Operations
  public:
    static int tomount ( QString mntpoint, QString device );
    static int tounmount ( QString device );
    static int toeject ( QString device );

//	private:
//		static bool mounted;
};

#endif
