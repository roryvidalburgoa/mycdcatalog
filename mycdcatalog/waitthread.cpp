/***************************************************************************
                          WaitThread.cpp  -  description
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

#include "waitthread.h"
#include "resultsview.h"

#include <klocale.h>
#include <kapp.h>

WaitThread::WaitThread(){
}

WaitThread::~WaitThread(){
}

/** exec thread */
void WaitThread::run(){

//	tr->mutex->lock();
//	if (tr->nbThreads > 0)
//		tr->nbThreads--;
//	tr->mutex->unlock();
//
//	while (1) {
//		tr->mutex->lock();
//		if (tr->nbThreads > 0)
//			tr->mutex->unlock();
//		else {
//			tr->mutex->unlock();
//			break;
//		}
//	}

	tr->wait();

/// to comment

/// Put code to say that read process has finished, show results partial or complete.
/// Change button names.
KApplication * kApp = KApplication::kApplication();
	ResultsView * rview = ResultsView::getInstance();
	
kApp->lock();
	if (
	//aRes->getCurDirFile() == "<font color=\"#ff0000\">Reading CDROM completed!!!</font>"
		tr->cdrom->complete
	) {
		rview->Stop->setText( i18n("&ReStart") );
		rview->Cancel->setText ( i18n("&Close") );
		rview->setCaption( i18n("Read process finished!") );
	}

	rview->VolumeData->setText(aRes->toString());
  rview->VolumeData->repaint();
	rview->Stop->repaint();
	rview->Cancel->repaint();
	rview->currentDirFile->repaint();
	rview->repaint();
kApp->unlock();

	s->finishSQLConnection();
//	delete s;
}
