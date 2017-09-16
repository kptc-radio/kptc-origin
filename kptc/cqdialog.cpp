/***************************************************************************
                          cqdialog.cpp  -  description
                             -------------------
    begin                : Mon Feb 26 2001
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

#include "cqdialog.h"
#include <klocale.h>
#include "configdata.h"
#include <kdebug.h>
#include "modem.h"
#include <qstring.h>
#include <qregexp.h>


CQDialog::CQDialog( QWidget *parent, const char* name , ModeCommander  *_modecommander) : QObject( parent, name ) {

	modecommander = _modecommander;

	TabDialog = new QTabDialog(0, "CQ-Dialog");
	TabDialog->setCaption( "CQ" );
	TabDialog->setOkButton( i18n("CALL C&Q"));
	//TabDialog->setApplyButton( i18n("CALL C&Q"));
	TabDialog->setDefaultButton( i18n("&Save"));
	TabDialog->setCancelButton( i18n("&Cancel"));

  CQText_Pactor = new QMultiLineEdit(TabDialog,"Pactor-text");
	CQText_Amtor = new QMultiLineEdit(TabDialog,"Amtor-text");
	CQText_RTTY = new QMultiLineEdit(TabDialog,"RTTY-text");
	CQText_PSK31 = new QMultiLineEdit(TabDialog,"PSK31-text");
	CQText_CW = new QMultiLineEdit(TabDialog,"CW-text");
	
	TabDialog->addTab( CQText_Pactor, "Pactor");
  TabDialog->addTab( CQText_Amtor, "Amtor");
	TabDialog->addTab( CQText_RTTY, "RTTY");
	TabDialog->addTab( CQText_PSK31, "PSK31");
	TabDialog->addTab( CQText_CW, "CW");

  connect ( TabDialog, SIGNAL ( applyButtonPressed () ), this, SLOT (startCall()) );
  connect ( TabDialog, SIGNAL ( defaultButtonPressed () ), this, SLOT (saveText()) );
	connect ( TabDialog, SIGNAL ( selected( const QString& )  ), this, SLOT (selectTab(const QString& )) );
}

void CQDialog::openDialog(  ) {

	
	CQText_Pactor->setText(configdata.getCQPactor());
	CQText_Amtor->setText(configdata.getCQAmtor());
	CQText_RTTY->setText(configdata.getCQRTTY());
	CQText_PSK31->setText(configdata.getCQPSK31());
	CQText_CW->setText(configdata.getCQCW());

	QString mod;
  if (modecommander != 0) mod = modecommander->currendmod();
	if (mod == "cmd:") TabDialog->showPage(CQText_Pactor);
  else if (mod == "AMTOR") TabDialog->showPage(CQText_Amtor);
	else if (mod == "AMTOR-MONITOR") TabDialog->showPage(CQText_Amtor);
  else if (mod == "RTTY") TabDialog->showPage(CQText_RTTY);
  else if (mod == "PSK31") TabDialog->showPage(CQText_PSK31);
  else if (mod == "CW") TabDialog->showPage(CQText_CW);

	TabDialog->show();

}


void CQDialog::saveText() {


  configdata.setCQPactor( CQText_Pactor->text());
	configdata.setCQAmtor( CQText_Amtor->text());
	configdata.setCQRTTY( CQText_RTTY->text());
	configdata.setCQPSK31( CQText_PSK31->text());
	configdata.setCQCW( CQText_CW->text());

}

void CQDialog::selectTab(const QString & Tab) {

	currenttab = Tab;	
	kdDebug() <<"CQDialog-currenttab: "<< Tab << endl;
	

}

void CQDialog::startCall() {

	kdDebug() <<"CQDialog:startCall" << endl;

	QString qs;
	if ( currenttab == "Pactor" ) {
		modecommander->changetoPactor();
		modecommander->Unproto();
		qs = CQText_Pactor->text();
		qs.replace( QRegExp("\n"), "\r" );
		qs = configdata.parseMacroText(qs);
		Modem::modem->writeLine(qs);
		modecommander->QRT();
	}
  else if ( currenttab == "Amtor" ) {
		modecommander->changetoAmtor();
		modecommander->FEC();
		qs = CQText_Amtor->text();
		qs.replace( QRegExp("\n"), "\r" );
		qs = configdata.parseMacroText(qs);
		Modem::modem->writeLine(qs);
		modecommander->QRT();
	}
	else if ( currenttab == "RTTY" ) {
		modecommander->changetoRTTY();
		modecommander->Changeover();
		qs = CQText_RTTY->text();
		qs.replace( QRegExp("\n"), "\r" );
		qs = configdata.parseMacroText(qs);
		Modem::modem->writeLine(qs);
		modecommander->QRT();
	}
  else if ( currenttab == "PSK31" ) {
		modecommander->changetoPSK31();
		modecommander->Changeover();
		qs = CQText_PSK31->text();
		qs.replace( QRegExp("\n"), "\r" );
		qs = configdata.parseMacroText(qs);
		Modem::modem->writeLine(qs);
		modecommander->QRT();
	}
	else if ( currenttab == "CW" ) {
		modecommander->changetoCW();
		qs = CQText_CW->text();
		qs.replace( QRegExp("\n"), "\r" );
		qs = configdata.parseMacroText(qs);
		sleep(1);
		Modem::modem->writeLine(qs);
	}
	


}


CQDialog::~CQDialog(){
}
