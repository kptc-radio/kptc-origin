/***************************************************************************
                          kptc.cpp  -  description
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


#include "kptc.h"
#include "cwspeedwidget.h"
#include "updatedialog.h"
#include <kmessagebox.h>
#include <kstatusbar.h>



Kptc::Kptc(QWidget *parent, const char *name) : KMainWindow()
{

    setCaption( i18n("Kptc - the PTC-II for penguins "));
		// connect( kapp, SIGNAL(shutDown()), this, SLOT(shutdown()) );

		this->resize( 650, 450 );


    currentterm=1;
		bPromptInfoFollows = false;
		
		modecommander = new ModeCommander(this, "modecommander");
		cqdialog = new CQDialog(this, "cqdialogQObject",  modecommander);

		////////////////////////////////////////////////////////////////////////////
    // Popup Menu:

    QPopupMenu *filemenu = new QPopupMenu;
		filemenu->insertSeparator();
    filemenu->insertItem( SmallIcon( "exit" ),i18n( "&Quit" ), this, SLOT(fileQuit()) );

    QPopupMenu *actionmenu = new QPopupMenu ;


		actionmenu->insertItem (SmallIcon( "reload" ),i18n( "Change&over"), this, SLOT(initchangeover()), CTRL + Key_Y );
	  actionmenu->insertItem (SmallIcon( "exit" ),i18n( "QR&T"), this, SLOT(initQRT()), CTRL + Key_D );
	  actionmenu->insertItem (SmallIcon( "stop" ),i18n( "&Stand by"), modecommander, SLOT(Standby()), CTRL + Key_S );
	  actionmenu->insertItem (SmallIcon( "konqueror" ),i18n( "&CQ..."), cqdialog, SLOT(openDialog()), CTRL + Key_Q );
		actionmenu->insertSeparator();
    actionmenu->insertItem (i18n( "&Command..."), this, SLOT(openCommandDialog()), SHIFT + Key_Escape );
		

		QPopupMenu *optionmenu = new QPopupMenu;
		optionmenu->insertItem( SmallIcon( "configure" ),i18n( "&Config..." ), this, SLOT(openconfigdialog()) );
		optionmenu->insertItem(SmallIcon( "memory" ), i18n("Firmware Update..."), this, SLOT(openUpdateDialog()));

    // window menu
    //QPopupMenu *windowmenu = new QPopupMenu ;
		//QPopupMenu *clearwindow = new QPopupMenu ;
		//clearwindow->insertItem (i18n("&traffic window"), this, SLOT(clearTrafficWindow()));
		//clearwindow->insertItem (i18n("&edit window"), this, SLOT(clearEditWindow()));
		//windowmenu->insertItem (i18n("&clear window"), clearwindow );

    QString about =
            i18n("Kptc 0.2\n"
                 "user interface for the SCS-PTC-II\n\n"
                 "(C) 2001 Lars Schnake\nmail@lars-schnake.de\n"
                 );

    KPopupMenu *helpmenu = helpMenu( about );

		fixmenu = new QPopupMenu ;
		
		QString s;
    for ( int i = 1; i <= 8; i++ ) {
      s.setNum(i);
     	fixmenu->insertItem ( "&" + s + ". " + configdata.getFixLabel( s ), this, SLOT (sendFixText( int )), CTRL + SHIFT + (Key_F1 +(i)) , i);
			fixmenu->setItemParameter ( i, i);

		}

    KMenuBar *menu = new KMenuBar( this );

    menu->insertItem( i18n( "&File" ), filemenu );
    menu->insertItem( i18n( "&Actions" ), actionmenu );
		menu->insertItem( i18n( "Fi&xtext" ), fixmenu );
		//menu->insertItem( i18n( "&Windows" ), windowmenu );	
		menu->insertItem(i18n("&Options"), optionmenu );	
    menu->insertSeparator();
    // menu->insertItem( i18n( "&Help" ), helpmenu );



		

		/////////////////////////////////////////////////////////////////////////////
		// Toolbar for changing the mods:

		modetoolbar = new KToolBar(this, "modetoolbar");
//    modetoolbar->setIconIconTextBottomText(KToolBar::IconTextBottom);
		modetoolbar->setBarPos(KToolBar::Top);
    modebuttons = new ModeButtons(modetoolbar);
		
		
		modetoolbar->insertLineSeparator();
    modetoolbar->insertWidget (1, modebuttons->pactorButton->width(), modebuttons->pactorButton) ;
		modetoolbar->insertLineSeparator();
		modetoolbar->insertWidget (2, modebuttons->amtorButton->width(), modebuttons->amtorButton) ;
		modetoolbar->insertLineSeparator();
		modetoolbar->insertWidget (3, modebuttons->rttyButton->width(), modebuttons->rttyButton) ;
		modetoolbar->insertLineSeparator();
		modetoolbar->insertWidget (4, modebuttons->psk31Button->width(), modebuttons->psk31Button) ;
		modetoolbar->insertLineSeparator();
		modetoolbar->insertWidget (5, modebuttons->cwButton->width(), modebuttons->cwButton) ;
		modetoolbar->insertLineSeparator();



		
	
		/*
		modetoolbar->insertButton("mini-pactor.xpm",1,SIGNAL(clicked()),modecommander, SLOT(changetoPactor()), true," | Pactor | ");
    modetoolbar->insertButton("mini-pactor.xpm",2,SIGNAL(clicked()),modecommander, SLOT(changetoAmtor()), true, " | Amtor |");
    modetoolbar->insertButton("mini-pactor.xpm",3,SIGNAL(clicked()),modecommander, SLOT(changetoRTTY()), true, " | RTTY | ");
		modetoolbar->insertButton("mini-pactor.xpm",4,SIGNAL(clicked()),modecommander, SLOT(changetoPSK31()), true, " | PSK31 | ");
    modetoolbar->insertButton("mini-pactor.xpm",5,SIGNAL(clicked()),modecommander, SLOT(changetoCW()), true, " | CW | ");

		
		KToolBarRadioGroup *moderadiogroup = new KToolBarRadioGroup(modetoolbar,"modradiogroup");
    modetoolbar->setToggle(1);
		modetoolbar->setToggle(2);
		modetoolbar->setToggle(3);
		modetoolbar->setToggle(4);
		modetoolbar->setToggle(5);		
		moderadiogroup->addButton(1);
    moderadiogroup->addButton(2);
		moderadiogroup->addButton(3);
		moderadiogroup->addButton(4);
		moderadiogroup->addButton(5);
		*/


   	
    ///////////////////////////////////////////////////////////////////////////////
		// toolbar on the left side

		lefttoolbar = new KToolBar(this, "lefttoolbar");
		lefttoolbar->setIconText(KToolBar::IconTextBottom);
		lefttoolbar->insertLineSeparator();
		lefttoolbar->setBarPos(KToolBar::Left);

		
		
		///////////////////////////////////////////////////////////////////////////////
		// statusbar

	 /* sendled = new KLed( statusBar() );
		sendled->setColor(KLed::red);
		sendled->off();  */

		//statusBar()->setInsertOrder( KStatusBar::RightToLeft );
		//statusBar()->insertWidget(sendled, sendled->width(),1);
		//statusBar()->addWidget(sendled, sendled->width(),1);
    
    //statusinfo = new StatusInfo(statusBar());
    statusinfo = new StatusInfo((QWidget *) statusBar());
		statusBar()->addWidget(statusinfo, statusinfo->width(), 1);
    statusinfo->show();
		
		
		//////////////////////////////////////////////////////////////////////////////
		// main window elements

    QSplitter *splitter = new QSplitter( QSplitter::Vertical, this );
    splitter->setOpaqueResize( TRUE );
    setCentralWidget( splitter );

		// modebuttons in splitter window instead of modetoolbar ?! :
    // modebuttons = new ModeButtons(splitter);

    termoutput = new MyTermout(splitter);
		termoutput->setFont(QFont("courier",12,QFont::Normal));
    textedit = new MyLineEdit(splitter);
    textedit->notify(this, SLOT(sendchar(unsigned char)));

		

    splitter->show();

		textedit->setFocus();
		connect( textedit, SIGNAL(echoCommand(QString)), this, SLOT( echoText(QString)));
		connect( textedit, SIGNAL(sendit(QString)), this, SLOT(sendline(QString)));



    //////////////////////////////////////////////////////////////////


		cwspeedwidget = new CWSpeedWidget( 0 );
    rttyspeedwidget = new RTTYSpeedWidget( 0 );
		connect(modebuttons->pactorButton, SIGNAL(clicked()), modecommander,SLOT(changetoPactor()));
		connect(modebuttons->amtorButton, SIGNAL(clicked()), modecommander,SLOT(changetoAmtor()));
		connect(modebuttons->rttyButton, SIGNAL(clicked()), modecommander,SLOT(changetoRTTY()));
		connect(modebuttons->psk31Button, SIGNAL(clicked()), modecommander,SLOT(changetoPSK31()));
		connect(modebuttons->cwButton, SIGNAL(clicked()), modecommander,SLOT(changetoCW()));


		configmachine = new ConfigMachine(this);

		// Modem :
    (void)new Modem;
		bool bModemOk = false;

		setAutoSaveSettings();

    if ( configdata.firststart() ) {

			KMessageBox::information( this, i18n("Thank you for installing Kptc !\n"
				"This is a Ham Radio software for the SCS-PTC-II\nRemember: This sofware is still beta !\n\n"
				"Connect the PTC to your computer\nand switch it on now.\nThen let´s continue with some configurations.\n"
				"Have Fun ! 73 de Lars DL3YFC"), i18n("Welcome to Kptc !"));	

  		ConfigDialog configdialog ;
    	if (configdialog.exec()== QDialog::Accepted) {
    		bModemOk = Modem::modem->opentty() ;
    		Modem::modem->notify(this, SLOT(parseModemOut(unsigned char)));			
    		configdata.setfirststart( false );
    		useconfigmachine();
				lefttoolbar->setBarPos(KToolBar::Left);
  		}
		}
    else {
    bModemOk = Modem::modem->opentty() ;
		Modem::modem->notify(this, SLOT(parseModemOut(unsigned char)));	
	  useconfigmachine();
		}		

	
		configmachine->login();
    kdDebug() << Modem::modem->modemMessage()<< endl;
  	if ( ! bModemOk) KMessageBox::sorry( this,
		i18n("Cannot open modem device !"), "Kptc" );	






}


