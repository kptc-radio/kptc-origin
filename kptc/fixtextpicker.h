/***************************************************************************
                          fixtextpicker.h  -  description
                             -------------------
    begin                : Wed Mar 7 2001
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

#ifndef FIXTEXTPICKER_H
#define FIXTEXTPICKER_H

#include <qwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlabel.h>


/**Lineedits and button to setup a fixtext
  *@author Lars Schnake
  */

class FixTextPicker : public QWidget  {
   Q_OBJECT
public: 
	FixTextPicker( QWidget *parent=0, const char *name=0 );
	~FixTextPicker();

  QPushButton *choosebutton;
	QLineEdit *editlabel;
	QLineEdit *editpath;
	QLabel	*numlabel;
	
	

private:
	



	

};

#endif
