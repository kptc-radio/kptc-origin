/***************************************************************************
                          configdialog.cpp  -  description
                             -------------------
    begin                : Fri Jan 26 2001
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


#include "configdialog.h"


ConfigDialog::ConfigDialog(QWidget *parent, const char* name, WFlags f)
  : QDialog(parent, name,true, f){



  QListBox* ListBox;
	ListBox = new QListBox( this, "ListBox" );
	ListBox->setGeometry( 10, 10, 110, 290 );
	ListBox->setMinimumSize( 110, 290 );
	ListBox->setMaximumSize( 110, 290 );
	ListBox->setFocusPolicy( QWidget::StrongFocus );
	ListBox->setBackgroundMode( QWidget::PaletteBase );
//	ListBox->setFontPropagation( QWidget::SameFont );
//	ListBox->setPalettePropagation( QWidget::SameFont );
	ListBox->setFrameStyle( 51 );
	ListBox->setLineWidth( 2 );
	ListBox->setMidLineWidth( 0 );
	ListBox->QFrame::setMargin( 0 );
	ListBox->insertItem( "PORT" );
	ListBox->insertItem( "PERSONAL" );
	ListBox->insertItem( "FIX-TEXT" );
	ListBox->insertItem( "PACKET" );
	ListBox->insertItem( "BOX" );
	ListBox->insertItem( "LOGIN" );
	ListBox->insertItem( "LOGOUT" );
	ListBox->setDragSelect( TRUE );
	ListBox->setAutoScroll( TRUE );
	ListBox->setScrollBar( FALSE );
	ListBox->setAutoScrollBar( TRUE );
	ListBox->setBottomScrollBar( FALSE );
	ListBox->setAutoBottomScrollBar( TRUE );
	ListBox->setSmoothScrolling( TRUE );
	ListBox->setMultiSelection( FALSE );
	ListBox->setAutoUpdate( TRUE );

	QPushButton* OkButton;
	OkButton = new QPushButton( this, "OkButton" );
	OkButton->setGeometry( 285, 310, 90, 20 );
	OkButton->setMinimumSize( 90, 20 );
	OkButton->setMaximumSize( 90, 20 );
	OkButton->setFocusPolicy( QWidget::TabFocus );
	OkButton->setBackgroundMode( QWidget::PaletteBackground );
//	OkButton->setFontPropagation( QWidget::NoChildren );
//	OkButton->setPalettePropagation( QWidget::NoChildren );
	OkButton->setText( i18n( "Ok") );
	OkButton->setAutoRepeat( FALSE );
	OkButton->setAutoResize( FALSE );
	OkButton->setToggleButton( FALSE );
	OkButton->setDefault( FALSE );
	OkButton->setAutoDefault( FALSE );
	OkButton->setIsMenuButton( FALSE );


	QPushButton* CancelButton;
	CancelButton = new QPushButton( this, "CancelButton" );
	CancelButton->setGeometry( 395, 310, 90, 20 );
	CancelButton->setMinimumSize( 90, 20 );
	CancelButton->setMaximumSize( 90, 20 );
	CancelButton->setFocusPolicy( QWidget::TabFocus );
	CancelButton->setBackgroundMode( QWidget::PaletteBackground );
//	CancelButton->setFontPropagation( QWidget::NoChildren );
//	CancelButton->setPalettePropagation( QWidget::NoChildren );
	CancelButton->setText( i18n("Cancel") );
	CancelButton->setAutoRepeat( FALSE );
	CancelButton->setAutoResize( FALSE );
	CancelButton->setToggleButton( FALSE );
	CancelButton->setDefault( FALSE );
	CancelButton->setAutoDefault( FALSE );
	CancelButton->setIsMenuButton( FALSE );

  QObject::connect (CancelButton, SIGNAL (clicked()), this, SLOT ( reject()));
  QObject::connect (ListBox, SIGNAL ( clicked( QListBoxItem * ) ), this, SLOT (selectwidget( QListBoxItem *)));
  QObject::connect (OkButton, SIGNAL (clicked()), this, SLOT ( writeconfig()));

	resize( 500,340 );
	setMinimumSize( 500, 340 );
	setMaximumSize( 500, 340 );



  widgetstack= new QWidgetStack(this);
  widgetstack->setFrameStyle(QFrame::Sunken | QFrame::Box);
  widgetstack->setLineWidth(1);
  widgetstack->setMidLineWidth(0);
  widgetstack->setGeometry( 130, 10, 360, 290 );


 // ************************ port settings GUI ********************************


  QWidget *port_top = new QWidget();

  QButtonGroup* port_ButtonGroup_1;
	port_ButtonGroup_1 = new QButtonGroup( port_top, "ButtonGroup_1" );
	port_ButtonGroup_1->setGeometry( 20, 20, 120, 150 );
	port_ButtonGroup_1->setMinimumSize( 0, 0 );
	port_ButtonGroup_1->setMaximumSize( 32767, 32767 );
	port_ButtonGroup_1->setFocusPolicy( QWidget::NoFocus );
	port_ButtonGroup_1->setBackgroundMode( QWidget::PaletteBackground );
//	port_ButtonGroup_1->setFontPropagation( QWidget::NoChildren );
//	port_ButtonGroup_1->setPalettePropagation( QWidget::NoChildren );
	port_ButtonGroup_1->setFrameStyle( 49 );
	port_ButtonGroup_1->setLineWidth( 1 );
	port_ButtonGroup_1->setMidLineWidth( 0 );
	port_ButtonGroup_1->QFrame::setMargin( 0 );
	port_ButtonGroup_1->setTitle( i18n("serial port") );
	port_ButtonGroup_1->setAlignment( 1 );
	port_ButtonGroup_1->setExclusive( true );

	
	port_RadioButton1 = new QRadioButton( port_ButtonGroup_1, "RadioButton1" );
	port_RadioButton1->setGeometry( 15, 20, 100, 20 );
	port_RadioButton1->setMinimumSize( 0, 0 );
	port_RadioButton1->setMaximumSize( 32767, 32767 );
	port_RadioButton1->setFocusPolicy( QWidget::TabFocus );
	port_RadioButton1->setBackgroundMode( QWidget::PaletteBackground );
//	port_RadioButton1->setFontPropagation( QWidget::NoChildren );
//	port_RadioButton1->setPalettePropagation( QWidget::NoChildren );
	port_RadioButton1->setText( "ttyS0 (com 1)" );
	port_RadioButton1->setAutoRepeat( FALSE );
	port_RadioButton1->setAutoResize( FALSE );
	port_RadioButton1->setChecked( FALSE );


	port_RadioButton2 = new QRadioButton( port_ButtonGroup_1, "RadioButton2" );
	port_RadioButton2->setGeometry( 15, 45, 100, 20 );
	port_RadioButton2->setMinimumSize( 0, 0 );
	port_RadioButton2->setMaximumSize( 32767, 32767 );
	port_RadioButton2->setFocusPolicy( QWidget::TabFocus );
	port_RadioButton2->setBackgroundMode( QWidget::PaletteBackground );
//	port_RadioButton2->setFontPropagation( QWidget::NoChildren );
//	port_RadioButton2->setPalettePropagation( QWidget::NoChildren );
	port_RadioButton2->setText( "ttyS1 (com 2)" );
	port_RadioButton2->setAutoRepeat( FALSE );
	port_RadioButton2->setAutoResize( FALSE );
	port_RadioButton2->setChecked( FALSE );

	
	port_RadioButton3 = new QRadioButton( port_ButtonGroup_1, "RadioButton3" );
	port_RadioButton3->setGeometry( 15, 70, 100, 20 );
	port_RadioButton3->setMinimumSize( 0, 0 );
	port_RadioButton3->setMaximumSize( 32767, 32767 );
	port_RadioButton3->setFocusPolicy( QWidget::TabFocus );
	port_RadioButton3->setBackgroundMode( QWidget::PaletteBackground );
//	port_RadioButton3->setFontPropagation( QWidget::NoChildren );
//	port_RadioButton3->setPalettePropagation( QWidget::NoChildren );
	port_RadioButton3->setText( "ttyS2 (com 3)" );
	port_RadioButton3->setAutoRepeat( FALSE );
	port_RadioButton3->setAutoResize( FALSE );
	port_RadioButton3->setChecked( FALSE );

	
	port_RadioButton4 = new QRadioButton( port_ButtonGroup_1, "RadioButton4" );
	port_RadioButton4->setGeometry( 15, 95, 100, 20 );
	port_RadioButton4->setMinimumSize( 0, 0 );
	port_RadioButton4->setMaximumSize( 32767, 32767 );
	port_RadioButton4->setFocusPolicy( QWidget::TabFocus );
	port_RadioButton4->setBackgroundMode( QWidget::PaletteBackground );
//	port_RadioButton4->setFontPropagation( QWidget::NoChildren );
//	port_RadioButton4->setPalettePropagation( QWidget::NoChildren );
	port_RadioButton4->setText( "ttyS3 (com 4)" );
	port_RadioButton4->setAutoRepeat( FALSE );
	port_RadioButton4->setAutoResize( FALSE );
	port_RadioButton4->setChecked( FALSE );

	port_RadioButton5 = new QRadioButton( port_ButtonGroup_1, "RadioButton5" );
	port_RadioButton5->setGeometry( 15, 120, 100, 20 );
	port_RadioButton5->setMinimumSize( 0, 0 );
	port_RadioButton5->setMaximumSize( 32767, 32767 );
	port_RadioButton5->setFocusPolicy( QWidget::TabFocus );
	port_RadioButton5->setBackgroundMode( QWidget::PaletteBackground );
//	port_RadioButton5->setFontPropagation( QWidget::NoChildren );
//	port_RadioButton5->setPalettePropagation( QWidget::NoChildren );
	port_RadioButton5->setAutoRepeat( FALSE );
	port_RadioButton5->setAutoResize( FALSE );
	port_RadioButton5->setChecked( FALSE );

	port_LineEdit_dev = new QLineEdit( port_top, "LineEdit_dev" );
	port_LineEdit_dev->setGeometry( 55, 140, 75, 20 );
	port_LineEdit_dev->setMinimumSize( 0, 0 );
	port_LineEdit_dev->setMaximumSize( 32767, 32767 );
	port_LineEdit_dev->setFocusPolicy( QWidget::StrongFocus );
	port_LineEdit_dev->setBackgroundMode( QWidget::PaletteBase );
//	port_LineEdit_dev->setFontPropagation( QWidget::NoChildren );
//	port_LineEdit_dev->setPalettePropagation( QWidget::NoChildren );
	port_LineEdit_dev->setText( "/dev/ttyS11" );
	port_LineEdit_dev->setMaxLength( 20 );
	port_LineEdit_dev->setFrame( QLineEdit::Normal );
	port_LineEdit_dev->setFrame( TRUE );

	QLabel* port_Label_3;
	port_Label_3 = new QLabel( port_top, "Label_3" );
	port_Label_3->setGeometry( 220, 20, 100, 30 );
	port_Label_3->setMinimumSize( 0, 0 );
	port_Label_3->setMaximumSize( 32767, 32767 );
//	port_Label_3->setFocusPolicy( QWidget::NoFocus );
	port_Label_3->setBackgroundMode( QWidget::PaletteBackground );
//	port_Label_3->setFontPropagation( QWidget::NoChildren );
//	port_Label_3->setPalettePropagation( QWidget::NoChildren );
	port_Label_3->setFrameStyle( 0 );
	port_Label_3->setLineWidth( 1 );
	port_Label_3->setMidLineWidth( 0 );
	port_Label_3->QFrame::setMargin( 0 );
	port_Label_3->setText( i18n( "port speed") );
	port_Label_3->setAlignment( 292 );
	port_Label_3->setMargin( -1 );

	
	port_ComboBox_speed = new QComboBox( FALSE, port_top, "ComboBox_speed" );
	port_ComboBox_speed->setGeometry( 200, 50, 100, 30 );
	port_ComboBox_speed->setMinimumSize( 0, 0 );
	port_ComboBox_speed->setMaximumSize( 32767, 32767 );
	port_ComboBox_speed->setFocusPolicy( QWidget::StrongFocus );
	port_ComboBox_speed->setBackgroundMode( QWidget::PaletteBackground );
//	port_ComboBox_speed->setFontPropagation( QWidget::AllChildren );
//	port_ComboBox_speed->setPalettePropagation( QWidget::AllChildren );
	port_ComboBox_speed->setSizeLimit( 10 );
	port_ComboBox_speed->setAutoResize( FALSE );
	port_ComboBox_speed->insertItem( "9600" );
	port_ComboBox_speed->insertItem( "19200" );
	port_ComboBox_speed->insertItem( "38400" );
	port_ComboBox_speed->insertItem( "57600" );
	port_ComboBox_speed->insertItem( "115200" );
	port_ComboBox_speed->setMaxCount( 10 );
	port_ComboBox_speed->setAutoCompletion( FALSE );

	port_ButtonGroup_1->insert( port_RadioButton1 );
	port_ButtonGroup_1->insert( port_RadioButton2 );
	port_ButtonGroup_1->insert( port_RadioButton3 );
	port_ButtonGroup_1->insert( port_RadioButton4 );


	connect( port_ButtonGroup_1, SIGNAL(clicked(int)), this, SLOT( update_widgets()) );


  widgetstack->addWidget(port_top,0);





// **************************** Pesonal Widget ***************************

QWidget * personal_top = new QWidget();

	QLabel* personal_Label_8;
	personal_Label_8 = new QLabel( personal_top, "Label_8" );
	personal_Label_8->setGeometry( 40, 110, 100, 20 );
	personal_Label_8->setMinimumSize( 0, 0 );
	personal_Label_8->setMaximumSize( 32767, 32767 );
	personal_Label_8->setFocusPolicy( QWidget::NoFocus );
	personal_Label_8->setBackgroundMode( QWidget::PaletteBackground );
//	personal_Label_8->setFontPropagation( QWidget::NoChildren );
//	personal_Label_8->setPalettePropagation( QWidget::NoChildren );
	personal_Label_8->setFrameStyle( 0 );
	personal_Label_8->setLineWidth( 1 );
	personal_Label_8->setMidLineWidth( 0 );
	personal_Label_8->QFrame::setMargin( 0 );
	personal_Label_8->setText( "SELCALL:" );
	personal_Label_8->setAlignment( 289 );
	personal_Label_8->setMargin( -1 );



	QLabel* personal_Label_7;
	personal_Label_7 = new QLabel( personal_top, "Label_7" );
	personal_Label_7->setGeometry( 40, 80, 100, 20 );
	personal_Label_7->setMinimumSize( 0, 0 );
	personal_Label_7->setMaximumSize( 32767, 32767 );
	personal_Label_7->setFocusPolicy( QWidget::NoFocus );
	personal_Label_7->setBackgroundMode( QWidget::PaletteBackground );
//	personal_Label_7->setFontPropagation( QWidget::NoChildren );
//	personal_Label_7->setPalettePropagation( QWidget::NoChildren );
	personal_Label_7->setFrameStyle( 0 );
	personal_Label_7->setLineWidth( 1 );
	personal_Label_7->setMidLineWidth( 0 );
	personal_Label_7->QFrame::setMargin( 0 );
	personal_Label_7->setText( "CALL:" );
	personal_Label_7->setAlignment( 289 );
	personal_Label_7->setMargin( -1 );

	QLabel* personal_Label_qth;
	personal_Label_qth = new QLabel( personal_top, "Label_qth" );
	personal_Label_qth->setGeometry( 40, 50, 100, 20 );	
	personal_Label_qth->setFrameStyle( 0 );
	personal_Label_qth->setLineWidth( 1 );
	personal_Label_qth->setMidLineWidth( 0 );
	personal_Label_qth->QFrame::setMargin( 0 );
	personal_Label_qth->setText( "QTH:" );
	personal_Label_8->setAlignment( 289 );
	personal_Label_8->setMargin( -1 );

	QLabel* personal_Label_6;
	personal_Label_6 = new QLabel( personal_top, "Label_6" );
	personal_Label_6->setGeometry( 40, 20, 100, 20 );
	personal_Label_6->setMinimumSize( 0, 0 );
	personal_Label_6->setMaximumSize( 32767, 32767 );
	personal_Label_6->setFocusPolicy( QWidget::NoFocus );
	personal_Label_6->setBackgroundMode( QWidget::PaletteBackground );
//	personal_Label_6->setFontPropagation( QWidget::NoChildren );
//	personal_Label_6->setPalettePropagation( QWidget::NoChildren );
	personal_Label_6->setFrameStyle( 0 );
	personal_Label_6->setLineWidth( 1 );
	personal_Label_6->setMidLineWidth( 0 );
	personal_Label_6->QFrame::setMargin( 0 );
	personal_Label_6->setText( i18n("Name:") );
	personal_Label_6->setAlignment( 289 );
	personal_Label_6->setMargin( -1 );

	
	personal_LineEdit_name = new QLineEdit( personal_top, "LineEdit_name" );
	personal_LineEdit_name->setGeometry( 120, 20, 80, 20 );
	personal_LineEdit_name->setMinimumSize( 0, 0 );
	personal_LineEdit_name->setMaximumSize( 32767, 32767 );
	personal_LineEdit_name->setFocusPolicy( QWidget::StrongFocus );
	personal_LineEdit_name->setBackgroundMode( QWidget::PaletteBase );
//	personal_LineEdit_name->setFontPropagation( QWidget::NoChildren );
//	personal_LineEdit_name->setPalettePropagation( QWidget::NoChildren );
	personal_LineEdit_name->setText( "TUX" );
	personal_LineEdit_name->setMaxLength( 20 );
	personal_LineEdit_name->setFrame( QLineEdit::Normal );
	personal_LineEdit_name->setFrame( TRUE );

	personal_LineEdit_qth = new QLineEdit( personal_top, "LineEdit_qth" );
	personal_LineEdit_qth->setGeometry( 120, 50, 80, 20 );
	personal_LineEdit_qth->setMinimumSize( 0, 0 );
	personal_LineEdit_qth->setMaximumSize( 32767, 32767 );
	personal_LineEdit_qth->setText( "Nürnberg" );
	personal_LineEdit_qth->setMaxLength( 30 );
	personal_LineEdit_qth->setFrame( QLineEdit::Normal );
	personal_LineEdit_qth->setFrame( TRUE );
	
	personal_LineEdit_call = new QLineEdit( personal_top, "LineEdit_call" );
	personal_LineEdit_call->setGeometry( 120, 80, 80, 20 );
	personal_LineEdit_call->setMinimumSize( 0, 0 );
	personal_LineEdit_call->setMaximumSize( 32767, 32767 );
	personal_LineEdit_call->setFocusPolicy( QWidget::StrongFocus );
	personal_LineEdit_call->setBackgroundMode( QWidget::PaletteBase );
//	personal_LineEdit_call->setFontPropagation( QWidget::NoChildren );
//	personal_LineEdit_call->setPalettePropagation( QWidget::NoChildren );
	personal_LineEdit_call->setText( "DK0TUX" );
	personal_LineEdit_call->setMaxLength( 12 );
	personal_LineEdit_call->setFrame( QLineEdit::Normal );
	personal_LineEdit_call->setFrame( TRUE );

	
	personal_LineEdit_selcall = new QLineEdit( personal_top, "LineEdit_selcall" );
	personal_LineEdit_selcall->setGeometry( 120, 110, 80, 20 );
	personal_LineEdit_selcall->setMinimumSize( 0, 0 );
	personal_LineEdit_selcall->setMaximumSize( 32767, 32767 );
	personal_LineEdit_selcall->setFocusPolicy( QWidget::StrongFocus );
	personal_LineEdit_selcall->setBackgroundMode( QWidget::PaletteBase );
//	personal_LineEdit_selcall->setFontPropagation( QWidget::NoChildren );
//	personal_LineEdit_selcall->setPalettePropagation( QWidget::NoChildren );
	personal_LineEdit_selcall->setText( "DTUX" );
	personal_LineEdit_selcall->setMaxLength( 4 );
	personal_LineEdit_selcall->setFrame( QLineEdit::Normal );
	personal_LineEdit_selcall->setFrame( TRUE );

	personal_CheckBox_cmsg = new QCheckBox(personal_top);
	personal_CheckBox_cmsg->setText( i18n("set \"connect message\"") );
	personal_CheckBox_cmsg->setGeometry( 120, 150, 150, 20 );
	personal_MultiLineEdit_ctext = new QMultiLineEdit(personal_top);
  personal_MultiLineEdit_ctext->setGeometry( 120, 170, 230, 100 );

	connect( personal_CheckBox_cmsg, SIGNAL(clicked()), this, SLOT( update_widgets()) );



  widgetstack->addWidget(personal_top,1);
///////////////////////////////////////////////////////////////////////////////////////
// *******************  FIX TEXT WIDGET   *****************************
	QWidget * fixtext_top = new QWidget(0, "fixtext_top");

	list.clear();
	oblist.clear();

	QBoxLayout *layout = new QBoxLayout(  fixtext_top, QBoxLayout::TopToBottom, 0, 0 );

	QString number;
	for ( int i = 1 ; i <= 8; i++ ) {
		number.setNum(i);

	FixTextPicker *tp = new FixTextPicker(fixtext_top, "textpicker_" + number);
  tp->numlabel->setText( number + ".");

	layout->addWidget( tp );

	list.append( tp );
  oblist.append (  tp->choosebutton );

	connect ( tp->choosebutton, SIGNAL (clicked()), this, SLOT ( chooseFile()));

	}




	layout->activate();

  widgetstack->addWidget(fixtext_top,3);


///////////////////////////////////////////////////////////////////////////////////////
//  ******************   BOX WIDGET  ***********************************

  QWidget * box_top = new QWidget();
	QLabel* box_Label;
	box_Label = new QLabel( box_top, "box" );
  box_Label->setText(" coming soon ... ");


  widgetstack->addWidget(box_top,4);


///////////////////////////////////////////////////////////////////////////////////////
// *******************  LOGOUT WIDGET  ********************************

	QWidget * logout_top = new QWidget();

	logout_CheckBox_cmsg = new QCheckBox(logout_top);
	logout_CheckBox_cmsg->setText( i18n("set \"away message\"") );
	logout_CheckBox_cmsg->setGeometry( 5, 5, 150, 20 );
	logout_MultiLineEdit_ctext = new QMultiLineEdit(logout_top);
  logout_MultiLineEdit_ctext->setGeometry( 150, 5, 200, 100 );
	logout_CheckBox_script = new QCheckBox(logout_top);
	logout_CheckBox_script->setText( i18n("use personal logout script") );
	logout_CheckBox_script->setGeometry( 5, 130, 200, 20 );
	logout_LineEdit_path = new QLineEdit(logout_top);
	logout_LineEdit_path->setGeometry( 5, 150, 150, 20 );
	logout_PushButton_choosescript = new QPushButton(i18n("choose"), logout_top);
	logout_PushButton_choosescript->setGeometry( 170, 150, 50, 20 );	

	connect( logout_PushButton_choosescript, SIGNAL(	clicked() ), this, SLOT( chooseLogoutFile()) );		


	connect( logout_CheckBox_cmsg, SIGNAL(clicked()), this, SLOT( update_widgets()) );
	connect( logout_CheckBox_script, SIGNAL(clicked()), this, SLOT( update_widgets()) );

	widgetstack->addWidget(logout_top,2);
///////////////////////////////////////////////////////////////////////////////////////
// *********************  LOGIN WIDGET  ********************************

	QWidget * login_top = new QWidget();

	login_CheckBox_script = new QCheckBox(login_top);
	login_CheckBox_script->setText( i18n("use personal login script") );
	login_CheckBox_script->setGeometry( 5, 5, 200, 20 );
	login_LineEdit_path = new QLineEdit(login_top);
	login_LineEdit_path->setGeometry( 5, 30, 150, 20 );
	login_PushButton_choosescript = new QPushButton(i18n("choose"), login_top);
	login_PushButton_choosescript->setGeometry( 170, 30, 50, 20 );			

	connect( login_PushButton_choosescript, SIGNAL(	clicked() ), this, SLOT( chooseLoginFile()) );
	connect( login_CheckBox_script, SIGNAL(clicked()), this, SLOT( update_widgets()) );	

	widgetstack->addWidget(login_top,5);

////////////////////////////////////////////////////////////////////////////////////////



// final :
  widgetstack->raiseWidget(0);
  resetwidgets();

}


void ConfigDialog::selectwidget( QListBoxItem * lbi ) {

if (lbi == NULL) return;

if (lbi->text() == "PORT")  widgetstack->raiseWidget(0);
else if (lbi->text() == "PERSONAL")  widgetstack->raiseWidget(1);
else if (lbi->text() == "LOGOUT")  widgetstack->raiseWidget(2);
else if (lbi->text() == "FIX-TEXT")  widgetstack->raiseWidget(3);
else if (lbi->text() == "BOX")  widgetstack->raiseWidget(4);
else if (lbi->text() == "LOGIN") widgetstack->raiseWidget(5);
else  widgetstack->raiseWidget(4);
// else
 kdDebug() <<"item: "<< lbi->text() << endl;

}

void ConfigDialog::resetwidgets() {

	QString port = configdata.getPort();
  if ( port == "/dev/ttyS0" ) port_RadioButton1->setChecked( TRUE );
  else if ( port == "/dev/ttyS1" ) port_RadioButton2->setChecked( TRUE );
  else if ( port == "/dev/ttyS2" ) port_RadioButton3->setChecked( TRUE );
  else if ( port == "/dev/ttyS3" ) port_RadioButton4->setChecked( TRUE );
  else  port_RadioButton5->setChecked( TRUE );
	port_LineEdit_dev->setText(configdata.getEditPort());
	

  QString portspeed = configdata.getPortSpeed();

  if ( portspeed == "9600" ) port_ComboBox_speed->setCurrentItem(0);
  else if ( portspeed == "19200" ) port_ComboBox_speed->setCurrentItem(1);
  else if ( portspeed == "38400" ) port_ComboBox_speed->setCurrentItem(2);
  else if ( portspeed == "57600" ) port_ComboBox_speed->setCurrentItem(3);
  else if ( portspeed == "115200" ) port_ComboBox_speed->setCurrentItem(4);
  else  port_ComboBox_speed->setCurrentItem(4);

	// reset personal widget
  personal_LineEdit_call->setText(configdata.getCall());
  personal_LineEdit_selcall->setText(configdata.getSelCall());
	personal_CheckBox_cmsg->setChecked( configdata.isCMsg() );
	personal_MultiLineEdit_ctext->setText( configdata.getCMsg() );
	personal_LineEdit_qth->setText(configdata.getQTH());
	personal_LineEdit_name->setText(configdata.getName());

  // reset logout widget
	logout_CheckBox_cmsg->setChecked( configdata.isAwayMsg() );
	logout_MultiLineEdit_ctext->setText( configdata.getAwayMsg() ) ;

	logout_LineEdit_path->setText( configdata.getLogoutPath() );
	logout_CheckBox_script->setChecked( configdata.isLogoutScript());

	// reset login widget
	login_LineEdit_path->setText( configdata.getLoginPath() );
	login_CheckBox_script->setChecked( configdata.isLoginScript());	

	// reset fix text widget
  FixTextPicker  *FixDummy;
  for ( FixDummy=list.first(); FixDummy != 0; FixDummy=list.next() )   {
  	
		QString num;
		num.setNum( list.findRef ( FixDummy ) + 1 );
		

		QString s = configdata.getFixLabel( num );
		FixDummy->editlabel->setText( s );

		s = configdata.getFixPath( num );
		FixDummy->editpath->setText( s );

  }
		

	update_widgets();



}

void ConfigDialog::writeconfig() {



	configdata.setPortSpeed( port_ComboBox_speed->currentText() );
  QString port;

  if (port_RadioButton1->isOn()) port = "/dev/ttyS0";
  else if (port_RadioButton2->isOn()) port = "/dev/ttyS1";
  else if (port_RadioButton3->isOn()) port = "/dev/ttyS2";
  else if (port_RadioButton4->isOn()) port = "/dev/ttyS3";
  else port =port_LineEdit_dev->text();
  configdata.setPort(port);
	configdata.setEditPort(port_LineEdit_dev->text());

  configdata.setCall( personal_LineEdit_call->text());
  configdata.setSelCall( personal_LineEdit_selcall->text());
  configdata.setCMsg( personal_CheckBox_cmsg->isChecked(), personal_MultiLineEdit_ctext->text() );
	configdata.setAwayMsg( logout_CheckBox_cmsg->isChecked(), logout_MultiLineEdit_ctext->text() );
	configdata.setLogoutPath( logout_LineEdit_path->text());
	configdata.setLogoutScript( logout_CheckBox_script->isChecked() );
	configdata.setLoginPath( login_LineEdit_path->text());
	configdata.setLoginScript( login_CheckBox_script->isChecked() );
	configdata.setName( personal_LineEdit_name->text() );
	configdata.setQTH(  personal_LineEdit_qth->text() );


	// fixtext	
  FixTextPicker  *FixDummy;
	QString num;
  for ( FixDummy=list.first(); FixDummy != 0; FixDummy=list.next() )   {
  	
		
		num.setNum( list.findRef ( FixDummy ) + 1 );
		
		configdata.setFixLabel( FixDummy->editlabel->text(), num );
		configdata.setFixPath( FixDummy->editpath->text(), num );
	

  }
  accept();

}

void ConfigDialog::chooseFile() {

	QString s( QFileDialog::getOpenFileName( QString::null, "", this ) );
  if ( s.isEmpty() )
        return;
	
	int i = oblist.findRef( sender() );
	FixTextPicker * FixDummy = list.at( i );
	QString num;
	num.setNum( i + 1 );

	FixDummy->editpath->setText( s );
	configdata.setFixPath( s, num);

}


void ConfigDialog::chooseLogoutFile() {

	QString s( QFileDialog::getOpenFileName( QString::null, "", this ) );
  if ( s.isEmpty() )
        return;
  logout_LineEdit_path->setText(s);


}

void ConfigDialog::chooseLoginFile() {

	QString s( QFileDialog::getOpenFileName( QString::null, "", this ) );
  if ( s.isEmpty() )
        return;
  login_LineEdit_path->setText(s);


}


void ConfigDialog::update_widgets() {

port_LineEdit_dev->setEnabled( port_RadioButton5->isOn() );
personal_MultiLineEdit_ctext->setEnabled(  personal_CheckBox_cmsg->isChecked() );
logout_MultiLineEdit_ctext->setEnabled( logout_CheckBox_cmsg->isChecked() );
logout_LineEdit_path->setEnabled( logout_CheckBox_script->isChecked() );
login_LineEdit_path->setEnabled(  login_CheckBox_script->isChecked() );

}


ConfigDialog::~ConfigDialog(){
}