void Kptc ::parseModemOut(unsigned char c) {


	if ((int) c == 6)  kdDebug() << "Packet-STATUSINFO"<< endl;

  if (bStatusByteFollows) {
		bStatusByteFollows = false;
		parseStatus( c );
	}
	else if ((int) c == 30 ) bStatusByteFollows = true;

	else if (c == 4)   bPromptInfoFollows = true; // command prompt info follows

  else if (bPromptInfoFollows) {

					parsePrompt( c );
          bPromptInfoFollows = false;
          parsePromptText = 20;
	}
	else if (parsePromptText > 0) {
					if ((int)c == 1) { parsePromptText = 0; currentterm = 1; textedit->setPrompt(prompt.stripWhiteSpace()); prompt="";} // prompt end
					else
					{
						parsePromptText--;
						if ( (c != '\n') || (c != '\r') ) prompt.append(c);
					}

	}

	else if ((int)c == 3 ) { currentterm = 3;   }    // delayed echo
	else if ((int)c == 2 ) { currentterm = 2;   }    // rx
  else if ((int)c == 1 ) { currentterm = 1;   }    // prompt , errors , ...
	else if ((int)c == 7 ) ; // klingeling :-) , changeover bell, do some ring ring here !?
  else
  {
      if ((currentterm == 2) || (currentterm == 3))
      {
				if (currentterm == 3) termoutput->setNewLineColor(red);   // echo
				else termoutput->setNewLineColor(darkGreen);              // rx

           termoutput->appendChar(c);
           show();
      }
      else if (currentterm == 1) {
			
				termoutput->setNewLineColor(black);
				termoutput->appendChar(c);
				if (c == '\n' || c == '\r' ) {
				
					if (statusmessage.contains("*** ") == 1 ) {

						if (statusmessage.contains("CONNECTED") || statusmessage.contains("CALLING")) {		
  						// statusmessage.replace( QRegExp("[*]"), "" );
  						statusmessage.stripWhiteSpace();
  						statusinfo->statusmessage->setText(statusmessage);
						}
						else if ( statusmessage.contains("STBY"))  statusinfo->statusmessage->setText("");
						
					}

					statusmessage = ""; 					

				}
				else statusmessage.append(c);
			

			}


  }



}



