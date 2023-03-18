/***************************************************************************
                          mp3_id3.h  -  description
                             -------------------
    begin                : Sat Apr 27 2002
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

#ifndef MP3_ID3_H
#define MP3_ID3_H

#include <qstring.h>
#include <qvector.h>

#include "mp3geob.h"
#include "mp3popm.h"
#include "mp3apic.h"
#include "mp3lyrics.h"

#undef Field
#include <id3/tag.h>

/**ID3 representation of a mp3 id3v1 or id3v2
 *@author Rory Vidal
 */

class MP3_ID3 {
public: 
    MP3_ID3();
    ~MP3_ID3();

    /** Printing to cout. */
    void print();

    /** string representation. */
    QString toString(void);

    /** parse id3 tags. */
    int getMP3Info(const char *);

    /** return a normalized genre. i.e. (120)Salsa -> 120. */
    QString getGenre();

    /** Keep a MP3_ID3 into DB. */
    int addRow(MysqlConnection *, int);
  /** replaces ID3_GetString from misc_support.h */
    char * ID3_GetString(const ID3_Frame *, ID3_FieldID);

 private: // Private methods
    /** reading all ID3 frames. */
    int getInfo(const ID3_Tag &);

    /** Store a Comercial Info into DB. */
    int addRow(const QString &);

    /** Store UFID frame */
    int addRow(string ufid, QString owner_ufid);

    /** get or create a row with item into table. */
    uint getOrCreate(QString , QString);
  /** returns the comment. */
  QString getComment();

 public: // Public attributes
    /** if exits tag v1 */
    bool has_id3_v1;

    /** if exits tag v2 */
    bool has_id3_v2;

    /** Number of frames found. */
    size_t nbfr;

 private: // Private attributes

    /** track number, position in set */
    QString track;

    /** album/movie/show title */
    QString album;

    /** Lead performer(s)/Soloist(s) */
    QString artist;

    /** Title/songname/content description */
    QString title;

    /** Year */
    QString year;

    /** Comments */
    QVector<QString> * comments;

    /** MP3 encoded by: . */
    QString encodedby;

    /** MP3 copyrighted by: . */
    QString copyright;
    
    /** Orig Artist */
    QString original_artist;

    /** composer of title. */
    QString composer;
    
    /** Length in milliseconds. It's a string. */
    QString length;

    /** The 'Media type' frame describes from which media the sound originated. */
    QString mediaType;

    /** The 'File type' frame indicates which type of audio this tag defines. */
    QString fileType;

    /** Encapsulated objects <binary data> in a ID3 tag. */
    QVector<MP3GEOB> * eobjects;

    /** Popularimeters in a ID3 tag. */
    QVector<MP3POPM> * popularimeters;

    /** URLS:
// WCOM  WCM  ID3FID_WWWCOMMERCIALINFO Commercial information
// WCOP  WCM  ID3FID_WWWCOPYRIGHT      Copyright/Legal infromation
// WOAF  WCP  ID3FID_WWWAUDIOFILE      Official audio file webpage
// WOAR  WAF  ID3FID_WWWARTIST         Official artist/performer webpage
// WOAS  WAR  ID3FID_WWWAUDIOSOURCE    Official audio source webpage
// WORS  WAS  ID3FID_WWWRADIOPAGE      Official internet radio station homepage
// WPAY  WRA  ID3FID_WWWPAYMENT        Payment
// WPUB  WPY  ID3FID_WWWPUBLISHER      Official publisher webpage
// WXXX  WXX  ID3FID_WWWUSER           User defined URL link
*/
    QVector<QString> * urls;

    /** This is simply a counter of the number of times a file has been played. */
    size_t pCounter;

    /** <Header for 'Unique file identifier', ID: "UFID"> 
     * Owner identifier <text string> $00 */
    QString owner_ufid;

    /** <Header for 'Unique file identifier', ID: "UFID">
     * Identifier <up to 64 bytes binary data> */
    string ufid;

    /** This frame contains a picture directly related to the audio file.  */
    QVector<MP3APIC> * pictures;
    
    /** This frame contains the lyrics of the song or a text transcription of other vocal
     * activities. */
    QVector<MP3Lyrics> * lyrics;

    /** Current MySQL connection. */
    MysqlConnection* curConn;

    /** genre/content type */
    QString genre;

    /** current filename. */
    QString fileName;

    /** DB File ID  */
    int fileid;
};

#endif
