/***************************************************************************
                          kptc.h  -  description
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


#ifndef KPTC_H
#define KPTC_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <kapp.h>
#include <qwidget.h>
// #include <ktmainwindow.h>
#include <kmainwindow.h>
#include <kapp.h>
#include <keditcl.h>
#include <mytermout.h>
//#include <mymultilineedit.h>
#include "mylineedit.h"
#include "commanddialog.h"
#include "modecommander.h"
#include <kled.h>
#include <qstatusbar.h>
#include "statusinfo.h"
#include "cqdialog.h"
#include "modebuttons.h"


#include "modem.h"
#include <qlineedit.h>
#include <qcombobox.h>
#include <qframe.h>

#include <qlabel.h>
#include <qlayout.h>
#include <qhbox.h>
#include <qfont.h>
#include <kapp.h>
#include <kmenubar.h>
#include <klocale.h>
#include <kmessagebox.h>
#include <qtextview.h>
#include <keditcl.h>

#include <qapplication.h>
#include <kdebug.h>

#include <configdialog.h>
#include <configdata.h>
#include <configmachine.h>
#include <qdialog.h>
#include <qmessagebox.h>
#include "kiconloader.h"
#include "modecommander.h"
#include <ktoolbar.h>
#include <ktoolbarradiogroup.h>
#include <qfile.h>
#include <kglobal.h>
#include <cwspeedwidget.h>
#include <rttyspeedwidget.h>


class Kptc : public KMainWindow
{
  Q_OBJECT
  public:
    /** construtor */
    Kptc(QWidget* parent=0, const char *name=0);



    /** destructor */
    ~Kptc();

		

  private:
		QPopupMenu *fixmenu;
		QStatusBar *mystatusBar;
		void useconfigmachine();
		KToolBar *modetoolbar;
		KToolBar *lefttoolbar;
    MyTermout *termoutput;
    MyLineEdit *textedit;
		CQDialog *cqdialog;
		ModeButtons *modebuttons;
		ConfigMachine * configmachine;
		
		
		void parsePrompt(const char);
		void parseStatus(const char);
    int currentterm;
		// meaning of currentterm :
		// 1: (ctrl-A) : prescripe/message window
		// 2: (ctrl-B) : rec window
		// 3: (ctrl-C) : delayed echo
    bool bPromptInfoFollows;
		bool bStatusByteFollows;
		
    CommandDialog commanddialog;
		ModeCommander *modecommander;
		StatusInfo *statusinfo;
		CWSpeedWidget  *cwspeedwidget;
		RTTYSpeedWidget * rttyspeedwidget;
    int parsePromptText ;
		QString prompt;
		bool queryClose ();
		QString statusmessage;


  public slots:
    void parseModemOut(unsigned char);
    void sendline(QString);
    void sendchar(unsigned char);
    void openconfigdialog();
		void openCommandDialog();
		void showPactor();
		void showAmtor();
		void showRTTY();
		void showPSK31();
		void showCW();
		
		void initchangeover();
		void initQRT();

		void updateStatusBar();

		void clearTrafficWindow();
		void clearEditWindow();
		void sendFixText ( int );
		void shutdown();
		void showcwspeeddialog();
		void showrttyspeeddialog();
		void echoText( QString );
		void openUpdateDialog();
		void fileQuit();

};

#endif
