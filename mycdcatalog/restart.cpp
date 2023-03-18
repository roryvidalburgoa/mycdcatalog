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

#include "restart.h"
#include "mounter.h"
#include "traverser.h"
#include "cfg.h"

/** Constructor */
ReStart::ReStart(){
}

/** Destructor */
ReStart::~ReStart(){
}

void ReStart::run (ResultsView * rview, Traverser * tr, Results * res){
	CFG * defCFG = CFG::getInstance();
//cerr << "waiting..."<<endl;
	tr->wait();
//cerr<<"tohide"<<endl;
	rview->hide();

delete rview; delete res;

/*cerr<<"toreset"<<endl;
	rview->reset();*/
//cerr<<"tomount"<<endl;
	Mounter::tounmount(defCFG->getMntPoint());
	if (defCFG->eject) Mounter::toeject(defCFG->getDevice());
/*cerr<<"todelres"<<endl;
	delete res;*/

//	delete rview;
//cerr<<"todeltr"<<endl;
	delete tr;
//cerr<<"toshow"<<endl;
	displayed = InitForm::getInstance();
	displayed->show();
}
