/***************************************************************************
                          update.cpp  -  description
                             -------------------
    begin                : Tue Mar 20 2001
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

#include "update.h"
#include <kdebug.h>
#include <kapp.h>
#include <qmessagebox.h>
#include <klocale.h>


Update::Update(QWidget *mywidget ) : QObject() {

updatewidget = mywidget;

}

Update::~Update(){
}


int Update::runUpdate(QString qsfilename )
{


   	char		Buffer[MAX_SECT_SIZE];

   	char		ch;
   	char		ManCode;
   	char		DevId;
   	FLASH		Flash;
   	unsigned long	FlashFree;
   	unsigned short	Sectors;
   	unsigned long	SectorsWritten = 0;
   	unsigned long	BytesRead;

   	int		hFile;
   	unsigned long	FileLength;

   	int		res;

   	FDTIME		FileStamp;
   	FDTIME		FlashStamp;


   	hFile = open((const char *)qsfilename.data(), O_RDONLY);

   	if(-1 == hFile) {

			QMessageBox::warning( updatewidget, "Kptc", i18n("ERROR: opening file : ") + qsfilename );	
   		//fprintf(stderr, "ERROR: opening file: %s\n", (const char *)qsfilename.data());
   		return -1;
   	}

   	lseek(hFile, 12, SEEK_SET);
   	read(hFile, &FileStamp, 4);

   	FileLength = lseek(hFile, 0, SEEK_END);
   	Modem::modem->writeLine("Q");
   	usleep(200);

   	Modem::modem->stopNotifier(); // close connection, skip data
   	Modem::modem->writeLine("UPDATE");
   	
   	readflush(Modem::modem->getFD()); /* read and ignore the UPDATE message */

   	Modem::modem->writeChar((char) 6 );	/* send ACK */

   	Modem::modem->rs232_read(&ManCode, 1);
   	Modem::modem->rs232_read(&DevId, 1);
   	Modem::modem->rs232_read(&FlashStamp, 4);

   	if(GetFlash(ManCode, DevId, &Flash) != 0) {
			QMessageBox::warning( updatewidget, "Kptc", i18n("ERROR: receiving Flash information !") );	
   		// fprintf(stderr, "ERROR: receiving Flash information!\n");
   		Modem::modem->send_esc();	/* send ESC */
   		close(hFile);
   		return -1;
  	}
  kdDebug() << "update::runupdate- manufaxturer, type: " << Flash.Manufacturer<<" / "<< Flash.Type <<endl;
  	//printf("Flash: %s - %s\n\n", Flash.Manufacturer, Flash.Type);

  	FlashFree = Flash.ulFlashSize - 16384 - Flash.usSectSize;

  	if(Flash.usSectSize == 0) {
			QMessageBox::warning( updatewidget, "Kptc", i18n("ERROR: wrong sector size !") );	
  		//fprintf(stderr, "ERROR: wrong sector size!\n");
  		Modem::modem->send_esc();	/* send ESC */
  		close(hFile);
  		return -1;
  	}

  	Sectors = FileLength / Flash.usSectSize;

  	if(FileLength % Flash.usSectSize) {
  		Sectors++;
  	}

  	if(FileLength > FlashFree) {
			QMessageBox::warning( updatewidget, "Kptc", i18n("ERROR: File too large !\nFile should not be longer than ") + FlashFree + i18n(" bytes.") );	
  		//fprintf(stderr, "ERROR: File too large!\n       File should not be longer than %ld bytes.\n", FlashFree);
  		Modem::modem->send_esc();	/* send ESC */
  		close(hFile);
  		return -1;
  	}
  	
  	if(FlashStamp.day == 0 || FlashStamp.month == 0 || (FlashStamp.day == 0x1f && FlashStamp.month == 0xf && FlashStamp.year == 0x7f)) {
      QMessageBox::warning( updatewidget, "Kptc", i18n("WARNING: Invalid Flash time stamp.\nPossibly no firmware installed.\n Update will proceed.") );	
  		//fprintf(stderr, "WARNING: Invalid Flash time stamp.\n         Possibly no firmware installed.\n\n");
  	}

  	if ( convtime(FileStamp) <= convtime(FlashStamp)) {

  		kdDebug() << "Update: same or newer time stamp"<<endl;


		switch( QMessageBox::warning( updatewidget, "Kptc", i18n("The current firmware has the same or a newer time stamp!\n"
                          "Do you whant to proceed or quit the update ?\n"),
                          i18n("Proceed"), i18n("Quit"), 0, 0, 1 )) {
		case 1: // Quit or Escape
      // exit
      Modem::modem->send_esc();	
  		close(hFile);
  		return -2;			
      break;
  }

  	}


  	Modem::modem->writeChar((char) 6);	/* send ACK */
  	
  	ch = (char) (Sectors >> 8);
  	Modem::modem->writeChar (ch);
  	ch = (char) Sectors;
  	Modem::modem->writeChar(ch);

  	Modem::modem->rs232_read(&ch, 1);

  	if (ch != ACK) {
			QMessageBox::warning( updatewidget, "Kptc", i18n("ERROR: Handshake failed !") );
  		//fprintf(stderr, "\a\aERROR: Handshake failed!\n");
  		Modem::modem->send_esc();	/* send ESC */
  		close(hFile);
  		return -1;
  	}



  	 QString text = QString(i18n("Writing %1 byte in %2 sectors.") .arg(FileLength).arg(Sectors));
		emit message(text);
		kapp->processEvents(); 	
  	lseek(hFile, 0, SEEK_SET);

  	do {
  		BytesRead = read(hFile, &Buffer, Flash.usSectSize);
  		if(BytesRead < Flash.usSectSize) {
  			memset(Buffer+BytesRead, 0, Flash.usSectSize-BytesRead);
  		}
  		write(Modem::modem->getFD(), &Buffer, Flash.usSectSize);
  		
  		SectorsWritten++;
  		
  		Modem::modem->rs232_read(&ch, 1);
  		
  		if (ch != ACK) {
        QMessageBox::warning( updatewidget, "Kptc", i18n("ERROR: Handshake failed !") );
  			//fprintf(stderr, "\a\aERROR: Handshake failed!\n");
  			Modem::modem->send_esc();	/* send ESC */
  			close(hFile);
  			return -1;
  		}

  		//sprintf(Buffer, "Written: %3ld%%\r", SectorsWritten * 100 / Sectors);
  		//write(STDOUT_FILENO, Buffer, strlen(Buffer));

  		emit progress((int) (SectorsWritten * 100 / Sectors));
			kapp->processEvents();
  		kdDebug() << "update:sectorsWritten:" << SectorsWritten <<" / sectors total:" << Sectors << endl;		
      kdDebug() << "update:progress:" << (SectorsWritten * 100 / Sectors) << endl;	
  		kdDebug() << "update:progress(int):" << (int) (SectorsWritten * 100 / Sectors) << endl;	


  	} while (BytesRead == Flash.usSectSize);

  	Modem::modem->writeLine("");

  	message(i18n("Update complete. Press Exit now."));

  	Modem::modem->startNotifier();
  	
  	close(hFile);

  	return 0;
		




	


}