void Kptc :: sendline(QString qs) {


  Modem::modem->writeLine( (const char*)qs );
 /*
  termoutput->appendString(qs);
  termoutput->appendString("\n");
  show();   */
}


void Kptc :: sendchar(unsigned char c){

  if (Modem::modem->writeChar(c));
}


void Kptc :: echoText(QString qtext) {


	termoutput->setNewLineColor(darkBlue);
	termoutput->appendString(qtext);

}

void Kptc :: openconfigdialog(){

  ConfigDialog configdialog ;
  if (configdialog.exec() == QDialog::Accepted) useconfigmachine();

}

void Kptc :: useconfigmachine(){
	

  configmachine->doconfig();
	statusinfo->call->setText(configdata.getCall() + " (" + configdata.getSelCall() + ") ");
	updateStatusBar();
	
	QString s;
	fixmenu->clear();
    for ( int i = 1; i <= 8; i++ ) {
      s.setNum(i);
     	fixmenu->insertItem ( "&" + s + ". " + configdata.getFixLabel( s ), this, SLOT (sendFixText( int )), SHIFT + (Key_F1 +(i)) , i);
			fixmenu->setItemParameter ( i, i);

		}

}


void Kptc :: openCommandDialog() {

		commanddialog.close();
		commanddialog.show();
		commanddialog.combo->setFocus();

}

