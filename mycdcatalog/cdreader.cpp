/***************************************************************************
                          cdreader.cpp  -  description
                             -------------------
    begin                : Mon Apr 22 2002
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

#include "cdreader.h"
#include "showerror.h"

#include <iostream.h>

extern "C" {
#include <sys/ioctl.h>	// ioctl
#include <linux/cdrom.h> // cdrom data

#include <sys/types.h> // open, lseek
#include <sys/stat.h>  // open
#include <fcntl.h>		// open

#include <unistd.h> // lseek, read
#include <linux/iso_fs.h>	// iso9660 data
}

CDReader::CDReader(){
}

CDReader::~CDReader(){
}

/** This method reads the CD information, it's the interface with the device and
the main method of the class. */
Volume * CDReader::readCDInfo(QString device){
	int drive;

	if (device) {

		drive = open(device, O_RDONLY | O_NONBLOCK);
		
		if (drive < 0) {
			ShowError::display("Error when opening the cdrom drive:\n"+device);
			return 0;
		}

		ioctl(drive, CDROMSTART);

		int status;

		if ((status = ioctl(drive, CDROM_DRIVE_STATUS)) < 0) {
			ShowError::display("Error when checking the cdrom drive status:\n"+device);
			return 0;
		}

		if (status != CDS_DISC_OK) {
			ShowError::display("No CDROM Disc into drive!\n"+device);
			return 0;
		}

		if ((status = ioctl(drive, CDROM_DISC_STATUS)) < 0) {
			ShowError::display("There was an error checking the cdrom disc status\n"+device);
			return 0;
		}

		Volume * vol = new Volume();

		switch (status) {
			case CDS_DATA_1: vol->status = 1; break;
			case CDS_DATA_2: vol->status = 2; break;
			case CDS_XA_2_1: vol->status = 3; break;
			case CDS_XA_2_2: vol->status = 4; break;
			case CDS_MIXED: vol->status = 5; break;
			default:
				ShowError::display("CDROM: "+device+ " isn't a data volume");
				return 0;
		}

/*
 		struct cdrom_multisession last_session;
		if (ioctl(drive, CDROMMULTISESSION, &last_session) < 0) {
			perror("There was an error taking last cdrom session address");
			return 0;
		}
		if (last_session.addr_format == CDROM_LBA) {
			cerr << "Last session address: " << last_session.addr.lba;
		}*/

		int toc_offset = 0;
		if (lseek(drive, ((off_t)(16 + toc_offset)) <<11, SEEK_SET) != -1) {
			iso_primary_descriptor ipd;

			if (read(drive, &ipd, sizeof(ipd)) != -1) {
			  iso_directory_record * idr;
			  idr = (iso_directory_record *) ipd.root_directory_record;

	/*
	 * High sierra:
	 *
	 *	DESC TYPE	== 1 (VD_SFS)	offset 8	len 1
	 *	STR ID		== "CDROM"	offset 9	len 5
	 *	STD_VER		== 1		offset 14	len 1
	 */
	if ((((char *)&ipd)[8] == 1) &&
	    (strncmp(&((char *)&ipd)[9], "CDROM", 5) == 0) &&
	    (((char *)&ipd)[14] == 1)) {
		ShowError::display("CD-ROM is in High Sierra format");
		return 0; //exit(0);
	}

	/*
	 * ISO 9660:
	 *
	 *	DESC TYPE	== 1 (VD_PVD)	offset 0	len 1
	 *	STR ID		== "CD001"	offset 1	len 5
	 *	STD_VER		== 1		offset 6	len 1
	 */
	if ((ipd.type[0] != ISO_VD_PRIMARY) ||
	    (strncmp(ipd.id, ISO_STANDARD_ID, sizeof(ipd.id)) != 0) ||
	    (ipd.version[0] != 1)) {
		ShowError::display("CD-ROM is NOT in ISO 9660 format");
		return 0; //exit(1);
	}

  vol->sys_id = render_chars(ipd.system_id, 32);
	vol->vol_id = render_chars(ipd.volume_id, 32);

//	delete render_chars(ipd.volume_set_id, 128);
	vol->pub_id = render_chars(ipd.publisher_id, 128);
	vol->preparer = render_chars(ipd.preparer_id, 128);
	vol->app_id = render_chars(ipd.application_id, 128);

//	delete render_chars(ipd.copyright_file_id, 37);
//	delete render_chars(ipd.abstract_file_id, 37);
//	delete render_chars(ipd.bibliographic_file_id, 37);

//	cout << "\nVolume set size is: " << isonum_723(ipd.volume_set_size) << endl;
//	cout << "Volume set sequence number is: " << isonum_723(ipd.volume_sequence_number) << endl;
//	cout << "Logical block size is: " << isonum_723(ipd.logical_block_size) << endl;
//	cout << "Volume size is: " << isonum_733(ipd.volume_space_size) << endl;

	vol->size = isonum_723(ipd.logical_block_size) * isonum_733(ipd.volume_space_size);

	close(drive);
	return vol;
			} else {
				ShowError::display("There was an error reading cdrom info");
				return 0;
			}
		} else {
			ShowError::display("There was an error seeking the cdrom drive");
			return 0;
		}
	}

}

char * CDReader::render_chars(char *s, int n)
{
	int	i,j;
	char *p;
	char *res;

	res =  new char[n];

	for (j=0;n > 0 && *s; n--,j++) {
		if (*s == ' ') {
			p = s;
			i = n;

			while (--i >= 0 && *p++ == ' ');

			if (i <= 0)	break;
		}

		res[j] = *s++;
//		cout << *s;
	}

	res[j] = 0;
//	cerr << "Reader::render_chars --> " << res << endl;
	return res;
}

int CDReader::isonum_721 (char *p)
{
	return ((p[0] & 0xff)
		| ((p[1] & 0xff) << 8));
}

int CDReader::isonum_723 (char *p)
{
	if (p[0] != p[3] || p[1] != p[2]) {
		cerr << "invalid format 7.2.3 number\n";
		return 0; //exit (1);
	}

	return (isonum_721 (p));
}

int CDReader::isonum_731 (char * p)
{
	return ((p[0] & 0xff)
		| ((p[1] & 0xff) << 8)
		| ((p[2] & 0xff) << 16)
		| ((p[3] & 0xff) << 24));
}

int CDReader::isonum_733 (char *p)
{
	return (isonum_731 (p));
}
