/***************************************************************************
                          mytermout.cpp  -  description
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


#include "mytermout.h"
#include <stdio.h>
#include <stdlib.h>
#include <qtimer.h>
#include <qclipboard.h>
#include <qapplication.h>

MyTermout::MyTermout(QWidget *parent, const char *name) : QtTableView(parent, name)
{
  setWFlags(WResizeNoErase/*|WRepaintNoErase*/);
	line.setAutoDelete(true);
  scrolltimer = NULL;
  firstline = -1;
	lastline = -1;
	maxlines=1000;
	// set some initial flags
	font = QFont::defaultFont();
	setFont (font);
	currentcol = Qt::black;
	setNumCols(1);
	setNumRows(0);

	setAutoUpdate (true);
	setTableFlags (Tbl_vScrollBar/*|Tbl_smoothVScrolling|Tbl_clipCellPainting*/);
  setBackgroundMode (PaletteBase);
	setFrameStyle (QFrame::WinPanel|QFrame::Sunken);
	show();

	vscroll = (QScrollBar*) verticalScrollBar();
  ((QScrollBar *)vscroll)->setSteps(cellHeight(0), ((QScrollBar *)vscroll)->pageStep()-cellHeight(0));

	blinktimer = new QTimer (this);
	QObject::connect (blinktimer, SIGNAL(timeout()), SLOT(slotCursorBlink()));

	setEditEnabled (false);
	newLine();
	QObject::connect (this, SIGNAL (keyPressed(char)), this, SLOT (slotKey(char)));
}

MyTermout::~MyTermout()
{
}

static QPixmap *buffer = 0;

static void cleanupMLBuffer()
{
    delete buffer;
    buffer = 0;
}

static QPixmap* getCacheBuffer( QSize sz )
{
  if ( !buffer ) {
		qAddPostRoutine( cleanupMLBuffer );
		buffer = new QPixmap;
  	}

    if ( buffer->width() < sz.width() || buffer->height() < sz.height() )
			buffer->resize( sz );
    return buffer;
}

/** This draws an Line to the widget */

void MyTermout::paintCell (QPainter* p, int row, int col)
{
	QString text;
	QColor color;
	bool marked;
	QPainter painter;
	const QColorGroup & g = colorGroup();
	QFontMetrics fm(font);
	int y = fm.ascent();
	int x = 2;
  QRect updateR = cellUpdateRect();
  QPixmap *buffer = getCacheBuffer( updateR.size() );

  buffer->fill ( g.base() );

	if ((int) (line.count()-1) >= row) {
		text = line.at(row)->text();
		color = line.at(row)->color();
		marked = line.at(row)->marked();

	  painter.begin( buffer );
		painter.translate( -updateR.left(), -updateR.top() );

		painter.setFont (font);

		if (marked) {
			painter.setPen (g.highlightedText() );
			painter.fillRect (updateR.left(), updateR.top(), fm.width(text)+3, fm.height(), g.brush( QColorGroup::Highlight ));
			painter.drawText (x, y, text);
		}
		else {
			painter.setPen (color);
			painter.drawText (x, y, text);
		}
	/* Draw the cursor if we are in the last line */

		if ((cursoron == true) && (edited == true) && (row == (int) (line.count()-1)) ) {
			painter.drawLine (updateR.left()+fm.width(text)+2, updateR.top()+1, updateR.left()+fm.width(text)+2, fm.height()-2);
		}
	  painter.end();
	}
  p->drawPixmap( updateR.left(), updateR.top(), *buffer,
			 0, 0, updateR.width(), updateR.height() );
}

void MyTermout::newLine()
{
	bool add_line = true;
  bool unten_bleiben = false;

  if ((vscroll->value() == vscroll->maxValue()) || (vscroll->maxValue() == 0))
    unten_bleiben = true;

	if (line.count()+1 >= maxlines) {                  // we have all occupied, remove the first line
			line.removeFirst();
			line.append (new TextLine (currentcol));
			repaint(false);

      if (!unten_bleiben)
      {
         if (vscroll->value() == 0)
         {
            repaint(false);
         }
         else
         {
            vscroll->subtractLine();
         }
      }
   }
   else
   {
      add_line = true;
			line.append (new TextLine (currentcol));
			setNumRows (line.count());
   }

	if (unten_bleiben) {
		int t = totalHeight();
		int v = viewHeight();
		if (t>v) {
			if (add_line)
				setYOffset (t-v);
			else
				scroll (0, cellHeight(1));
		}
	}
}

void MyTermout::appendChar (char c)
{

		
	QFontMetrics fm(font);
	int pos;
	char b[2];
	QString character;
	QString lastword;

	b[1] = 0;
	b[0] = c;
	character = QString (b);

  if (character == "\n") {
		newLine();
		updateCell (line.count()-2, 0, false);
		return;
		}
	if (fm.width(line.last()->text()) >= viewWidth()-/*fm.width("m")*/vscroll->width()) {
		pos = line.last()->text().findRev (' ');
	  lastword = line.last()->text().mid(pos, -1);
		line.last()->setText( line.last()->text().left (pos));
		newLine();
		updateCell (line.count()-2, 0, false);
	  line.last()->setText (lastword.mid (1, -1));
	}

	if (character == "\b") {                                                // Handle Backspace
    if (line.last()->text().length() != 0)
			line.last()->setText (line.last()->text().left (line.last()->text().length()-1));
		else {
			if (line.count() != 1) {
				line.removeLast();
				updateCell (line.count(), 0, false);
				}
			}
		}
	else {
		line.last()->setText (line.last()->text() + character);
		}
	updateCell (line.count()-1, 0, false);
}

