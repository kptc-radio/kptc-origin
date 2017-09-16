/***************************************************************************
                          commanddialog.h  -  description
                             -------------------
    begin                : Wed Feb 14 2001
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


#ifndef COMMANDDIALOG_H
#define COMMANDDIALOG_H

#include <qdialog.h>
#include <qcombobox.h>

/**
  *@author Lars Schnake
  */

class CommandDialog : public QDialog  {
public: 
	CommandDialog(QWidget *parent=0, const char *name=0, WFlags f=0);
	~CommandDialog();

  QComboBox *combo;
private:
	
  void keyPressEvent(QKeyEvent *) ;

};
#endif
