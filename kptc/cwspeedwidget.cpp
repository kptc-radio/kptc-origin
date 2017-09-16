/***************************************************************************
                          CWSpeedWidget.cpp  -  description
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

#include "cwspeedwidget.h"
#include <qlayout.h>
#include <modem.h>

CWSpeedWidget::CWSpeedWidget(QWidget *parent, const char *name ) : QDialog(parent,name) {



  setCaption(i18n("cw tx speed"));
  resize( 200,80 );
	setMinimumSize( 200, 80 );

	QVBoxLayout *vbox = new QVBoxLayout(this,0);
  slider = new QSlider( 40,1200, 1, 160, QSlider::Horizontal, this, "slider");	
	lineedit = new QLineEdit( this, "lineedit");
	lineedit->setText("160");
	okbutton = new QPushButton( i18n("OK"), this );
  vbox->addWidget(slider);
  vbox->addWidget(lineedit);
  vbox->addWidget(okbutton);
	connect( okbutton, SIGNAL(clicked()), this, SLOT(change()));	
	connect( slider, SIGNAL(valueChanged(int)), this, SLOT(updateText(int)));
	connect(lineedit, SIGNAL(textChanged(const QString &)), this, SLOT(updateSlider(const QString &)));


}

void CWSpeedWidget::updateText(int i) {


	QString qi;
	qi.setNum(i);
	speed = i;
	lineedit->setText(qi);
}

void CWSpeedWidget::updateSlider(const QString &qs) {

	speed = qs.toUInt();

	slider->setValue(speed);
}


void CWSpeedWidget::change() {

	QString qs;
	qs.setNum(speed);
	qs.prepend("cws ");
	Modem::modem->send_esc();
	Modem::modem->writeLine(qs);
	accept();

}

CWSpeedWidget::~CWSpeedWidget(){
}
