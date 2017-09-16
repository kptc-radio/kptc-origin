/***************************************************************************
                          CWSpeedWidget.h  -  description
                             -------------------
    begin                : Mon Mar 12 2001
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

#ifndef CWSPEEDWIDGET_H
#define CWSPEEDWIDGET_H

#include <qdialog.h>
#include <qpushbutton.h>
#include <qslider.h>
#include <qlineedit.h>
#include <klocale.h>

/**to change the cw tx speed
  *@author Lars Schnake
  */

class CWSpeedWidget : public QDialog  {
   Q_OBJECT
public: 
	CWSpeedWidget(QWidget *parent=0, const char *name=0);
	~CWSpeedWidget();
	QPushButton * okbutton;
	QSlider * slider;
	QLineEdit * lineedit;
private:
	int speed;

private slots:
	void updateText(int);
	void updateSlider(const QString &);
	void change();	
};

#endif