void Kptc :: clearTrafficWindow() {

	termoutput->repaint(false);

}

void Kptc :: clearEditWindow() {

	textedit->clear();

}

void Kptc :: showPactor() {

  modebuttons->buttongroup->setButton(1);
  lefttoolbar->clear();
	lefttoolbar->setIconText(KToolBar::IconTextBottom);
	lefttoolbar->insertButton(BarIcon("stop"),1,SIGNAL(clicked()),modecommander, SLOT( Standby()), true, i18n("Stand by"));
  lefttoolbar->insertButton(BarIcon("exit"),2,SIGNAL(clicked()),this, SLOT( initQRT()), true, i18n("QRT"));
	lefttoolbar->insertButton(BarIcon("reload"),3,SIGNAL(clicked()),this, SLOT( initchangeover()), true, i18n("changeover"));
	lefttoolbar->insertButton(BarIcon("konqueror"),5,SIGNAL(clicked()),cqdialog, SLOT( openDialog()), true, i18n(" CQ "));
	lefttoolbar->insertButton(BarIcon("idea"),4,SIGNAL(clicked()),modecommander, SLOT( Unproto()), true, i18n("Unproto TX"));

	lefttoolbar->insertButton(BarIcon("remote"),6,SIGNAL(clicked()),modecommander, SLOT( Listen()), true, i18n("Listen"));
  lefttoolbar->setToggle(6);
	lefttoolbar->setButton(6,modecommander->isListen());
}

void Kptc :: showAmtor() {

  modebuttons->buttongroup->setButton(2);
  lefttoolbar->clear();
  lefttoolbar->insertButton(BarIcon("stop"),1,SIGNAL(clicked()),modecommander, SLOT( Standby()), true, i18n("Stand by"));
  lefttoolbar->insertButton(BarIcon("exit"),1,SIGNAL(clicked()),this, SLOT( initQRT()), true, i18n("QRT"));
	lefttoolbar->insertButton(BarIcon("reload"),1,SIGNAL(clicked()),this, SLOT( initchangeover()), true, i18n("changeover"));
	
	lefttoolbar->insertButton(BarIcon("konqueror"),5,SIGNAL(clicked()),cqdialog, SLOT( openDialog()), true, i18n(" CQ "));
	lefttoolbar->insertButton(BarIcon("idea"),1,SIGNAL(clicked()),modecommander, SLOT( FEC()), true, i18n("FEC TX"));
	lefttoolbar->insertButton(BarIcon("gnome-term"),3,SIGNAL(clicked()),modecommander, SLOT( Monitor()), true, i18n("Monitor"));
}

