/***************************************************************************
                          fixtextpicker.cpp  -  description
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

#include "fixtextpicker.h"
#include <qlayout.h>
#include <klocale.h>
#include <qwidget.h>



FixTextPicker::FixTextPicker(QWidget *parent , const char *name ) : QWidget(parent,name) {

	choosebutton = new QPushButton( i18n("choose..."), this, "button" );
  editpath = new QLineEdit(this);
	editlabel = new QLineEdit(this);
	numlabel = new QLabel("number", this);
	
  QHBoxLayout *layout = new QHBoxLayout( this, 4 );
  layout->addWidget( numlabel );
  layout->addWidget( editlabel );
  layout->addWidget( editpath );
  layout->addWidget( choosebutton );

}
FixTextPicker::~FixTextPicker(){
}
