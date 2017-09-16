/***************************************************************************
                          cqdialog.h  -  description
                             -------------------
    begin                : Mon Feb 26 2001
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

#ifndef CQDIALOG_H
#define CQDIALOG_H

#include <qobject.h>
#include <qtabdialog.h>
#include <qmultilineedit.h>
#include "modecommander.h"

/**
  *@author Lars Schnake
  */

class CQDialog : public QObject  {
Q_OBJECT
public: 
	CQDialog(QWidget *parent=0, const char *name=0, ModeCommander *modecommander = 0);
	~CQDialog();

	QTabDialog *TabDialog;	

private:

	QMultiLineEdit *CQText_Pactor ;
	QMultiLineEdit *CQText_Amtor;
	QMultiLineEdit *CQText_RTTY ;
	QMultiLineEdit *CQText_PSK31 ;
	QMultiLineEdit *CQText_CW ;
  ModeCommander *modecommander;
	QString currenttab;
	
public slots:
	void openDialog( );
	void saveText();
  void startCall();
	void selectTab(const QString&);
	
};

#endif