void MyTermout::resizeEvent (QResizeEvent* e)
{
  QtTableView::resizeEvent (e);
	setCellWidth (width());
}

void MyTermout::appendString (char* text, bool signal)
{
	setAutoUpdate (false);
	unsigned int i;
	for (i=0;i<=strlen(text);++i) {
		appendChar (text[i]);
		}
	setAutoUpdate (true);
	if (signal)
		emit textAppended (text);
	repaint(false);
}

void MyTermout::appendString (QString text, bool signal)
{
	if (!text.isNull()) {
		char* s = strdup (text.latin1());
		appendString (s, signal);
		free (s);
	}
}

void MyTermout::setFont (QFont f)
{
	font = f;
	QFontMetrics fm (font);
	setCellHeight (fm.height());
	repaint(false);
}

void MyTermout::setNewLineColor (QColor col)
{
	bool newcolor = false;
	if (currentcol != col) newcolor = true;	
	currentcol=col;
	if ( newcolor ) appendChar('\n');
}

void MyTermout::clearAllMarks()
{
	unsigned int i;
	for (i=0;i<line.count();++i)
		line.at(i)->setMarked (false);
	repaint(false);
	firstline=-1;
	lastline=-1;
}

void MyTermout::mousePressEvent( QMouseEvent *e)
{
	int row;
	int len;
	QFontMetrics fm(font);
	if (e->button() == LeftButton) {
		row = findRow(e->pos().y());
		if (row != -1)
			len = fm.width(line.at(row)->text())+5;
		else
			len =-1;

		if ((row >= firstline) && (row <= lastline) && (len != -1) && (e->pos().x() < len)) {
	 		QDragObject *d = new QTextDrag( getMarkedText(), this );
     	d->dragCopy();
			}
		else {
			clearAllMarks();
    	marking = true;
    	mark_new = true;
    	markdirection = 0;
    	lastmarkline = -1;
			}
		}
	if (e->button() == MidButton) {
		if (QApplication::clipboard()->text().latin1() != NULL) {
			char* tmp = strdup (QApplication::clipboard()->text().latin1());
			appendString (tmp);
			free (tmp);
			}
		}
}

void MyTermout::mouseMoveEvent (QMouseEvent* e)
{
  int i,row;
  if (marking)
  {
     row = findRow(e->pos().y());
     if (row != lastmarkline)
     {
        lastmarkline = row;
        if (row != -1)
        {
           if (mark_new || firstline == -1)
           {
              firstline = row;
              lastline = row;
           }
            if (markdirection == 0)
              if (firstline <= row)
                 markdirection = MARKDIR_TOPDOWN;
              else
                 markdirection = MARKDIR_DOWNTOP;
            if (row < firstline)
              markdirection = MARKDIR_DOWNTOP;

           if (markdirection == MARKDIR_TOPDOWN)
           {
              // Gucken, ob gerade eine oder mehrere Zeilen wieder freigegeben
              // wurden.
              if (lastline > row)
              {
                 // Ja! Alles zwischen firstline (incl) und row(excl.) freigeben
                 for (i=row+1; i<=lastline; i++)
                 {
                    line.at(i)->setMarked( false );
                 }
                 lastline = row;
              }
               // Gucken, ob wir gerade ein paar Zeilen markiert haben
              if ((row > firstline) || mark_new)
              {
                 for (i=firstline; i<=row; i++)
                 {
                    line.at(i)->setMarked(true);
                 }
                 lastline = row;
              }
           }
            // Gucken, ob wir ganz unten mit unserer Markierung angelangt
           // sind. Wenn ja wird das ganze etwas heruntergescrollt
           if (row == lastRowVisible())
           {
              scrolltimer = new QTimer(this);
              connect(scrolltimer, SIGNAL(timeout()), SLOT(slotTimerUnten()));
              scrolltimer->start(MARKTIMER, true);
           }
           else
              if (scrolltimer != NULL)
                 if (markdirection == MARKDIR_TOPDOWN)
                    if (scrolltimer->isActive())
                       scrolltimer->stop();

           // Gucken, ob wir ganz oben mit unserer Markierung angelangt
           // sind. Wenn ja wird das ganze etwas heraufgescrollt
           if (row != 0)
              if (row == topCell())
              {
                 scrolltimer = new QTimer(this);
                 connect(scrolltimer, SIGNAL(timeout()), SLOT(slotTimerOben()));
                 scrolltimer->start(MARKTIMER, true);
              }
              else
                 if (scrolltimer != NULL)
                    if (markdirection == MARKDIR_DOWNTOP)
                       if (scrolltimer->isActive())
                          scrolltimer->stop();

           // Gucken, ob wir gerade ueber dem oberen Ende 'rausscrollen
           if (markdirection == MARKDIR_DOWNTOP)
           {
              // Oben soll was markiert werden
              if (row < firstline)
              {
                 for (i=row; i<firstline; i++)
                 {
                    line.at(i)->setMarked( true );
                 }
                 firstline = row;
              }
               // Wieder nach unten scrollen? -> alles obere "demarkieren"
              if (row > firstline)
               {
                  for (i=firstline; i<row; i++)
                  {
                     line.at(i)->setMarked( false );
                  }
                  firstline = row;
               }
            }

            if (firstline == lastline)
               markdirection = MARKDIR_TOPDOWN;

            mark_new = false;
         }
      }
   }

	 repaint(false);
}

