/***************************************************************************
                          mylineedit.h  -  description
                             -------------------
    begin                : Tue Mar 13 2001
    copyright            : (C) 2001 by lschnak@suse.de
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

#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <qwidget.h>
#include <qlineedit.h>
#include <qlist.h>

/**text imput widget
reimplementation of QLineEdit
  *@author lschnak@suse.de
  */

class MyLineEdit : public QLineEdit  {
   Q_OBJECT
public: 
	MyLineEdit(QWidget *parent=0, const char *name=0);
	~MyLineEdit();

  void keyPressEvent (QKeyEvent*);
  void notify(const QObject *, const char *);
  void insertChar(unsigned char);
  void myinsert( QString qs );
	void setPrompt( QString );


private:

	void focusInEvent( QFocusEvent * );
	void focusOutEvent( QFocusEvent * );

	bool commandmode;
	int cursorpos;
	int promptlength;
	QString qsprompt;

	QList <QString> commandlist;

signals:

  void sendit(QString);
  void sendit(unsigned char);
	void echoCommand(QString);

};

#endif
