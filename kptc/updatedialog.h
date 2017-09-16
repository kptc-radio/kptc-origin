/***************************************************************************
                          updatedialog.h  -  description
                             -------------------
    begin                : Tue Mar 20 2001
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

#ifndef UPDATEDIALOG_H
#define UPDATEDIALOG_H

#include <qwidget.h>
#include <qdialog.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qprogressbar.h>
#include <qlineedit.h>
#include "update.h"


/**
  *@author Lars Schnake
  */

class UpdateDialog : public QDialog  {
   Q_OBJECT
public: 
	UpdateDialog(QWidget *parent=0, const char *name=0, WFlags f=0);
	~UpdateDialog();




private:

	QPushButton *okbutton;
	QPushButton *cancelbutton;
	QLineEdit *lineedit;
	QPushButton *choosebutton;
	QProgressBar *progressbar;
	QLabel *infolabel;
	Update *update;
	bool updaterunning;

protected:

 void closeEvent( QCloseEvent* );
	
private slots:
	
	void myfileDialog();
	void initUpdate();
	void updateMessage(QString);

public slots:
	
};

#endif
