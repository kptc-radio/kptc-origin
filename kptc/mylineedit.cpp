/***************************************************************************
                          mylineedit.cpp  -  description
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

#include "mylineedit.h"
#include <kdebug.h>

MyLineEdit::MyLineEdit(QWidget *parent, const char *name) : QLineEdit(parent, name){

  this->setFont(QFont("courier",12,QFont::Normal));
  setReadOnly (false);
  setMinimumSize( 400, 30 );
  setMaximumSize( 1690, 30 );
	setFocusPolicy( QWidget::StrongFocus );
	//connect ( this, SIGNAL(returnPressed()), this, SLOT(clear()) );
	commandmode = true;
	cursorpos = 0;
	promptlength = 0;
	commandlist.setAutoDelete(true);
	commandlist.clear();
	commandlist.append(new QString(""));

}


void MyLineEdit::notify(const QObject *receiver, const char *member) {
  connect(this, SIGNAL(sendit(unsigned char)), receiver, member);

}

void MyLineEdit::setPrompt(QString prompt) {

	qsprompt = prompt;
	setText( prompt );
	promptlength = prompt.length();
	if ( prompt == "") commandmode = false;
	else commandmode = true;


}



void MyLineEdit::keyPressEvent(QKeyEvent *ke) {

    ke->accept();
    switch ( ke->key() ) {

		case Key_Left:
			if (!commandmode) return;
			if (cursorPosition()<= promptlength) return;
			break;
		case Key_Right:
			if (!commandmode) return;
			break;
		case Key_Backspace:
			if (commandmode && cursorPosition()<= promptlength) return;
			break;

		case Key_Up:
      if (commandmode) {
				QString *pprev;				
				pprev = commandlist.prev();
				if (pprev) {

					QString updummy = qsprompt;
					updummy.append(*pprev);
					setText(updummy);
					end(false);
				}	
				else commandlist.first();						
			}
			return;

		case Key_Down:
      if (commandmode) {
				if ( * commandlist.current() == "" ) return;
				QString *pnext;
				pnext = commandlist.next();
        if (pnext) {
					QString downdummy = qsprompt;
					downdummy.append(*pnext);
					setText(downdummy);
					end(false);
        }
			}
			return;


		case Key_Enter:
		case Key_Return:
			if ( commandmode ) {
				emit echoCommand(text().prepend("\n"));
				if (promptlength > 0) {
					QString qtext = text();
					qtext.remove(0,(promptlength));
					qtext.stripWhiteSpace();	
					sendit(qtext);
          commandlist.last();
					if (qtext != "") { commandlist.remove(); commandlist.append(new QString(qtext)); commandlist.append(new QString(""));}					
					if (commandlist.count() > 10 ) commandlist.removeFirst();
					commandlist.last();
				}
			}

			setText("");
			commandmode = false;
		break;			


		}

		
    char a = ke->ascii();
		
    if (!commandmode) sendit(a);

		if ( ke->key() == CTRL + Key_Z || ke->key()== CTRL + Key_U ) return;
		QLineEdit::keyPressEvent(ke);       // lokale Echo ??

}


void MyLineEdit::insertChar(unsigned char c) {
  myinsert(QChar(c));
}

void MyLineEdit::myinsert( QString ) {

 /* // get cursor position
  int line, col;
  getCursorPosition( &line, &col );

  // write text
  insertAt( qs, line, col );
	 */

}



void MyLineEdit::focusInEvent( QFocusEvent * ev )
{

	QLineEdit::focusInEvent( ev );
  setCursorPosition(cursorpos);
}

void MyLineEdit::focusOutEvent ( QFocusEvent * ev )
{

	cursorpos = cursorPosition();
	QLineEdit::focusInEvent( ev );

}


MyLineEdit::~MyLineEdit(){
}
