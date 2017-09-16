/***************************************************************************
                          statusinfo.cpp  -  description
                             -------------------
    begin                : Mon Feb 19 2001
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


#include "statusinfo.h"
#include <qlayout.h>
#include <qlabel.h>
#include <qtooltip.h>
#include <klocale.h>
#include <qwhatsthis.h>

StatusInfo::StatusInfo(QWidget *parent, const char *name ) : QWidget(parent,name) {

	this->setFont(QFont("courier",10,QFont::Normal));
  setMinimumSize( 400, 20 );


  led = new KLed( KLed::red, this, "SEND_LED");
	//led->setGeometry ( 2, 2, 16, 16);
	led->setFixedSize(18,18);
	led->off();
	QToolTip::add(led, i18n("SEND-LED"));
	QWhatsThis::add(led, i18n("The Send LED show the direction\nof the information flow.\nOn means: sending text\noff means: receiving text"));

  send = new QLabel(this);
	//send->setGeometry( 20, 0, 30, 20 );
	send->setFixedSize(30,20);
	send->setText("SEND");

  prompt = new QLabel(this);
	//prompt->setGeometry( 50, 0, 80, 20 );
	prompt->setFixedSize(80,20);
  prompt->setFrameStyle(QFrame::Sunken | QFrame::Box);
	QToolTip::add(prompt, i18n("prompt"));
	QWhatsThis::add(prompt, i18n("Here is the current prompt showen."));

	mode = new QLabel(this);
	//mode->setGeometry( 130, 0, 80, 20 );
	mode->setFixedSize(80,20);
	mode->setFrameStyle(QFrame::Sunken | QFrame::Box);
	mode->setText("NO RESPONSE !");
	QToolTip::add(mode, i18n("mode"));
	QWhatsThis::add(mode, i18n("Here are information about\nthe current mode showen."));

	status = new QLabel(this);
	//status->setGeometry( 210, 0, 80, 20 );
	status->setFixedSize(80,20);
	status->setFrameStyle(QFrame::Sunken | QFrame::Box);
	QToolTip::add(status, i18n("status"));
	QWhatsThis::add(status, i18n("Here are some status information showen."));

	statusmessage = new QLabel(this);
	statusmessage->setMaximumHeight(20);
	statusmessage->setFrameStyle(QFrame::Sunken | QFrame::Box);
	QToolTip::add(statusmessage, i18n("connect message"));
	QWhatsThis::add(statusmessage, i18n("Here is the current connect message showen."));

  call = new QLabel(this);
	call->setFrameStyle(QFrame::Sunken | QFrame::Box);
	QToolTip::add(call, i18n("call/selcall"));
	QWhatsThis::add(call, i18n("This is your call and your Amtor Selcall\nhow you have entered it in the config dialog"));
	QHBoxLayout *layout = new QHBoxLayout (this);

	layout->addWidget (led);
	layout->addWidget (send);
	layout->addWidget (prompt);
	layout->addWidget (mode);
	layout->addWidget (status);	
  layout->addWidget (statusmessage,1);
	//layout->addStretch(1);
	layout->addWidget (call);

}
StatusInfo::~StatusInfo(){
}
