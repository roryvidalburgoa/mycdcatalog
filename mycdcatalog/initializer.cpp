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

#include "initializer.h"

#include "session.h"
#include "filehandlerfactory.h"
#include "showerror.h"

#include <iostream.h>

#include <qtextstream.h>

CFG * defCFG = 0;
const uint TESTID = 9999;
bool delTestVolume;

void Initializer::run ( ){
	acfgmanager = new CFGManager();
	defCFG = acfgmanager->readFile();

	if (!defCFG)
		cerr << "Using an empty configuration" << endl;

  acfgmanager->showCFG();
}

void Initializer::testMode(KCmdLineArgs *args) {
	ShowError::gui = false;
	QVector<QString> * files = 0;

	QCString list = args->getOption("f");
	if (!list) list = args->getOption("filelist");

  delTestVolume = args->isSet("deleteTest") || args->isSet("d");

	int i,n;

	if (list) {//cerr << "(" << list << ")" << endl;
	  QFile f(list);
  	if ( f.open(IO_ReadOnly) ) {    // file opened successfully
    	QTextStream t( &f );        // use a text stream
      QString s;
      n = 0;
      while ( !t.eof() ) {        // until end of file...
          t.readLine();       // line of text excluding '\n'
					n++;
      }

			if (!files)
				files = new QVector<QString> (args->count()+n);

			f.at(0);

      while ( !t.eof() ) {        // until end of file...
				files->insert(files->count(), new QString(t.readLine()));
      }

      f.close();
		}
	}

	if (!files)
		files = new QVector<QString> (args->count());

	for (i=0; i < args->count(); i++) // Counting start at 0!
   {
			files->insert(files->count(), new QString(args->arg(i)));
   }

  args->clear(); // Free up some memory

	processFiles(files);
}

void Initializer::processFiles(QVector<QString> * files) {
	acfgmanager = new CFGManager();
	defCFG = acfgmanager->readFile();

	if (!defCFG) {
		defCFG = CFG::getInstance();
		defCFG->setDefaults();
	}

	QString password = "";
	char p[128];
	while (password.length() == 0) { // don't want to use strlen()
		cout << "Give a password:" << endl;
		cin >> p;
		password = p;
	}

	defCFG->password = password;
//	defCFG->password = QString("");

//	defCFG->print();

	Session * s = new Session();
	s->test(defCFG);

	SQLManager * requested = s->getSQL();
	if(delTestVolume) {
		requested->delete_volume(TESTID);
//		requested->delete_volume(0);
		return;
  }

  File cur;
	FileType * ft = new FileType();
  FileHandlerFactory fhf = FileHandlerFactory();

//adding test rows in tables.
	requested->mk_test_rows(TESTID);

	for (int i=0; i< files->count() ; i++) {
			cout << "[" << i << "] \"" << *(files->at(i)) << "\" : ";
			cur = File( QFileInfo( *(files->at(i)) ) );
			cur.parent_id = TESTID;

// Finding file types.
			ft->extension = cur.extension(false);
			if (ft->findType(cur.filePath()) < 0) {
				cerr << "Unreadable file!" << endl;
				cur.filetype = ft;
				cur.readable = false;
				requested->addRow(&cur);		// set file->id.
				continue;
			} else {
				cur.filetype = ft;
				cur.readable = true;
				requested->addRow(&cur);		// set file->id.
			}

  	    FileHandler * fh = fhf.getFileHandler(ft);
				if (fh)
					fh->handleIt(&cur, requested->getConnection());
        cout << "OK" << endl;
	}
	s->finishSQLConnection();
}
