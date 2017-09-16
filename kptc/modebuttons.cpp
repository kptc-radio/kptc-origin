/***************************************************************************
                          modebuttons.cpp  -  description
                             -------------------
    begin                : Wed Mar 7 2001
    copyright            : (C) 2001 by Lars Schnake
    email                : lschnak@suse.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "modebuttons.h"
#include "qlayout.h"



ModeButtons::ModeButtons(QWidget *parent, const char *name ) : QObject(parent,name) {

	
	buttongroup = new QButtonGroup(parent, "buttongroup");

	pactorButton = new QPushButton("Pactor" , parent );
  amtorButton = new QPushButton("Amtor", parent );
	rttyButton = new QPushButton( "RTTY", parent );
	psk31Button = new QPushButton( "PSK31", parent );
	cwButton = new QPushButton( "CW", parent );


	buttongroup->insert( pactorButton , 1 );
	buttongroup->insert( amtorButton ,2 );
	buttongroup->insert( rttyButton ,3 );
	buttongroup->insert( psk31Button ,4 );
	buttongroup->insert( cwButton ,5 );

	buttongroup->setExclusive(true);

	pactorButton->setToggleButton(true);
  amtorButton->setToggleButton(true);
	rttyButton->setToggleButton(true);
	psk31Button->setToggleButton(true);
	cwButton->setToggleButton(true);
	


}
ModeButtons::~ModeButtons(){
}
