/***************************************************************************
                          commanddialog.cpp  -  description
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


#include "commanddialog.h"
#include "modem.h"
#include <kdebug.h>
#include <klocale.h>

CommandDialog::CommandDialog(QWidget *parent, const char *name, WFlags f) : QDialog (parent, name, false, f){


	setCaption(i18n("command"));
  resize( 180,50 );
	setMinimumSize( 180, 50 );
	setMaximumSize( 180, 50 );

  combo = new QComboBox (true, this, "combobox");
  combo->setGeometry( 15,10, 150, 30 );
	combo->setMinimumSize( 0, 0 );
	combo->setMaximumSize( 32767, 32767 );
	combo->setFocusPolicy( QWidget::StrongFocus );
	combo->setBackgroundMode( QWidget::PaletteBackground );
//	combo->setFontPropagation( QWidget::AllChildren );
//	combo->setPalettePropagation( QWidget::AllChildren );
	combo->setAutoResize( FALSE );
	combo->setMaxCount( 20 );
	combo->setAutoCompletion( true );
  combo->setInsertionPolicy(QComboBox::AtTop);


	

}


void CommandDialog::keyPressEvent(QKeyEvent *ke) {



	ke->accept();
	switch(ke->key()) {
  case Key_Enter:   ;
	case Key_Return:
	//////////////////////////////////////////////	
	// send the command to the ptc:

	
  kdDebug() << "CommandDialog::keyEvent" <<combo->currentText()<< endl;
  Modem::modem->send_esc();
	Modem::modem->writeLine(combo->currentText());
  combo->clearEdit();
  break;

	default: ke->ignore();
	}

		
}

CommandDialog::~CommandDialog(){
}