int Update::GetFlash(char ManCode, char DevId, FLASH *Flash)
{
	int Result;
	switch((unsigned char)ManCode) {
		/* AMD Flash wird zwar erkannt aber f�r Programmierung nicht unterst�tzt */
		case 0x01:
			Flash->Manufacturer = "AMD";
			switch((unsigned char)DevId) {
				case 0xa4:
					Flash->Type = "Am29F040";
					Flash->usSectSize = 65535;
					Flash->ulFlashSize = 524288;
					Result = 0;
					break;
				default:
					Flash->Type = "UNKNOWN";
					Flash->usSectSize = 0;
					Flash->ulFlashSize = 0;
					Result = -1;
					break;
				}
				break;

		case 0x1f:
			Flash->Manufacturer = "Atmel";
			switch((unsigned char)DevId) {
				case 0x5d:
					Flash->Type = "AT29C512";
					Flash->usSectSize = 128;
					Flash->ulFlashSize = 65535;
					Result = 0;
					break;
				case 0xd5:
					Flash->Type = "AT29C010";
					Flash->usSectSize = 128;
					Flash->ulFlashSize = 131072;
					Result = 0;
					break;
				case 0xda:
					Flash->Type = "AT29C020";
					Flash->usSectSize = 256;
					Flash->ulFlashSize = 262144;
					Result = 0;
					break;
				case 0x5b:
					Flash->Type = "AT29C040";
					Flash->usSectSize = 512;
					Flash->ulFlashSize = 524288;
					Result = 0;
					break;
				case 0xa4:
					Flash->Type = "AT29C040A";
					Flash->usSectSize = 256;
					Flash->ulFlashSize = 524288;
					Result = 0;
					break;
				default:
					Flash->Type = "UNKNOWN";
					Flash->usSectSize = 0;
					Flash->ulFlashSize = 0;
					Result = -1;
					break;
				}
				break;

		default:
			Flash->Manufacturer = "INVALID";
			Flash->Type = "INVALID";
			Flash->usSectSize = 0;
			Flash->ulFlashSize = 0;
			Result = -1;
			break;
		}

	return Result;
}


time_t Update::convtime(FDTIME PTC_Time)
{
	struct tm	btime;

	btime.tm_sec = PTC_Time.twosecs * 2;
	btime.tm_min = PTC_Time.minutes;
	btime.tm_hour = PTC_Time.hours;
	btime.tm_mday = PTC_Time.day;
	btime.tm_mon = PTC_Time.month;
	btime.tm_year = PTC_Time.year + 80;
	btime.tm_wday = 0;
	btime.tm_yday = 0;
	btime.tm_isdst = 0;

	return mktime(&btime);
}


int Update::readflush(int handle)
{
	fd_set		set;
	struct timeval	timeout;
	int		Max;
	int		endloop;
	int		res;
	char		tmp;


	Max = 0;
	endloop = 0;
	do {
		timeout.tv_sec = 0;
		timeout.tv_usec = 100000; /* 0.1 seconds */

		FD_ZERO(&set);
		FD_SET(handle, &set);
		res = select(FD_SETSIZE, &set, NULL, NULL, &timeout);
		if (0 == res) {
			//fprintf(stderr, "ERROR: timed out!\n");
			endloop = 1;
		} else if (-1 == res) {
			perror("rs232_read select");
			//exit(10);
			return -1;
		} else {
			Max += read(handle, &tmp, 1);

		}
	} while (!endloop);

	return res;
}

