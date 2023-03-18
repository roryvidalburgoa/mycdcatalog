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

#ifndef CFG_H
#define CFG_H

#include <qstring.h>

class CFG {
  // Associations

	private:
  // Attributes
	static CFG * instance;
    QString mntpoint;
    QString device;
    QString username;
    QString socket;

	public:
  /** default mysql port UDP or TCP: 3306 */
  static ushort defPort;

  bool changed;

  /**  */
  QString password;

  /**  */
  QString database;

  /** Signals if socket option is local or remote, if local it's a "local socket",
		* if not it's a "server:port" option. */
  bool remote;

  /** if true eject cdrom when finished */
  bool eject;

  // Operations
 private:
  /** Constructor */
  CFG( );

  public:
  /** Constructor from bytes */
  CFG(char *);

  /** Destructor */
  ~CFG( );
  static CFG * getInstance();

  /** Give byte representation of a CFG */
  char * getBytes();

  QString getMntPoint (  );
  void putMntPoint ( QString mntpoint );
  QString getDevice (  );
  void putDevice ( QString device );
  QString getUser (  );
  void putUser ( QString user );
  QString getSocket (  );
  void putSocket ( QString socket );

  void display (  );

  /** Print a config. */
  void print();

  /** config to string */
  QString toString();

  /** set instance */
  static void setInstance(CFG *);

  /** setting of a default configuration */
  void setDefaults();

};

#endif
