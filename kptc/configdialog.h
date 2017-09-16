/***************************************************************************
                          configdialog.h  -  description
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

#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <qdialog.h>
#include <qwidgetstack.h>
#include <qlistbox.h>
#include <qradiobutton.h>
#include <qcombobox.h>
#include <qmultilinedit.h>
#include <qcheckbox.h>



#include <qpixmap.h>
#include <qlayout.h>
#include <qpushbutton.h>
#include <qbuttongroup.h>
#include <qvbox.h>
#include <qhbox.h>
#include <qlabel.h>
#include <qlistbox.h>
#include <qlineedit.h>
#include <klocale.h>
#include <kdebug.h>
#include <qlayout.h>
#include <qlist.h>
#include <qfiledialog.h>

#include "configdata.h"
#include <configmachine.h>
#include "fixtextpicker.h"



/**
  *@author Lars Schnake
  */

class ConfigDialog : public QDialog  {
Q_OBJECT
public: 
	ConfigDialog(QWidget *parent=0, const char *name=0, WFlags f=0);
	~ConfigDialog();


private:
  QWidgetStack* widgetstack;

  QRadioButton* port_RadioButton1;
  QRadioButton* port_RadioButton2;
	QRadioButton* port_RadioButton3;
	QRadioButton* port_RadioButton4;
	QRadioButton* port_RadioButton5;
	QLineEdit* port_LineEdit_dev;
	QComboBox* port_ComboBox_speed;
  QLineEdit* personal_LineEdit_call;
  QLineEdit* personal_LineEdit_selcall;
  QLineEdit* personal_LineEdit_name;
	QLineEdit* personal_LineEdit_qth ;
	QMultiLineEdit* personal_MultiLineEdit_ctext;
	QCheckBox* personal_CheckBox_cmsg ;
	QMultiLineEdit* logout_MultiLineEdit_ctext;
	QCheckBox* logout_CheckBox_cmsg ;
  QList <FixTextPicker> list;
	QList <QObject> oblist;
	QLineEdit* logout_LineEdit_path;
	QCheckBox* logout_CheckBox_script;
	QPushButton* logout_PushButton_choosescript;
	QLineEdit* login_LineEdit_path;
	QCheckBox* login_CheckBox_script;
	QPushButton* login_PushButton_choosescript;


private slots:
  void resetwidgets();
  void selectwidget(QListBoxItem *) ;
  void writeconfig();
	void chooseFile();
	void chooseLogoutFile();
	void chooseLoginFile();
	void update_widgets();
};


#endif
