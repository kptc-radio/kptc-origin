/***************************************************************************
                          rttyspeedwidget.cpp  -  description
                             -------------------
    begin                : Mon Mar 12 2001
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

#include "rttyspeedwidget.h"
#include <qlayout.h>
#include <modem.h>

RTTYSpeedWidget::RTTYSpeedWidget(QWidget *parent, const char *name ) : QDialog(parent,name){


  setCaption(i18n("RTTY BAUDE RATE"));
  resize( 200,80 );
	setMinimumSize( 200, 80 );

	QVBoxLayout *vbox = new QVBoxLayout(this,0);
  slider = new QSlider( 20,300, 1, 45, QSlider::Horizontal, this, "slider");	
	lineedit = new QLineEdit( this, "lineedit");
	lineedit->setText("45");
	okbutton = new QPushButton( i18n("OK"), this );
  vbox->addWidget(slider);
  vbox->addWidget(lineedit);
  vbox->addWidget(okbutton);
	connect( okbutton, SIGNAL(clicked()), this, SLOT(change()));	
	connect( slider, SIGNAL(valueChanged(int)), this, SLOT(updateText(int)));
	connect(lineedit, SIGNAL(textChanged(const QString &)), this, SLOT(updateSlider(const QString &)));


}


void RTTYSpeedWidget::updateText(int i) {


	QString qi;
	qi.setNum(i);
	speed = i;
	lineedit->setText(qi);
}

void RTTYSpeedWidget::updateSlider(const QString &qs) {

	speed = qs.toUInt();

	slider->setValue(speed);
}


void RTTYSpeedWidget::change() {

	QString qs;
	qs.setNum(speed);
	qs.prepend("bau ");
	Modem::modem->send_esc();
	Modem::modem->writeLine(qs);
	accept();

}

RTTYSpeedWidget::~RTTYSpeedWidget(){
}
