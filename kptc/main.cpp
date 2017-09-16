/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : Wed Feb 14 2001
    copyright            : (C) 2001 by Lars Schnake
    email                : mail@lars-schnake.de
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
#include <kmenubar.h>
#include <kapp.h>
#include <kmainwindow.h>

#include "kptc.h"


static const char *description =
	I18N_NOOP("Kptc - User Interface for the SCS-PTC-II");


static KCmdLineOptions options[] =
{
  { 0, 0, 0 }
  // INSERT YOUR COMMANDLINE OPTIONS HERE
};

int main(int argc, char *argv[])
{

  KAboutData aboutData( "kptc", I18N_NOOP("Kptc"),
    VERSION, description, KAboutData::License_GPL,
    "(c) 2001, Lars Schnake");
  aboutData.addAuthor("Lars Schnake",0, "mail@lars-schnake.de");
  KCmdLineArgs::init( argc, argv, &aboutData );
  KCmdLineArgs::addCmdLineOptions( options ); // Add our own options.

  KApplication app;


 // KTMainWindow *top = new KTMainWindow();
 // top->resize( 800, 600 );

  Kptc *kptc = new Kptc();
  app.setMainWidget(kptc);
  kptc->show();

  QObject :: connect ( &app, SIGNAL (lastWindowClosed ()), &app, SLOT (quit()));

  return app.exec();
}
