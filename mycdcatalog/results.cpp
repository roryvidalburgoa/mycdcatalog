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

#include "results.h"
#include "resultsview.h"

#include <iostream.h>
#include <qtextstream.h>

#include <klocale.h>

Results::Results() {
//	percent = 0;
	aVol = 0;
	curDirFile = "";
	curSize = 0;
  curRate = 0.0;
//	nbDirs = 0;
//	nbFiles = 0;
	totalSize = 0;
}

Results::~Results() {
	delete curDirFile;
	delete aVol;
}

void Results::display (  ){
	ResultsView * rview = ResultsView::getInstance();

	rview->setCaption( i18n("CD Reading...") );
	rview->aProgressBar->setTotalSteps(aVol->size);

//	cout << "connecting slots and signals" << endl;

//	if (connect(this, SIGNAL(setCurSize_signal(int)),
//							rview, SLOT(setSizeProgress(int))))
//		cout << "setProgress connected" << endl;
//	else cout << "setProgress NOT connected" << endl;

	connect(this, SIGNAL(setCurSize_signal(int)),
							rview, SLOT(setSizeProgress(int)));

	connect(this, SIGNAL(setCurRate_signal(double)),
							rview, SLOT(setDownloadRate(double)));

//	if (connect(this, SIGNAL(setCurDirFile_signal(const QString &)),
//							rview, SLOT(setDirFileText(const QString &))))
//		cout << "setCurrentDirFile connected" << endl;
//	else cout << "setCurrentDirFile NOT connected" << endl;

	connect(this, SIGNAL(setCurDirFile_signal(const QString &)),
							rview, SLOT(setDirFileText(const QString &)));

	rview->openOn(this);
}

/** print a results object */
void Results::print(){
	cout << toString() << endl;
}

/** set curSize */
void Results::setCurSize(int v){
	 	curSize = v;
    emit setCurSize_signal(v);
}

/** set curDTime */
void Results::setCurRate(double v){
	 	curRate = v;
    emit setCurRate_signal(v);
}

/** set current directory or file read */
void Results::setCurDirFile(const QString & qs){
		curDirFile = qs;
		emit setCurDirFile_signal(qs);
}

/** String representation of a result */
QString Results::toString() {
	QString str;
	QTextOStream (&str) << "<div align=\"center\">\n<table border=\"0\" cellpading=\"5\">"
		<< "<tr> <td align=\"center\" colspan=\"2\" bgcolor=\"#D3DCE3\">" << curDirFile << "</td> </tr>"
		<< "<tr> <td bgcolor=\"#CCCCCC\">Volume Size:</td> <td align=\"right\" bgcolor=\"#CCCCCC\">"
		<< aVol->size/1048576.0 << " Mbytes. </td> </tr>"
		<< "<tr> <td bgcolor=\"#CCCCCC\">Number of directories:</td> <td align=\"right\" bgcolor=\"#CCCCCC\">"
		<< aVol->nbDirs << "</td> </tr>"
		<< "<tr> <td bgcolor=\"#CCCCCC\">Number of files:</td> <td align=\"right\" bgcolor=\"#CCCCCC\">"
		<< aVol->nbFiles << "</td> </tr>"
		<< "<tr> <td bgcolor=\"#CCCCCC\">Total Files size:</td> <td align=\"right\" bgcolor=\"#CCCCCC\">"
		<< totalSize/1048576.0 << " Mbytes. </td> </tr>"
		<< "<tr> <td bgcolor=\"#CCCCCC\">Volume ID:</td> <td align=\"right\" bgcolor=\"#CCCCCC\">"
		<< aVol->vol_id << "</td> </tr>"
		<< "<tr> <td bgcolor=\"#CCCCCC\">Unreadable Directories:</td> <td align=\"right\" bgcolor=\"#CCCCCC\">"
		<< "<font color=\"#ff0000\">" << aVol->unreadable_dirs << " </font> </td> </tr>"
		<< "<tr> <td bgcolor=\"#CCCCCC\">Unreadable Files:</td> <td align=\"right\" bgcolor=\"#CCCCCC\">"
		<< "<font color=\"#ff0000\">" << aVol->unreadable_dirfiles - aVol->unreadable_dirs << " </font> </td> </tr>"
		<< "</table> </div>" << endl;
	return str;
}

/** get current directory or file. */
QString Results::getCurDirFile(){
	return curDirFile;
}
