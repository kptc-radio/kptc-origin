/***************************************************************************
                          configdata.cpp  -  description
                             -------------------
    begin                : Wed Feb 14 2001
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


#include "configdata.h"
#include <qmap.h>
#include <kapp.h>
#include <ksimpleconfig.h>
#include <kmessagebox.h>
#include <kdebug.h>

#include <qregexp.h>




ConfigData configdata;


ConfigData::ConfigData()
{
}

ConfigData::~ConfigData(){
}


QString ConfigData::parseMacroText( QString text ) {

	text.replace( QRegExp("%MYCALL%"), configdata.getCall() );
	text.replace( QRegExp("%MYSELCALL%"), configdata.getSelCall() );
	text.replace( QRegExp("%MYQTH%"), configdata.getQTH() );
	text.replace( QRegExp("%MYNAME%"), configdata.getName() );
	

	return text;		

}


// change and read keys

void ConfigData::setPort(const QString dev) {

  if (dev != 0L){
  KSimpleConfig conf( "kptcrc" );
  conf.setGroup("PORT");
  conf.writeEntry("PORTDEVICE", dev);
  }
}

QString ConfigData::getPort() {
 KSimpleConfig conf( "kptcrc" );
 conf.setGroup("PORT");
 QString s = conf.readEntry( "PORTDEVICE", "/dev/ttyS0");     // default: com 1

return s;

}

void ConfigData::setEditPort(const QString dev) {

  KSimpleConfig conf( "kptcrc" );
  conf.setGroup("PORT");
  conf.writeEntry("PORTDEVICE_EDIT", dev);
}

QString ConfigData::getEditPort() {
 KSimpleConfig conf( "kptcrc" );
 conf.setGroup("PORT");
 QString s = conf.readEntry( "PORTDEVICE_EDIT", "/dev/ttyS11");

return s;

}

void ConfigData::setPortSpeed(const QString speed) {

  if (speed != 0L){
  KSimpleConfig conf( "kptcrc" );
  conf.setGroup("PORT");
  conf.writeEntry("PORTSPEED", speed);
  }

}


QString ConfigData::getPortSpeed() {
	KSimpleConfig conf("kptcrc");
	conf.setGroup("PORT");
	QString s = conf.readEntry( "PORTSPEED", "38400");
return s;

}

void ConfigData::setCall( QString call ){
 KSimpleConfig conf("kptcrc");
 conf.setGroup("PERSONAL");
 conf.writeEntry("CALL", call);
}


QString ConfigData::getCall(){
 KSimpleConfig conf("kptcrc");
 conf.setGroup("PERSONAL");
 QString s = conf.readEntry( "CALL", "DK0TUX");
return s;
}

void ConfigData::setSelCall( QString call ){
 KSimpleConfig conf("kptcrc");
 conf.setGroup("PERSONAL");
 conf.writeEntry("SELCALL", call);
}


QString ConfigData::getSelCall(){
 KSimpleConfig conf("kptcrc");
 conf.setGroup("PERSONAL");
 QString s = conf.readEntry( "SELCALL", "DTUX");
return s;
}


void ConfigData::setfirststart( bool  first) {

	KSimpleConfig conf("kptcrc");
	conf.setGroup("GENERAL");
	if (!first) conf.writeEntry("FIRSTSTART", "FALSE");
}

bool ConfigData::firststart() {

  KSimpleConfig conf("kptcrc");
	conf.setGroup("GENERAL");
	QString s= conf.readEntry("FIRSTSTART", "TRUE");
  kdDebug() << "configdata::firststart() - entry:" << s << endl;
	if ( s == "TRUE" ) return true;
	else return false;

}

void ConfigData::setAwayMsg(bool set, QString msg) {

  KSimpleConfig conf("kptcrc");
	conf.setGroup("LOGOUT");
	if (set) conf.writeEntry("USEAWAYMSG", "TRUE");
	else conf.writeEntry("USEAWAYMSG", "FALSE");
	conf.writeEntry("AWAYMSG", msg );	

}

bool ConfigData::isAwayMsg() {
	
	KSimpleConfig conf("kptcrc");
	conf.setGroup("LOGOUT");
	QString s= conf.readEntry("USEAWAYMSG", "TRUE");
	if (s == "TRUE") return true;
	else return false;

}

QString ConfigData::getAwayMsg() {

	KSimpleConfig conf("kptcrc");
	conf.setGroup("LOGOUT");
	QString s= conf.readEntry("AWAYMSG", "Here is %MYCALL% from %MYQTH%,\n\ncurrently terminal is not active!\n\n73 de %MYNAME%.");
	return s;

}
/////
void ConfigData::setCMsg(bool set, QString msg) {

  KSimpleConfig conf("kptcrc");
	conf.setGroup("PERSONAL");
	if (set) conf.writeEntry("USECMSG", "TRUE");
	else conf.writeEntry("USECMSG", "FALSE");
	conf.writeEntry("CMSG", msg );	

}

bool ConfigData::isCMsg() {
	
	KSimpleConfig conf("kptcrc");
	conf.setGroup("PERSONAL");
	QString s= conf.readEntry("USECMSG", "TRUE");
	if (s == "TRUE") return true;
	else return false;

}

QString ConfigData::getCMsg() {

	KSimpleConfig conf("kptcrc");
	conf.setGroup("PERSONAL");
	QString s= conf.readEntry("CMSG", "Here is %MYCALL% from %MYQTH% !");
	return s;

}


void ConfigData::setCQPactor( QString qtext ) {

	KSimpleConfig conf("kptcrc");
	conf.setGroup("CQTEXT");

	conf.writeEntry("PACTOR", qtext );	

}

QString ConfigData::getCQPactor() {

  KSimpleConfig conf("kptcrc");
	conf.setGroup("CQTEXT");
	QString s= conf.readEntry("PACTOR", "CQ CQ CQ de %MYCALL%\nCQ CQ CQ de %MYCALL%\nCQ CQ CQ de %MYCALL%\npse K\n");
	return s;
}

void ConfigData::setCQAmtor( QString qtext ) {

	KSimpleConfig conf("kptcrc");
	conf.setGroup("CQTEXT");

	conf.writeEntry("AMTOR", qtext );	

}

QString ConfigData::getCQAmtor() {

  KSimpleConfig conf("kptcrc");
	conf.setGroup("CQTEXT");
	QString s= conf.readEntry("AMTOR", "CQ CQ CQ de %MYCALL%\nCQ CQ CQ de %MYCALL%\nCQ CQ CQ de %MYCALL%\npse K\n");
	return s;
}

void ConfigData::setCQRTTY( QString qtext ) {

	KSimpleConfig conf("kptcrc");
	conf.setGroup("CQTEXT");

	conf.writeEntry("RTTY", qtext );	

}

QString ConfigData::getCQRTTY() {

  KSimpleConfig conf("kptcrc");
	conf.setGroup("CQTEXT");
	QString s= conf.readEntry("RTTY", "ryryryryryry\nCQ CQ CQ de %MYSELCALL%\nCQ CQ CQ de %MYSELCALL%\npse K\n");
	return s;
}
void ConfigData::setCQPSK31( QString qtext ) {

	KSimpleConfig conf("kptcrc");
	conf.setGroup("CQTEXT");

	conf.writeEntry("PSK31", qtext );	

}

QString ConfigData::getCQPSK31() {

  KSimpleConfig conf("kptcrc");
	conf.setGroup("CQTEXT");
	QString s= conf.readEntry("PSK31", "CQ CQ CQ de %MYCALL%\nCQ CQ CQ de %MYCALL%\nCQ CQ CQ de %MYCALL%\npse K\n");
	return s;
}

void ConfigData::setCQCW( QString qtext ) {

	KSimpleConfig conf("kptcrc");
	conf.setGroup("CQTEXT");

	conf.writeEntry("CW", qtext );	

}

QString ConfigData::getCQCW() {

  KSimpleConfig conf("kptcrc");
	conf.setGroup("CQTEXT");
	QString s= conf.readEntry("CW", "cq cq cq de %MYCALL%\ncq cq cq de %MYCALL%\npse k\n");
	return s;
}


void ConfigData::setFixLabel( QString label, QString number) {

	KSimpleConfig conf("kptcrc");
	conf.setGroup("FIXTEXT");
	conf.writeEntry( number, label );
}

QString ConfigData::getFixLabel ( QString number ) {

	KSimpleConfig conf("kptcrc");
	conf.setGroup("FIXTEXT");
	QString s = conf.readEntry( number, "TEXT NR. " + number );
	return s;
}

void ConfigData::setFixPath( QString path, QString number) {

	KSimpleConfig conf("kptcrc");
	conf.setGroup("FIXTEXT");
	conf.writeEntry( number + "PATH" , path );
}

QString ConfigData::getFixPath ( QString number ) {

	KSimpleConfig conf("kptcrc");
	conf.setGroup("FIXTEXT");
	QString s = conf.readEntry( number + "PATH" , "" );
	return s;
}

void ConfigData::setName( QString name ) {

 KSimpleConfig conf("kptcrc");
 conf.setGroup("PERSONAL");
 conf.writeEntry("NAME", name);
}

QString ConfigData::getName(){

 KSimpleConfig conf("kptcrc");
 conf.setGroup("PERSONAL");
 QString s = conf.readEntry( "NAME", "Tux");
return s;
}

void ConfigData::setQTH( QString name ) {

 KSimpleConfig conf("kptcrc");
 conf.setGroup("PERSONAL");
 conf.writeEntry("QTH", name);
}

QString ConfigData::getQTH(){

 KSimpleConfig conf("kptcrc");
 conf.setGroup("PERSONAL");
 QString s = conf.readEntry( "QTH", "Antarctic");
return s;
}


void ConfigData::setLogoutPath( QString path) {

	KSimpleConfig conf("kptcrc");
	conf.setGroup("LOGOUT");
	conf.writeEntry( "PATH" , path );
}

QString ConfigData::getLogoutPath () {

	KSimpleConfig conf("kptcrc");
	conf.setGroup("LOGOUT");
	QString s = conf.readEntry( "PATH" , "" );
	return s;
}


void ConfigData::setLoginPath( QString path) {

	KSimpleConfig conf("kptcrc");
	conf.setGroup("LOGIN");
	conf.writeEntry( "PATH" , path );
}

QString ConfigData::getLoginPath () {

	KSimpleConfig conf("kptcrc");
	conf.setGroup("LOGIN");
	QString s = conf.readEntry( "PATH" , "" );
	return s;
}

void ConfigData::setLogoutScript( bool set ) {

	QString qset;
	if (set) qset = "TRUE";
	else qset = "FALSE";
	KSimpleConfig conf("kptcrc");
	conf.setGroup("LOGOUT");
	conf.writeEntry( "LOGOUTSCRIPT" , qset );

}

bool ConfigData::isLogoutScript() {

	KSimpleConfig conf("kptcrc");
	conf.setGroup("LOGOUT");
	QString s = conf.readEntry( "LOGOUTSCRIPT" , "FALSE" );
	if ( s == "TRUE" ) return true;
	else return false;

}


void ConfigData::setLoginScript( bool set ) {

	QString qset;
	if (set) qset = "TRUE";
	else qset = "FALSE";
	KSimpleConfig conf("kptcrc");
	conf.setGroup("LOGIN");
	conf.writeEntry( "LOGINSCRIPT" , qset );

}

bool ConfigData::isLoginScript() {

	KSimpleConfig conf("kptcrc");
	conf.setGroup("LOGIN");
	QString s = conf.readEntry( "LOGINSCRIPT" , "FALSE" );
	if ( s == "TRUE" ) return true;
	else return false;

}


