/***************************************************************************
                          updatedialog.cpp  -  description
                             -------------------
    begin                : Tue Mar 20 2001
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

#include "updatedialog.h"
#include <qlayout.h>
#include <klocale.h>
//#include <kfiledialog.h>
#include <qfiledialog.h>




UpdateDialog::UpdateDialog(QWidget *parent, const char* name, WFlags f)
  : QDialog(parent, name,true, f) {


	updaterunning = false;
	update = new Update();

	setCaption("PTC Firmware Update");
	okbutton = new QPushButton(i18n("start Update"), this, "okbutton");
	cancelbutton = new QPushButton(i18n("Exit"),this, "chancelbutton");
	lineedit = new QLineEdit(this, "lineedit");
	choosebutton = new QPushButton(i18n("choose"),this, "choosebutton");
	progressbar = new QProgressBar(this, "progressbar");
	progressbar->setTotalSteps(100);
	infolabel = new QLabel(this, "infolabel");
	infolabel->setFrameStyle( QFrame::Panel | QFrame::Sunken );
	infolabel->setText("choose the new Firmware");

	QBoxLayout *toplayout = new QBoxLayout(this,QBoxLayout::TopToBottom, 10);
  QBoxLayout *buttonlayout = new QBoxLayout(QBoxLayout::LeftToRight);
  QBoxLayout *filepicklayout = new QBoxLayout(QBoxLayout::LeftToRight);	

	toplayout->addLayout(filepicklayout);
	toplayout->addWidget(infolabel);
	toplayout->addWidget(progressbar);
	toplayout->addLayout(buttonlayout);

	buttonlayout->addStretch();
	buttonlayout->addWidget(okbutton);
	buttonlayout->addWidget(cancelbutton);

	filepicklayout->addWidget(lineedit);
	filepicklayout->addWidget(choosebutton);


  QObject::connect (cancelbutton, SIGNAL (clicked()), this, SLOT ( reject()));
  QObject::connect (choosebutton, SIGNAL (clicked()), this, SLOT ( myfileDialog()));
  QObject::connect (okbutton, SIGNAL (clicked()), this, SLOT ( initUpdate()));
	QObject::connect (update, SIGNAL (progress(int)), progressbar, SLOT ( setProgress(int)));
	QObject::connect (update, SIGNAL (message(QString)), this, SLOT ( updateMessage(QString)));	

}

void UpdateDialog::myfileDialog() {

	QString filename = QFileDialog::getOpenFileName( QString::null,
								 "*.pt*\n*.pt2\n*.pte\n*",
								 this, i18n("choose new Firmware:") );
	if (filename == NULL)
  return;
	lineedit->setText(filename);	
}

void UpdateDialog::initUpdate() {

	updaterunning = true;

  QObject::disconnect (cancelbutton, SIGNAL (clicked()), this, SLOT ( reject()));
  QObject::disconnect (choosebutton, SIGNAL (clicked()), this, SLOT ( fileDialog()));
  QObject::disconnect (okbutton, SIGNAL (clicked()), this, SLOT ( initUpdate()));

	update->runUpdate(lineedit->text());

  QObject::connect (cancelbutton, SIGNAL (clicked()), this, SLOT ( reject()));
  QObject::connect (choosebutton, SIGNAL (clicked()), this, SLOT ( fileDialog()));
  QObject::connect (okbutton, SIGNAL (clicked()), this, SLOT ( initUpdate()));

updaterunning = false;
}

void UpdateDialog::updateMessage(QString text) {

	infolabel->setText(text);
}


void UpdateDialog::closeEvent( QCloseEvent* ce )
{

	if (!updaterunning) { ce->accept(); return; }
	else { ce->ignore();}

}

UpdateDialog::~UpdateDialog(){
}
