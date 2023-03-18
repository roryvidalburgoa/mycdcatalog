/*
 * file - find type of a file or files - main program.
 *
 * Copyright (c) Ian F. Darwin, 1987.
 * Written by Ian F. Darwin.
 *
 * This software is not subject to any license of the American Telephone
 * and Telegraph Company or of the Regents of the University of California.
 *
 * Permission is granted to anyone to use this software for any purpose on
 * any computer system, and to alter it and redistribute it freely, subject
 * to the following restrictions:
 *
 * 1. The author is not responsible for the consequences of use of this
 *    software, no matter how awful, even if they arise from flaws in it.
 *
 * 2. The origin of this software must not be misrepresented, either by
 *    explicit claim or by omission.  Since few users ever read sources,
 *    credits must appear in the documentation.
 *
 * 3. Altered versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.  Since few users
 *    ever read sources, credits must appear in the documentation.
 *
 * 4. This notice may not be removed or altered.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/param.h>	/* for MAXPATHLEN */
#include <sys/stat.h>
#include <fcntl.h>	/* for open() */
#ifdef RESTORE_TIME
# if (__COHERENT__ >= 0x420)
#  include <sys/utime.h>
# else
#  ifdef USE_UTIMES
#   include <sys/time.h>
#  else
#   include <utime.h>
#  endif
# endif
#endif
#ifdef HAVE_UNISTD_H
#include <unistd.h>	/* for read() */
#endif
#ifdef HAVE_LOCALE_H
#include <locale.h>
#endif

#include <netinet/in.h>		/* for byte swapping */

#include "file.h"
/*#include "patchlevel.h"*/

#ifndef	lint
FILE_RCSID("@(#)$Id: file.c,v 1.59 2001/07/23 00:02:32 christos Exp $")
#endif	/* lint */


#ifdef S_IFLNK
# define USAGE  "Usage: %s [-bciknsvzL] [-f namefile] [-m magicfiles] file...\n"
#else
# define USAGE  "Usage: %s [-bciknsvz] [-f namefile] [-m magicfiles] file...\n"
#endif

#ifndef MAGIC
# define MAGIC "/usr/share/magic"
#endif

#ifndef MAXPATHLEN
#define	MAXPATHLEN	512
#endif

extern char acode[32];
extern char adesc[32];


int			/* Misc globals				*/
	nmagic = 0;	/* number of valid magic[]s 		*/

struct  magic *magic;	/* array of magic entries		*/

const char *magicfile = 0;	/* where the magic is		*/
const char *default_magicfile = MAGIC;

char *progname;		/* used throughout 			*/
int lineno;		/* line number in the magic file	*/


#if 0
static int	byteconv4	__P((int, int, int));
static short	byteconv2	__P((int, int, int));
#endif



#if 0
/*
 * byteconv4
 * Input:
 *	from		4 byte quantity to convert
 *	same		whether to perform byte swapping
 *	big_endian	whether we are a big endian host
 */
static int
byteconv4(from, same, big_endian)
	int from;
	int same;
	int big_endian;
{
	if (same)
		return from;
	else if (big_endian) {		/* lsb -> msb conversion on msb */
		union {
			int i;
			char c[4];
		} retval, tmpval;

		tmpval.i = from;
		retval.c[0] = tmpval.c[3];
		retval.c[1] = tmpval.c[2];
		retval.c[2] = tmpval.c[1];
		retval.c[3] = tmpval.c[0];

		return retval.i;
	}
	else
		return ntohl(from);	/* msb -> lsb conversion on lsb */
}

/*
 * byteconv2
 * Same as byteconv4, but for shorts
 */
static short
byteconv2(from, same, big_endian)
	int from;
	int same;
	int big_endian;
{
	if (same)
		return from;
	else if (big_endian) {		/* lsb -> msb conversion on msb */
		union {
			short s;
			char c[2];
		} retval, tmpval;

		tmpval.s = (short) from;
		retval.c[0] = tmpval.c[1];
		retval.c[1] = tmpval.c[0];

		return retval.s;
	}
	else
		return ntohs(from);	/* msb -> lsb conversion on lsb */
}
#endif

/*
 * process - process input file
 */
int process(inname, wid)
	const char	*inname; //filename
	int wid;						//strlen(filename)
{
	int	fd = 0;
	unsigned char	buf[HOWMANY+1];	/* one extra for terminating '\0' */
	int nbytes = 0;	/* number of bytes read from a datafile */
	char match = '\0';

	if (inname && (wid>0)) {
		if ((fd = open(inname, O_RDONLY | O_NONBLOCK)) < 0) { // change non block if not necessary
			fprintf(stderr, "open failes (%s).\n", strerror(errno));
			fprintf(stderr, "file: (%s).\n", inname);
			return -1;
		}

	/*
	 * try looking at the first HOWMANY bytes
	 */
	if ((nbytes = read(fd, (char *)buf, HOWMANY)) == -1) {
		fprintf(stderr, "read failed (%s).\n", strerror(errno));
		fprintf(stderr, "file: (%s).\n", inname);
		sprintf(acode, "unreadable");
		sprintf(adesc, "input/output error");
		(void) close(fd);
		return -1;
		/*NOTREACHED*/
	}

	if (nbytes == 0) {
		sprintf(acode, "empty");
		sprintf(adesc, "zero size");
		(void) close(fd);
		return 0;
	}
	else {
		buf[nbytes++] = '\0';	/* null-terminate it */
		match = tryit(buf, nbytes);
	}

	(void) close(fd);
	} else return -1;

	return 0;
}


int
tryit(buf, nb)
	unsigned char *buf;
	int nb;
{

	/* try tests in /etc/magic (or surrogate magic file) */
	if (softmagic(buf, nb))
		return 's';

	/* try known keywords, check whether it is ASCII */
	if (ascmagic(buf, nb))
		return 'a';

	/* abandon hope, all ye who remain here */
	sprintf(acode , "data");
	sprintf(adesc, "Unknown");
	return '\0';
}
