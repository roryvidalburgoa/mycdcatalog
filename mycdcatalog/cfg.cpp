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

#include <iostream.h>
#include <strstream.h>
#include <qtextstream.h>
//#include <qarray.h>

extern "C" {
//#include <stdio.h>
#include <string.h>
}

#include "cfg.h"
#include "initform.h"

CFG * CFG::instance = 0;

ushort CFG::defPort = 3306;

CFG * CFG::getInstance() {
  if (instance)
    return instance;
  else return new CFG();
}

/** Constructor */
CFG::CFG() {
  device = "";
  mntpoint = "";
  username = "";
  socket = "";
  database = "";
  remote = true;
	eject = false;

  password = "";
  changed = false;
}

CFG::CFG(char * buf){
  size_t uint_s = sizeof(unsigned int);
	size_t bool_s = sizeof(bool);
  unsigned int sizes[5];

  char * cur = buf + uint_s; // drop total_size "unsigned int"
  memcpy (sizes, cur, 5 * uint_s);
  cur += 5 * uint_s;
  
  device = QString(cur); //cerr << sizes[0] << "\t";
  mntpoint = QString(cur += sizes[0]); //cerr << sizes[1] << "\t";
  username = QString(cur += sizes[1]); //cerr << sizes[2] << "\t";
  socket = QString(cur += sizes[2]); //cerr << sizes[3] << "\t";
  database = QString(cur += sizes[3]); //cerr << sizes[4] << "\t";

  memcpy (&remote, cur += sizes[4], bool_s);
  memcpy (&eject, cur += bool_s, bool_s);

  password = "";
  changed = false;
  //cerr << *((unsigned int *) buf) << endl;
}

/** Destructor */
CFG::~CFG() {
  instance = 0;
}

QString CFG::getMntPoint (  ){
  return mntpoint;
}

void CFG::putMntPoint ( QString mpoint ){
  mntpoint = mpoint;
}

QString CFG::getDevice (  ){
  return device;
}

void CFG::putDevice ( QString adev ){
  device = adev;
}

QString CFG::getUser (  ){
  return username;
}

void CFG::putUser ( QString user ){
  username = user;
}

QString CFG::getSocket (  ){
  return socket;
}

void CFG::putSocket ( QString s ){
  socket = s;
}

void CFG::display (  ){
  InitForm * iform = InitForm::getInstance();
	iform->openOn(this);
}

QString CFG::toString() {
  //	strstream aStream;
  QString str;
  QTextOStream(&str) << "Device: <" << device << ">"
		     << "\nMount Point: <" << mntpoint << ">"
		     << "\nUsername: <" << username << ">"
		     << "\nPassword: <" << password << ">"
		     << "\nRemote: <" << remote << ">"
		     << "\nSocket: <" << socket << ">"
		     << "\nDatabase: <" << database << ">"
		     << "\nChanged: <" << changed << ">"
		     << "\nEject: <" << eject << ">"
				 << endl;

  return str;
  /*	aStream << "Device: <" << device << ">";
	aStream << "\nMount Point: <" << mntpoint << ">";
	aStream << "\nUsername: <" << username << ">";
	aStream << "\nPassword: <" << password << ">"
	<< "\nRemote: <" << remote << ">";
	aStream << "\nSocket: <" << socket << ">";
	aStream << "\nDatabase: <" << database << ">";
	aStream << "\nChanged: <" << changed << ">" << ends;
	return aStream.str();*/
}

/** Print a config. */
void CFG::print(){
  cout << toString() << endl;
}

/** set instance */
void CFG::setInstance(CFG * aCFG){
  instance = aCFG;
}

/** Give byte representation of a CFG */
char * CFG::getBytes(){
  unsigned int total_size = 0;
  unsigned int string_sizes[5];

  string_sizes[0] = device.length() +1;
  string_sizes[1] = mntpoint.length() +1;
  string_sizes[2] = username.length() +1;
  string_sizes[3] = socket.length() +1;
  string_sizes[4] = database.length() +1;

  for (int i=0;i<5;i++) {
//    cerr << string_sizes[i] << "\t";
    total_size += string_sizes[i];
  }

  size_t uint_s = sizeof(unsigned int);
  size_t char_s = sizeof(char);
  size_t bool_s = sizeof(bool);

  total_size += 6 * uint_s + 2 * bool_s;

//  cerr << total_size << endl;

  char * buf = new char[total_size];
  char * ptr = buf;

  memcpy (ptr, &total_size, uint_s);
  memcpy (ptr += uint_s, string_sizes, 5 * uint_s);

  ptr += 5 * uint_s;
  if (string_sizes[0] > 1)
    memcpy (ptr, device.latin1(), string_sizes[0] * char_s);
  else *ptr = 0;

  ptr += string_sizes[0];
  if (string_sizes[1] > 1)
    memcpy (ptr, mntpoint.latin1(), string_sizes[1] * char_s);
  else *ptr = 0;

  ptr += string_sizes[1];
  if (string_sizes[2] > 1)
    memcpy (ptr, username.latin1(), string_sizes[2] * char_s);
  else *ptr=0;

  ptr += string_sizes[2];
  if (string_sizes[3] > 1)
    memcpy (ptr, socket.latin1(), string_sizes[3] * char_s);
  else *ptr=0;

  ptr += string_sizes[3];
  if (string_sizes[4] > 1)
    memcpy (ptr, database.latin1(), string_sizes[4] * char_s);
  else *ptr=0;

  memcpy (ptr += string_sizes[4], &remote, bool_s);
  memcpy (ptr += bool_s, &eject, bool_s);

  return buf;
}

void CFG::setDefaults () {
  device = "/dev/cdrom";
  mntpoint = "/mnt/cdrom";
  username = "root";
  socket = "localhost:6000";
  database = "test";
  remote = true;

  password = "";
  changed = false;
}