void Kptc :: showRTTY() {

	// modetoolbar->toggleButton(3);
  modebuttons->buttongroup->setButton(3);

  lefttoolbar->clear();
	lefttoolbar->insertButton(BarIcon("stop"),1,SIGNAL(clicked()),modecommander, SLOT( Standby()), true, i18n("Stand by"));
	lefttoolbar->insertButton(BarIcon("exit"),1,SIGNAL(clicked()),this, SLOT( initQRT()), true, i18n("QRT"));
	lefttoolbar->insertButton(BarIcon("reload"),1,SIGNAL(clicked()),this, SLOT( initchangeover()), true, i18n("changeover"));
	lefttoolbar->insertButton(BarIcon("gear"),4,SIGNAL(clicked()),this, SLOT(showrttyspeeddialog()), true, i18n("baudrate"));
	lefttoolbar->insertButton(BarIcon("konqueror"),5,SIGNAL(clicked()),cqdialog, SLOT( openDialog()), true, i18n(" CQ "));
}

void Kptc :: showPSK31() {

	//modetoolbar->toggleButton(4);
  modebuttons->buttongroup->setButton(4);


  lefttoolbar->clear();
	lefttoolbar->insertButton(BarIcon("stop"),1,SIGNAL(clicked()),modecommander, SLOT( Standby()), true, i18n("Stand by"));
	lefttoolbar->insertButton(BarIcon("exit"),1,SIGNAL(clicked()),this, SLOT( initQRT()), true, i18n("QRT"));
	lefttoolbar->insertButton(BarIcon("reload"),1,SIGNAL(clicked()),this, SLOT( initchangeover()), true, i18n("changeover"));
	lefttoolbar->insertButton(BarIcon("konqueror"),5,SIGNAL(clicked()),cqdialog, SLOT( openDialog()), true, i18n(" CQ "));
}

void Kptc :: showCW() {

  modebuttons->buttongroup->setButton(5);

  lefttoolbar->clear();
	lefttoolbar->insertButton(BarIcon("stop"),1,SIGNAL(clicked()),modecommander, SLOT( Standby()), true, i18n("Stand by"));
	lefttoolbar->insertButton(BarIcon("edit"),2,SIGNAL(clicked()),modecommander, SLOT( cwprescribe()), true, i18n("prescribe"));
	lefttoolbar->insertButton(BarIcon("finish"),3,SIGNAL(clicked()),modecommander, SLOT( cwflush()), true, i18n("flush"));
	lefttoolbar->insertButton(BarIcon("player_stop"),1,SIGNAL(clicked()),modecommander, SLOT( cwautospeed()), true, i18n("fix speed"));
	lefttoolbar->insertButton(BarIcon("up"),1,SIGNAL(clicked()),modecommander, SLOT( increaseCWSpeed()), true, i18n("speed up"));
	lefttoolbar->insertButton(BarIcon("down"),1,SIGNAL(clicked()),modecommander, SLOT( decreaseCWSpeed()), true, i18n("speed down"));
	lefttoolbar->insertButton(BarIcon("gear"),7,SIGNAL(clicked()),this, SLOT(showcwspeeddialog()), true, i18n("tx speed"));

	lefttoolbar->insertButton(BarIcon("konqueror"),8,SIGNAL(clicked()),cqdialog, SLOT( openDialog()), true, i18n(" CQ "));
	
}

void Kptc :: showcwspeeddialog() {

  cwspeedwidget->close();
	cwspeedwidget->show();
}


void Kptc :: showrttyspeeddialog() {

	rttyspeedwidget->close();
	rttyspeedwidget->show();


}
void Kptc :: initchangeover() {

	 //textedit->myinsert("[changeover]\n");
	 termoutput->appendString("\n[changeover]\n");
   modecommander->Changeover();
}

void Kptc :: initQRT() {

	//textedit->myinsert("[QRT]\n");
	termoutput->appendString("\n[QRT]\n");
	modecommander->QRT();
}

