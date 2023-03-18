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

#ifndef SQLMANAGER_H
#define SQLMANAGER_H

#define MYSQL_NO_SHORT_NAMES
#include <sqlplus.hh>
//#undef null

#include "volume.h"
#include "directory.h"
#include "file.h"

#include "showerror.h"
#include <qregexp.h>

inline QString norm(uint value) {
	if (value) return QString::number(value);
	else return QString ("NULL");
}

inline QString norm(QString str) {
	QString res;

	if (!str || (str == "")) {
		res = "NULL";
	} else {
		res = str;
		res.replace(QRegExp("\""), "\\\"");
		res = "\"" + res + "\"";
	}

	return res;
}

class SQLManager {
  // Associations

  // Attributes
  /** A MySQL connection handler */
  MysqlConnection * con;

  // Operations
	private:
  /** real connection */
	int real_connect (const char *,const char *,const char *,const char *,const char *, unsigned int);

	int getOrCreate(QDateTime);
  /** get or create a extension entry */
  int getOrCreate(QString);
  /** get or create a file type entry */
  int getOrCreate(FileType *);
  /** delete files of a CDROM. */
  void delete_files(int);

	unsigned int last_vol_id;

  /** name of date times table is mysql server */
  static QString datetimes_table;

  /** name of extensions table: ".ext" */
  static QString extension_table;

  public:
  /** Constructor */
   SQLManager();

  /** Destructor */
   ~SQLManager();

  int addRow (Volume *);
  int addRow (Directory *);
  int addRow (File *);

  void close (  );

  /** Make a connection to a mysql unix socket. */
  int connect (const char *,const char *,const char *,const char *);

  /** Make a connection to a mysql server:port. */
  int connect(const char *,const char *,unsigned short int,const char *,const char *);

  /** updates a volume */
  int update(Volume *);
  /** Converts from a QDateTime to a the mysql datetime format */
  QString datetime(const QDateTime &);

  /** returns the current connection. */
  MysqlConnection * getConnection();
  /** Just do test rows in Volume and Directory. */
  void mk_test_rows(const uint);
  /** Deletes a volume row and their directories and their files. */
  void delete_volume(uint);
};

#endif
