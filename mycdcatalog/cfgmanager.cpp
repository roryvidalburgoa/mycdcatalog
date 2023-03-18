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

#include "cfgmanager.h"
#include <iostream.h>
#include <fstream.h>

extern "C" {
#include <string.h>
#include <stdlib.h>
}

CFGManager::CFGManager() {
	char * home = getenv("HOME");
	if (!home) config_file = strdup(".mycdcatalog");
	else {
		config_file = new char[strlen(home)+strlen(".mycdcatalog")+2]; // home + "/" + cfgname + '\0'
		strcpy(config_file,home);
		strcat(config_file,"/.mycdcatalog");
	}
//	cerr << config_file << endl;
}

CFG * CFGManager::readFile ( ){
	return readFile(config_file);
}

CFG * CFGManager::readFile ( const char * CFGFile){
	return readFile((char *) CFGFile);
}

CFG * CFGManager::readFile ( char * CFGFile ){
//	managed = CFG::getInstance();
  ifstream cfile(CFGFile);

  if (cfile.good()) {
    unsigned int size;
    size_t uint_s = sizeof(unsigned int);

//    cerr << "file.read(size)= " <<
      cfile.read((char *) &size, uint_s);
//<< endl;
//    cerr << "total_size = " << size;

    char * buffer = new char[size];
    cfile.seekg(0L, ios::beg);
//    cerr << "file.read(buffer)= " <<
      cfile.read(buffer, size);
// << endl;
//    cerr << "buffer: " << buffer;

    managed = new CFG(buffer);
  } else {
    cerr << "Error opening config file to read: " << CFGFile << endl;
		managed = CFG::getInstance();
    return 0;
  }

  cfile.close();
  return managed;
}

void CFGManager::showCFG ( ){
	if (!managed)
		managed = CFG::getInstance();
	else
		CFG::setInstance(managed);

//	managed->print();
//	CFG::getInstance()->print();
	managed->display();
}

int CFGManager::writeFile ( CFG * aCFG ){
	return writeFile( aCFG ,  config_file );
}

int CFGManager::writeFile ( CFG * aCFG , const char * CFGFile){
	return writeFile( aCFG , CFGFile );
}

int CFGManager::writeFile ( CFG * aCFG , char * CFGFile){
  if (aCFG == 0) {
    if (managed == 0)
      return -1;
    else aCFG = managed;
  }

  ofstream cfile(CFGFile);

  if (cfile.good()) {
    char * buffer = aCFG->getBytes();
    unsigned int size;
    memcpy (&size, buffer, sizeof(unsigned int));
//    cerr << "CGFManager::writeFile: writting config " << size << " bytes" <<
      cfile.write(buffer,size); // << endl;
//	cerr << config_file << endl;
  } else {
    cerr << "Error opening config file to write: " << CFGFile << endl;
    return -1;
  }

  cfile.close();
  return 0;
}

/** Returns managed. */
//Del by KDevelop: CFG * CFGManager::getCFG(){
//Del by KDevelop: 	return managed;
//Del by KDevelop: }