void Kptc :: updateStatusBar() {

	statusinfo->prompt->setText(modecommander->currendmod());
  if (modecommander->currendmod() == "cmd:")  showPactor();
  else if (modecommander->currendmod() == "AMTOR")  showAmtor();
	else if (modecommander->currendmod() == "AMTOR-MONITOR")  showAmtor();
	else if (modecommander->currendmod() == "RTTY")  showRTTY();
	else if (modecommander->currendmod() == "PSK31")  showPSK31();
	else if (modecommander->currendmod() == "CW")  showCW();
	else showPactor();
}

void Kptc :: parsePrompt(const char c) {


					//  analyze prompt
				
					

					switch( c ) {
					case 32:  	
						modecommander->setcurrendmod("cmd:");
						break;
					case 33:
						modecommander->setcurrendmod("AMTOR");
						break;
					case 34:
						modecommander->setcurrendmod("AMTOR-MONITOR");
						break;						
        	case 35:
						modecommander->setcurrendmod("RTTY");
						break;
					case 36:
						modecommander->setcurrendmod("CW");
						break;
					case 37:
						modecommander->setcurrendmod("PSK31");
						break;				
					default:
						modecommander->setcurrendmod( "??????" );
					}

					updateStatusBar();


}

void Kptc :: parseStatus(const char c) {

	// check DIRECTION bit ( SEND-LED )
	if (( c & 0x08 ) > 0 )    statusinfo->led->on();
	else statusinfo->led->off();

	// check STATUS bits
	QString status;
	switch ( c & 0x07 ) {
  case 0:
		status =  "ERROR";
		break;
  case 1:
		status =  "REQUEST";
		break;
  case 2:
		status =  "TRAFFIC";
		break;
  case 3:
		status =  "IDLE";
		break;
  case 4:
		status =  "OVER";
		break;
  case 5:
		status =  "PHASE";
		break;
  case 6:
		status =  "SYNCH";
		break;
  case 7:
		status =  "";
		break;
	default:
    status =  "??????";
		break;
	}

	statusinfo->status->setText(status);

	// check MODE bits
	QString mode;
	switch ( (c & 112) >> 4 ) {
	case 0:
		mode =  "STAND BY";
		break;
	case 1:
		mode =  "AMTOR-ARQ";
		break;
	case 2:
		mode =  "PACTOR-ARQ";
		break;
	case 3:
		mode =  "AMTOR-FEC";
		break;
	case 4:
		mode =  "PACTOR-FEC";
		break;
	case 5:
		mode =  "RTTY / CW";
		break;
  case 6:
		mode =  "LISTEN";
		break;
	case 7:
		mode =  "channel busy";
		break;
	}
	statusinfo->mode->setText(mode);

 	// read listen mode from status byte ??
	// if ( mode == "LISTEN" ) modecommander->setListen(true);
	// else modecommander->setListen(false);
}


void Kptc::sendFixText( int id ) {


	QString qsid;
	qsid.setNum( id );
	QString filename = configdata.getFixPath(qsid);
	QFile file ( filename );
	if ( ! file.open (IO_ReadOnly)) {
		KMessageBox::error( this,
		i18n("Cannot open fix text file !\n Error by opening \"" + filename +"\""  ) );	 // error by opening text file
		return;
	}		
	QString buffer;

	while (!file.atEnd()) {
	file.readLine( buffer, 1024 );
	Modem::modem->writeLine( buffer );
	}
  file.close() ;

}

void Kptc::openUpdateDialog() {


	UpdateDialog updatedialog;
	if (updatedialog.exec()==QDialog::Accepted) Modem::modem->startNotifier();


}



void Kptc::shutdown() {

	modecommander->changetoPactor();
  sleep(1) ;
	kapp->processEvents();
	configmachine->logout();
	if ( ! Modem::modem->closetty()) kdDebug() << Modem::modem->modemMessage() << endl;	
	
}

/*void Kptc::closeEvent( QCloseEvent* ce ) {

	// emit shutdown();
	ce->accept();

}

*/

void Kptc::fileQuit() {

close();
}

bool Kptc::queryClose() {

	shutdown();

return true;
}


Kptc::~Kptc()
{

	
}
