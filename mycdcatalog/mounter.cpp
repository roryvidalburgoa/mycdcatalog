/***************************************************************************
                            -  description
                             -------------------
    begin                : Fri Apr 12 16:37:10 CEST 2002
    copyright            : (C) 2002 by Rory Vidal
    email                : roryvidal@yahoo.fr
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "mounter.h"
#include "showerror.h"

#include <iostream.h>

extern "C" {
#include <sys/types.h>	// open
#include <sys/stat.h>	// open
#include <fcntl.h>	// open
#include <sys/ioctl.h>	//ioctl

#include <sys/mount.h> // mount , umount
#include <errno.h>	// error number
#include <linux/cdrom.h>	// cdrom data
}

//bool Mounter::mounted = false;

int Mounter::tomount ( QString mntpoint, QString device ) {
	if (mntpoint && device) ;
	else return -1;

/*	if (Mounter::mounted) {
		ShowError::display("mount: CDROM already mounted");
		return -1;
	}*/

	cout << "Mounting device: " << device << " to directory: " << mntpoint << endl;
	if (mount (device,mntpoint,"iso9660",MS_RDONLY,NULL) < 0) {
		QString errmsg = "mount -t iso9660 " + device + " " + mntpoint + "\nError mounting device";

		if (errno == EBUSY) {
			errmsg +=  "\nCDROM already mounted, or mount point in use";
			ShowError::display(errmsg);
		} else {
			ShowError::display(errmsg);
			return -1;
		}
	}

//	Mounter::mounted = true;
	return 0;
}

int Mounter::tounmount ( QString mntpoint ) {
	if (!mntpoint) return -1;

/*	if (!Mounter::mounted) {
		ShowError::display("umount: CDROM not mounted");
		return -1;
	}*/

	cout << "Unmounting directory: " << mntpoint << endl;
	if (umount (mntpoint) < 0) {
		QString errmsg = "Unmount \"" + mntpoint + "\"\nError unmounting device";

		if (errno == EBUSY)
			errmsg += "\nCDROM in use";

		ShowError::display(errmsg);
		return -1;
	}

//	Mounter::mounted = false;
	return 0;
}

int Mounter::toeject ( QString device ){
	if (!device) return -1;

	cout << "Ejecting device: " << device << endl;
	int drive = open(device, O_RDONLY | O_NONBLOCK);
	if (drive < 0) {
		ShowError::display("Error opening: \"" + device + "\"");
		return -1;
	}

	if (ioctl(drive, CDROMEJECT ) < 0) {
		ShowError::display("Error ejecting device: \"" + device + "\"");
		return -1;
	}

	return 0;
}
