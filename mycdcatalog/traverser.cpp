/***************************************************************************
                          traverser.cpp  -  description
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

#include "traverser.h"

#include "showerror.h"
#include "filehandlerfactory.h"

#include <kapp.h>

//#include <kmimemagic.h>
#include <directory.h>
#include <file.h>
#include <qdir.h>
#include <stack.h>
#include <qdatetime.h>

const double conv_const = 1000.0 / 1024.0;

Traverser::Traverser(){
	mutex = new QMutex();
	cancel_exec = false;
//	nbThreads = 2;
}

Traverser::~Traverser(){
	delete mutex;
}

void Traverser::run ( ){
 	defCFG = CFG::getInstance();

//	mutex->lock();
//	if (nbThreads > 0)
//		nbThreads--;
//	mutex->unlock();
//
//	while (1) {
//		mutex->lock();
//		if (nbThreads > 0)
//			mutex->unlock();
//		else {
//			mutex->unlock();
//			break;
//		}
//	}

	if (readCD()<0) return;
//	requested->close();

	cerr << "Traverser::run() exiting..." << endl;
}

void Traverser::stop (  ){
	mutex->lock();
	cerr << "Traverser::stop()" << endl;
}

void Traverser::cancel (  ){
  if (mutex->locked()) mutex->unlock();
	mutex->lock();
	cancel_exec = true;
	cerr << "Traverser::cancel()" << endl;
	mutex->unlock();
}

void Traverser::resume (  ){
	cerr << "Traverser::resume()" << endl;
	mutex->unlock();
}

/** travers CD structure, read dir and files and store information into mysql db */
int Traverser::readCD() { // readCD()
  cerr << "Traverser::readCD()" << endl;
	KApplication * kApp = KApplication::kApplication();

  DirFile cur;
  stack<DirFile> aStack;
	FileType * ft = new FileType();

  FileHandlerFactory fhf = FileHandlerFactory();

  if (!QDir::setCurrent(defCFG->getMntPoint())) {
		kApp->lock();
    ShowError::display("Can't 'CD " + defCFG->getMntPoint() + "'");
		kApp->unlock();
		cerr << "Can't 'CD " << defCFG->getMntPoint() << "'" << endl;
    return -1;
  }

  aStack.push(DirFile("./"));
  unsigned int value = 0;

	QTime initTime;
  initTime.start();

	QTime beginTime;

  while(!aStack.empty()) { // while !stack.empty()
    mutex->lock();
    if (cancel_exec) { // if
      mutex->unlock();
      break;
    } // if
    mutex->unlock();

    cur = aStack.top(); aStack.pop();
    if (cur.exists()) { // exits()

//      mutex->lock();
kApp->lock();
      aRes->setCurDirFile(cur.filePath());		// Changing current file in widget
kApp->unlock();
//      mutex->unlock();

			if (cur.isFile()) { // isFile()

			  // time before reading a file
				beginTime.start();

				cdrom->nbFiles++;
				unsigned int parentid = cur.parent_id;
				File aFile = File(cur);
				aFile.parent_id = parentid;

// Finding file types.
				ft->extension = (aFile.extension(false)).lower();
				if (ft->findType(aFile.filePath()) < 0) {
					cdrom->unreadable_dirfiles ++;
					aFile.readable = false;
				} else aFile.readable = true;

				aFile.filetype = ft;

				requested->addRow(&aFile);		// set file->id.
//cout << aFile.filePath() << " : " << aFile.id << endl;
        FileHandler * fh = fhf.getFileHandler(ft);
				if (fh)
					fh->handleIt(&aFile, requested->getConnection());

//  else cerr << "None file handler found" << endl;
//				mutex->lock();
	{
kApp->lock();
				long s = aFile.size();
				aRes->setCurSize(value += s);		// Changing current size(progress bar)
				long e = beginTime.elapsed();
//cout << e << " milisecs ";
//cout << s << " bytes" << endl;
double myrate = (s/double(e)) * conv_const;

				aRes->setCurRate(myrate);
kApp->unlock();
	}
//				mutex->unlock();

      }
      else { // else isDir()
				cdrom->nbDirs++;
				unsigned short int parentid = cur.parent_id;
				Directory aDir = Directory(cur);
				aDir.parent_id = parentid;
				QDir curDir = QDir(aDir.filePath());
//	curDir.setFilter( QDir::NoSymLinks );
				aDir.NbDirFiles = curDir.count()-2; // "." and ".." not count

				curDir.setSorting(QDir::DirsFirst|QDir::Reversed);
				const QFileInfoList *list = curDir.entryInfoList();
				if (!list) {
					cdrom->unreadable_dirs++;
					cdrom->unreadable_dirfiles += aDir.NbDirFiles;
					aDir.readable = false;
          requested->addRow(&aDir); // adding an unreadable directory to db.
					cerr << "Directory unreadable: " << aDir.filePath() << endl;
					continue;
				} else {
					aDir.readable = true;
          requested->addRow(&aDir); // adding a directory to db, retreive dir id (aDir.id)
				}

				QFileInfoListIterator it( *list );      // create list iterator
				QFileInfo *fi;                          // pointer for traversing

				DirFile df;
        while ( (fi=it.current()) ) {           // for each file...
					df = DirFile(*fi);
					df.parent_id = aDir.id;

					if ((df.fileName() != ".") && (df.fileName() != "..")) {
//						cerr << "Successor: " << df.fileName() << endl;
				    aStack.push(df);		// adding successors into three
					}

	  			++it;                               // goto next list element
				} // for each file ...
			} // else isFile()
		} // exists()

//    mutex->unlock();
  } // while()

  if (!QDir::setCurrent("/")) {    // releasing CDROM mountpoint
kApp->lock();
    ShowError::display("Can't 'CD /'");
kApp->unlock();
		cerr << "Can't 'CD /'" << endl;
    return -1;
  }

	aRes->totalSize = value;
	cdrom->filesSize = value;
	//aRes->nbDirs = cdrom->nbDirs;
	//aRes->nbFiles = cdrom->nbFiles;

  if (!cancel_exec) {
    cdrom->complete = true;
//    mutex->lock();
kApp->lock();
    aRes->setCurSize(cdrom->size);
		aRes->setCurRate(conv_const * ( cdrom->size/double(initTime.elapsed()) ) );
	  aRes->setCurDirFile("<font color=\"#0000ff\">Reading CDROM completed!!!</font>");
kApp->unlock();
//    mutex->unlock();
  } else {
//    mutex->lock();
kApp->lock();
	  aRes->setCurDirFile("<font color=\"#ff0000\">Read CDROM incomplete!!!</font>");
kApp->unlock();
//    mutex->unlock();
	}

  requested->update(cdrom);
	cout << "Traverser::readCD()" << endl;
	return 0;
}// readCD()