void MyTermout::slotTimerOben()
{
	int row = topCell();

	if (row > 0)
	{
		setTopCell(topCell()-1);
		line.at(row)->setMarked( true );
		updateCell(row, 0, false);
		firstline = row;
  }

   if ((scrolltimer != NULL) && (row != 0))
      scrolltimer->start(MARKTIMER, true);
}

void MyTermout::slotTimerUnten()
{

	unsigned int row = lastRowVisible();

	if (row < line.count()-1)
	{
		setTopCell(topCell()+1);
		line.at(row)->setMarked( true );
		updateCell(row, 0, false);
		lastline = row;
	}

	if ((scrolltimer != NULL) && ((unsigned int)row < line.count()-1))
		scrolltimer->start(MARKTIMER, true);
}

void MyTermout::mouseReleaseEvent (QMouseEvent* e)
{
   if (e->button() == LeftButton)
   {
      marking = false;
      if (firstline > -1)
      {
         if (scrolltimer != NULL)
         {
            scrolltimer->stop();
            delete scrolltimer;
            scrolltimer = NULL;
         }
         QApplication::clipboard()->setText(getMarkedText());
      }
   }

}

void MyTermout::setEditEnabled (bool ed)
{
	if (ed) {
		setFocusPolicy (StrongFocus);
		setAcceptDrops (true);
	  cursoron=false;
		edited=true;
	}
	else {
		setFocusPolicy (NoFocus);
		setAcceptDrops (false);
		cursoron=false;
		edited=false;
	}

}

void MyTermout::slotCursorBlink()
{
    cursoron = !cursoron;
    updateCell( line.count()-1, 0, false );
}

void MyTermout::focusInEvent( QFocusEvent * )
{
	if ( !blinktimer->isActive() )
		blinktimer->start( QApplication::cursorFlashTime() / 2, FALSE );
	cursoron = TRUE;
	updateCell( line.count()-1, 0, FALSE );
}

void MyTermout::focusOutEvent ( QFocusEvent * )
{
	blinktimer->stop();
	if ( cursoron) {
		cursoron = false;
		updateCell( line.count()-1, 0, false );
		}
}


void MyTermout::keyPressEvent( QKeyEvent *e )
{
	if (edited) {
		if (e->key() == Key_Up) {
			setTopCell(topCell()-1);
			repaint (false);
			e->accept();
			return;
			}

		if (e->key() == Key_Down) {
			setTopCell(topCell()+1);
			repaint (false);
			e->accept();
			return;
			}

		int key = e->ascii();
			if (key == '\n' || key == '\r') {
				appendChar ('\n');
				emit keyPressed ('\n');
				e->accept();
				return;
				}

			if (key == '\b') {
				appendChar ('\b');
				emit keyPressed ('\b');
				e->accept();
				return;
        }

			if (key >= 31 && key <= 255) {
				appendChar (key);
				emit keyPressed (key);
				e->accept();
				return;
				}
	}
	e->ignore();
}

void MyTermout::dragEnterEvent(QDragEnterEvent* event)
{
  event->accept(QTextDrag::canDecode(event));
}
void MyTermout::dropEvent(QDropEvent* event)
{
	QString text;
	if ( QTextDrag::decode(event, text)) {
		char* tmp = strdup (text.latin1());
		appendString (tmp);
		free (tmp);
	}
		
}

void MyTermout::slotKey (char k)
{
	char b[2];
	b[1] = 0;
	b[0] = k;
	emit textAppended (b);
}

QString MyTermout::getMarkedText()
{
	int i;
	QString tmpstring;
	for (i=firstline;i<=lastline;i++)
	{
		tmpstring = tmpstring + line.at(i)->text();
		if (firstline != lastline)
			tmpstring = tmpstring + "\n";
	}
	return tmpstring;
}

void MyTermout::slotPageUp()
{
	int pos;
	if (rowYPos(lastRowVisible(), &pos))
		((QScrollBar *)vscroll)->setValue(yOffset()-pos);
}

void MyTermout::slotPageDown()
{
	int pos;
	if (rowYPos(lastRowVisible(), &pos))
		((QScrollBar *)vscroll)->setValue(yOffset()+pos);
}


