/***************************************************************************
                          mytermout.h  -  description
                             -------------------
    begin                : Wed Feb 14 2001

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
// this widget is taken from Kpsk by Luc Langehegermann
// minor changes by Lars Schnake

#ifndef MYTERMOUT_H
#define MYTERMOUT_H

#include <kapp.h>
#include <qstring.h>
#include <qcolor.h>
#include "qttableview.h"
#include <qdragobject.h>
#include <qscrollbar.h>
#include <qfont.h>
#include <qwidget.h>
#include <qlist.h>
#include <qpainter.h>

#define MARKDIR_TOPDOWN 1
#define MARKDIR_DOWNTOP 2
#define MARKTIMER 150

/*
 * In this structure we hold an entire line - the text and the color
 * TextLine is used internel by MyTermout
 */

class TextLine {
	public:
		TextLine (QColor color) { c = color; s = "";m = false; }
		QString text() { return s; }
		QColor color() { return c; }
		bool marked() { return m; }
		void setText (QString text) { s = text; }
		void setMarked (bool mark) { m = mark; }
	private:
		QColor c;
		QString s;
		bool m;
		
};

class MyTermout : public QtTableView
{
  Q_OBJECT
public:
    MyTermout(QWidget* parent=0, const char *name=0);
    ~MyTermout();
  /**  */
  void appendChar (char c);
  /**  */
  void appendString (char* text, bool signal=true);
  /**  */
  void setFont (QFont f);
  /**  */
  void setNewLineColor (QColor col);
  /**  */
  void mouseMoveEvent (QMouseEvent* e);
  /**  */
  void setEditEnabled (bool ed);
  /**  */
  void appendString (QString text, bool signal=true);
private: // Private methods
  /** This draws an Line to the widget */
  void paintCell (QPainter* p, int row, int col);
  /**  */
  void newLine();
  /**  */
  void resizeEvent (QResizeEvent* e);
  /**  */
  void clearAllMarks();
  /**  */
  void mousePressEvent( QMouseEvent *e);
  /**  */
  void mouseReleaseEvent (QMouseEvent* e);
  /**  */
  void focusInEvent( QFocusEvent * );
  /**  */
  void focusOutEvent ( QFocusEvent * );
  /**  */
  void keyPressEvent( QKeyEvent *e );
  /**  */
  void dragEnterEvent(QDragEnterEvent* event) ;
  /**  */
  void dropEvent(QDropEvent* event);
  /**  */
  QString getMarkedText();
  /**  */
	QScrollBar* vscroll;
	QList<TextLine> line;
	unsigned int maxlines;
	QFont font;
	QColor currentcol;
  int firstline,lastline;
  int markdirection;
  int lastmarkline;
	int mark_new;
	int marking;
	QTimer* scrolltimer;
	QTimer* blinktimer;
	bool cursoron;
	bool edited;
private slots:
  /**  */
  void slotTimerOben();
  /**  */
  void slotTimerUnten();
  /**  */
  void slotCursorBlink();
  /**  */
  void slotKey (char k);
signals:
	void keyPressed (char k);
	void textAppended (char* text);
public slots: // Public slots
  /**  */
  void slotPageUp();
	void slotPageDown();
};

#endif
