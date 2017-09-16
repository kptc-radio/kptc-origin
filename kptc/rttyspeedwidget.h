/***************************************************************************
                          rttyspeedwidget.h  -  description
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

#ifndef RTTYSPEEDWIDGET_H
#define RTTYSPEEDWIDGET_H

#include <qdialog.h>
#include <qpushbutton.h>
#include <qslider.h>
#include <qlineedit.h>
#include <klocale.h>

/**change baude rate for RTTY
  *@author Lars Schnake
  */

class RTTYSpeedWidget : public QDialog  {
   Q_OBJECT
public: 
	RTTYSpeedWidget(QWidget *parent=0, const char *name=0);
	~RTTYSpeedWidget();

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
