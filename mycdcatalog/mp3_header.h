/***************************************************************************
                          mp3_header.h  -  description
                             -------------------
    begin                : Sun Apr 28 2002
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

#ifndef MP3_HEADER_H
#define MP3_HEADER_H

#include "file.h"
#include <fstream>

#include "sqlmanager.h" // in file.h ?

/**Header of MPEG file.
 *@author Rory Vidal
 */

class MP3_Header {
 public: // Public methods
    MP3_Header();
    ~MP3_Header();

    /** Constructor with position assignement */
    MP3_Header(streampos);

    /** Constructor with position and hasV1Tag assignement */
    MP3_Header(streampos, bool);

    /** reads the header of an MP3 frame. (the first frame) */
    int readHeader(File *);

    /** MPEG 1.0 or 2.0 or 2.5 */
    float getMPEGType();

    /** Mode: Mono, Stereo, Joint Stereo , etc ... */
    QString getMode();

    /** string representation. */
    QString toString();

    /** print a MP3_Header. */
    void print();

    /** Keep a MP3_Header into DB. */
    int addRow(MysqlConnection *, int);

 private: // Private attributes
    /** Represents the end of ID3 tag and the start of MP3 data.
     * position into mpeg file.
     * Header found at: */
    streampos position;

    /** initial position. */
    streampos initPos;

    /** representation of a mpeg file. */
    ifstream * mfile;

    bool hasV1Tag;

    /** return the version number for MPEG. */
    unsigned short int version;

    /** Layer I, II or III. */
    unsigned int layer;

    /** IF (Error protection) TRUE */
    unsigned int error_protection;

    /** kbits / sec. */
    unsigned int bitrate;

    /** Frequency in Hz. */
    unsigned int samplerate;

    unsigned int padding;
    unsigned int extension;
    unsigned int mode;
    unsigned int mode_extention;

    /** True if copyrighted */
    unsigned int copyright;

    /** if true original. */
    unsigned int original;

    /** NONE if false. */
    unsigned int emphasis;

    unsigned int frameLength;

    /** Number of frames in file. */
    unsigned long totalframes;

    /** duration in seconds. */
    unsigned int duration;

 private: // Private methods
    /** finds a mpeg frame, for get their header info. */
    streamoff findFrame(streampos);

 public: // Public attributes
    /** Size in bytes, the mp3 file without tags (v1 and v2) */
    streampos filesize;
};

#endif
