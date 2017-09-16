/***************************************************************************
                          modem.h  -  description
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


#ifndef MODEM_H
#define MODEM_H

#include <qobject.h>

#include <qdir.h>

#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

#include <qsocketnotifier.h>

#include <config.h>

/**modem class for serial communication
  *@author Lars Schnake
  */

class Modem : public QObject  {
Q_OBJECT
public:
  Modem();
  ~Modem();

/** lock and open serial port with settings of ConfigData*/
  bool opentty();
/** unlock and close serial port */
  bool closetty();
/** write a char to port */
  bool writeChar(unsigned char);
/** write a char[] + Enter to port*/
  bool writeLine(const char *);

  bool dataMode() const { return data_mode; }
  void setDataMode(bool set) { data_mode = set; }
/** returns the last modem (error?)message */
  const QString modemMessage();

/** set up the connection to get notified if data was received */
  void notify(const QObject *, const char *);
/** disconnect the notify connection ( see notify )*/
  void stop();
/** send escape to change to command mode*/
  void send_esc();
/** simple read from port */
	int rs232_read(void *, int);
	int getFD();


public:
  static Modem *modem;

signals:
/** is emitted if data was received */
  void charWaiting(unsigned char);


public slots:

	/** notify if chars arriving from ptc */
  void startNotifier();
	/** stop the notifier */
  void stopNotifier();
	/** read from port */
  void readtty(int);

private:
  speed_t modemspeed();  // parse modem speed
  bool modem_is_locked;
  int modemfd;
  QSocketNotifier *sn;
  bool data_mode;
  QString errmsg;
  struct termios initial_tty;
  struct termios tty;
  unsigned char dataMask;
	bool lock_device();
  bool unlock_device();
	QString qdev;
};


#endif

