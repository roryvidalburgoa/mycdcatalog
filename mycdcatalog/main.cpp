/***************************************************************************
                          main.cpp  -  description
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

#include <kcmdlineargs.h>
#include <kaboutdata.h>
#include <klocale.h>

#include "initform.h"
#include "initializer.h"

#include <iostream.h>

static const char *description =
	I18N_NOOP("MyCDCatalog");
// INSERT A DESCRIPTION FOR YOUR APPLICATION HERE
	
	
static KCmdLineOptions moptions[] =
{
		{"f <filelist>", 0, 0},
		{"filelist <filelist>", I18N_NOOP("A list of files."), 0},

//		{"p", 0, 0},
//		{"password", I18N_NOOP("mysql password.") ,0},

		{"d", 0, 0},
		{"deleteTest", I18N_NOOP("Delete test rows."), 0},

    { "!+[files]", I18N_NOOP("files to use."), 0 },
    { 0, 0, 0 } // End of options.
};


int main(int argc, char *argv[])
{
  KAboutData aboutData( "mycdcatalog", I18N_NOOP("MyCDCatalog"),
    VERSION, description, KAboutData::License_GPL,
    "(c) 2002, Rory Vidal", 0, 0, "roryvidal@yahoo.fr");
  aboutData.addAuthor("Rory Vidal",0, "roryvidal@yahoo.fr");

	KCmdLineArgs::init( argc, argv, &aboutData );
  KCmdLineArgs::addCmdLineOptions( moptions ); // Add our own options.

	KCmdLineArgs *args = KCmdLineArgs::parsedArgs();

	bool fopt = args->isSet("f");

  QCString flistOptArg = args->getOption("f");
  if (!flistOptArg) flistOptArg = args->getOption("filelist");
	if (!flistOptArg) flistOptArg = "";

	bool delTestVolume = args->isSet("deleteTest") || args->isSet("d");

  Initializer *init = new Initializer();

	int r = 0;
	if ( args->count() || (flistOptArg!="") || delTestVolume) {//cerr<<"NOGUI"<<endl;
		init->testMode(args);
		return r;
	} else {//cerr<<"GUI"<<endl;
	  KApplication a;
		a.setMainWidget(InitForm::getInstance());
		init->run();
		r = a.exec();
	}

	return r;
}
