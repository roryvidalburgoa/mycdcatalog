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

#include "resultsview.h"
#include "closer.h"
#include "restart.h"
#include "cfg.h"

#include <iostream.h>

#include <kapp.h>

/** definition of a STATIC member */
ResultsView * ResultsView::instance = 0;

ResultsView::ResultsView()
{
}

ResultsView::~ResultsView()
{
	instance = 0;
//	delete instance;
}

/** For implement singleton pattern */
ResultsView * ResultsView::getInstance(){
	if (!instance) {
//		instance = 1;
		instance = new ResultsView();
//		return new InitForm();
	} //else return 0;
	return instance;
}

void ResultsView::openOn ( Results * aResult ){
	defRes = aResult;
//	VolumeData->clear();
	VolumeData->setText(defRes->aVol->toString());
	currentDirFile->setText(i18n("/"));
	show();
	return;
}

void ResultsView::cancel_slot()
{
	if (Cancel->text() == "&Cancel") {
		// Cancel reading process
		Stop->setText( i18n("&ReStart") );
		Cancel->setText ( i18n("&Close") );
		tree_parser->cancel();

	} else if (Cancel->text() == "&Close") {
		// Close application
		Closer * cl = new Closer();
		tree_parser->wait();
		cl->not_mounted = false;
		cl->run(CFG::getInstance());

	} else {
		qWarning( "ResView::cancel_slot(): Some big error!" );
		qWarning( Cancel->text() );
	}
}

void ResultsView::stop_resume_slot()
{
	if (Stop->text() == "&Stop") {
		// Stop reader
		Stop->setText( i18n("&Resume") );
		tree_parser->stop();

	} else if (Stop->text() == "&ReStart") {
		// Restart showing InitForm
		ReStart * restart = new ReStart();
		restart->run(this , tree_parser , defRes);
		delete restart;

	} else if (Stop->text() == "&Resume") {
		// Resume reader
		tree_parser->resume();
		Stop->setText(i18n("&Stop"));

	} else {
		qWarning( "ResView::stop_resume_slot(): Some big error!" );
		qWarning( Stop->text() );
	}
}

/** The reader thread */
void ResultsView::setTraverser(Traverser * tr) {
	tree_parser = tr;
}

/** change progress bar */
void ResultsView::setSizeProgress(int val) {
//	cout << "Changing progress bar value: " << val << endl;
	aProgressBar->setProgress(val);
//  update();
	aProgressBar->update();
}

/** change download time */
void ResultsView::setDownloadRate(double val) {
//	cout << "Changing download time value: " << val << endl;
  QString t;// = QString::number(val,'g',2) + " KB/S.";
if (val < 1)
	t.sprintf("%.2f B/Sec.",val*1024);
else
	t.sprintf("%.2f KB/Sec.",val);
//cout << "Rate: " << val << endl;
	rate->setText(t);
//  update();
	rate->update();
}

/** Change the QLabel text for currentDirFile */
void ResultsView::setDirFileText(const QString & qs){
//	cout << "Changing qlabel current dirfile value: " << qs << endl;
//	currentDirFile->clear();
//KApplication::kApplication()->lock();
	currentDirFile->setText(qs);
//KApplication::kApplication()->unlock();
//	currentDirFile->update();
	currentDirFile->repaint();
}

/** Reset internal state */
void ResultsView::reset(){
//	VolumeData->clear();
cerr<<"tosettextvolume"<<endl;
	VolumeData->setText(i18n(""));
cerr<<"tosettextcurdirfile"<<endl;
	currentDirFile->setText(i18n(""));
cerr<<"toresetpbar"<<endl;
	aProgressBar->reset();
cerr<<"tosettextstop"<<endl;
  Stop->setText(i18n("&Stop"));
cerr<<"tosettextcancel"<<endl;
	Cancel->setText(i18n("&Cancel"));
cerr<<"totree_parser=0"<<endl;
	tree_parser = 0;
cerr<<"todefres=0"<<endl;
	defRes = 0;
  rate->setText(i18n(""));
}
