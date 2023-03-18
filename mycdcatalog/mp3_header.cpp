/***************************************************************************
                          mp3_header.cpp  -  description
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

#include "mp3_header.h"
#include <iostream.h>
#include <qtextstream.h>

extern "C" {
#include <stdio.h>
}

QString mp3header_table = "MP3Header";

const unsigned short int MPEG_HEADER_LENGTH = 4;
const unsigned short int ERR_DEF = 16;

//char *version_names[3] =
//{
//	"1",    /* 11 - MPEG 1 */
//	"2",    /* 10 - MPEG 2 */
//	"2.5"   /* 00 - MPEG 2.5 */
//};

char *emph_names[4] =
  {
    "None",
    "50/15 ms",
    "",	// reserved
    "CCIT J.17"
  };

char *layer_names[3] =
  {
    "I",    /* 11 - Layer 1 */
    "II",   /* 10 - Layer 2 */
    "III"   /* 01 - Layer 3 */
  };

char* mode_names[5] =
  {
    "Stereo",
    "Joint Stereo",    /* Stereo */
    "Dual Channel",    /* Stereo */
    "Single Channel",   /* Mono */
    "Multi Channel"
  };

int frequencies[3][4] =     // Heartz (Hz)
  {
    {44100, 48000, 32000, 0},    /* MPEG 1 */
    {22050, 24000, 16000, 0},    /* MPEG 2 */
    {11025, 12000,  8000, 0}     /* MPEG 2.5 */
  };

int bitrates[3][3][14] =
  {
    {		/* MPEG 1 */
      {32,64,96,128,160,192,224,256,288,320,352,384,416,448},    /* Layer 1 */
      {32,48,56, 64, 80, 96,112,128,160,192,224,256,320,384},    /* Layer 2 */
      {32,40,48, 56, 64, 80, 96,112,128,160,192,224,256,320}     /* Layer 3 */
    },
    {		/* MPEG 2 */
      {32,48,56,64,80,96,112,128,144,160,176,192,224,256},    /* Layer 1 */
      { 8,16,24,32,40,48, 56, 64, 80, 96,112,128,144,160},    /* Layer 2 */
      { 8,16,24,32,40,48, 56, 64, 80, 96,112,128,144,160}     /* Layer 3 */
    },
    {		/* MPEG 2.5 */
      {32,48,56,64,80,96,112,128,144,160,176,192,224,256},    /* Layer 1 */
      { 8,16,24,32,40,48, 56, 64, 80, 96,112,128,144,160},    /* Layer 2 */
      { 8,16,24,32,40,48, 56, 64, 80, 96,112,128,144,160}     /* Layer 3 */
    }
  };

MP3_Header::MP3_Header(){
  bitrate=copyright=duration=emphasis=error_protection=0;
  extension=filesize=frameLength=0;
  hasV1Tag = false;
  initPos=layer=mode=mode_extention=original=0;
  padding=position=samplerate=totalframes=version=0;
}

/** Constructor with initial position assignement */
MP3_Header::MP3_Header(streampos start) :initPos(start) {
  bitrate=copyright=duration=emphasis=error_protection=0;
  extension=filesize=frameLength=0;
  hasV1Tag = false;
  layer=mode=mode_extention=original=0;
  padding=position=samplerate=totalframes=version=0;	
}

/** Constructor with initial position and hasV1Tag assignement */
MP3_Header::MP3_Header(streampos start, bool v1) {
  initPos = start;
  hasV1Tag = v1;
  bitrate=copyright=duration=emphasis=error_protection=0;
  extension=filesize=frameLength=0;
  layer=mode=mode_extention=original=0;
  padding=position=samplerate=totalframes=version=0;
}

MP3_Header::~MP3_Header(){
}

/** reads the header of an MP3 frame. (the first frame) */
int MP3_Header::readHeader(File * fileinfo) { // readHeader()
  uchar * buffer = new uchar[MPEG_HEADER_LENGTH];

  mfile = new ifstream();
  mfile->open(fileinfo->filePath(), ios::in | ios::binary);

  if (!mfile->good()) {
    cerr << "Can't open file: " << fileinfo->filePath() << endl;
    mfile->close();
    return -1;
  }

  position = initPos;
  for(;;) { // for
    //    cerr << "Position: " << position << endl;
    if (
	(position = findFrame(position)) < 0
	) {
      cerr << "None frame found in file: " << fileinfo->filePath() << endl;
      mfile->close();
      return -1;
    }

    //cerr << "New Position: " << position << endl;
    mfile->seekg(position);
    if (mfile->tellg() != position) {
      cerr << "Can't go to: " << position << endl;
      mfile->close();
      return -1;
    }

    mfile->read(buffer, MPEG_HEADER_LENGTH);
    if (mfile->gcount() != MPEG_HEADER_LENGTH) {
      cerr << "Can't read " << MPEG_HEADER_LENGTH << " bytes, only: "
	   << mfile->gcount() << "bytes from file: " << fileinfo->filePath() << endl;
      mfile->close();
      return -1;
    }

    switch ((buffer[1]>>3 & 0x03)) { // switch
    case 3:	/* MPEG 1 */
      version = 0;
      break;
    case 2:	/* MPEG 2 */
      version = 1;
      break;
    case 1: /* Reserved */
      //					version = 3;
      break;
    case 0:	/* MPEG 2.5 */
      version = 2;
      break;
    default:
      version = ERR_DEF;
    } // switch

    //cerr << "a version found: " << version << endl;
    /* A protection against garbage which may give a invalid version */
    if (version > 2) {
      position++;
      continue;
    }

    layer            = 3-((buffer[1]>>1) & 0x03);
    error_protection = !(buffer[1] & 0x01);
    bitrate          = (buffer[2]>>4) & 0x0F;  // can't be 0, don't use 'free'
    bitrate          = bitrates[version][layer][bitrate-1];
    samplerate       = (buffer[2]>>2) & 0x03;
    samplerate       = frequencies[version][samplerate];
    padding          = (buffer[2]>>1) & 0x01;
    extension        = buffer[2] & 0x01;
    mode             = (buffer[3]>>6) & 0x03;
    mode_extention   = (buffer[3]>>4) & 0x03;
    copyright        = (buffer[3]>>3) & 0x01;
    original         = (buffer[3]>>2) & 0x01;
    emphasis         = (buffer[3]) & 0x03;

    //cerr << "a sample rate found: " << samplerate << endl;
    if (!bitrate || !samplerate) {
      position++;
      continue;
    }

    /* Calculate frameLength in bytes */	
    switch (layer) { // switch
    case 0: // FrameLengthInBytes = (12 * BitRate / SampleRate + Padding) * 4
      frameLength = (unsigned int) ( ( (12000.0*bitrate/double(samplerate) ) + padding) * 4.0 );
      break;
    case 1:
    case 2: // FrameLengthInBytes = 144 * BitRate / SampleRate + Padding
      frameLength = (unsigned int) ( (144000.0*bitrate/double(samplerate)) + padding );
      break;
    default:
      //			frameLength = 0; // reserved layer
      position++;
      continue;
    }

    if (!frameLength) { // without VBR ?
      position++;
      continue;
    }

    //cerr << "checking if new frame FrameLength: " << frameLength << endl;
    /* Check if at the end of this frame, begins an other frame */
    if (findFrame(position+frameLength) == position+frameLength)
      break;
    else position++;
  } // for

  filesize = fileinfo->size() - initPos; // without ID3 header if exists

  //	mfile->seekg(-128L, ios::end);
  //	mfile->read(buffer,4);
  //	buffer[3] = 0;
  //
  //	if (QString(buffer) == "TAG") {
  if (hasV1Tag) {
    filesize -= 128;	// without TAG at file end
    //		cout << "TAG: padding=" << padding << " Size: " << filesize << endl;
  }

  mfile->close();

  duration = (unsigned int) (((filesize * 8) / double(bitrate)) / 1000.0);
  // filesize in bytes

  if (frameLength!=0) { // && samplerate!= 0) {
    totalframes = long(filesize/ double(frameLength));
    /*		uint dur = uint (totalframes*(1152.0/(float)(version+1))/
		(float)samplerate);
		cout << "A duration: " << dur << endl;*/
  } else {
    cerr << "Warning!! frameLength=" << frameLength << " in file '"<< fileinfo->fileName()
	 <<"', can't determine totalframes!" << endl;
  }

  return 0;
}

/** finds a mpeg frame, for get their header info. */
streamoff MP3_Header::findFrame(streampos pos) {
  if (pos < 0) {
    cerr << "MP3_Header::findFrame: No good position: " << pos;
    return -1;
  }

  streamoff readsize;
  //	streampos curpos;
  //  cerr << "findFrame: first seek(" << pos << ")" << endl;
  mfile->seekg(pos);
  if (mfile->tellg() != pos) {
    cerr << "MP3_Header::findFrame: no good positioning" << endl;
    return -1;
  }

  uchar * buffer = new uchar[MPEG_HEADER_LENGTH];
  do { // do
    mfile->read(buffer,MPEG_HEADER_LENGTH);
    readsize = mfile->gcount();
    //		curpos = mfile->tellg();
    //    cout << "findFrame: second seek(" << 1-readsize << ")" << " curpos=" << curpos << endl;

    if (readsize < MPEG_HEADER_LENGTH) {
      //      cout << "MP3_Header::findFrame: Only " << readsize << " bytes read, "
      //				<< "InitPos " << pos << endl;
      //			cout << "InitPos: " << pos << " Pos: " << curpos << ", ";
      //			printf("%2X %2X %2X %2X",buffer[0], buffer[1], buffer[2], buffer[3]);
      //			cout << endl;
      return -1;
    } else {
      //			cout << "InitPos: " << pos << " Pos: " << curpos << ", ";
      //			printf("%2X %2X %2X %2X",buffer[0], buffer[1], buffer[2], buffer[3]);
      //			cout << endl;
      mfile->seekg(-3L, ios::cur);
    }

  } while(
	  ( (buffer[0]&0xFF)!=0xFF ) ||
	  ( ( (buffer[1]&0xE0)!=0xE0 ) && ( (buffer[1]&0xF0)!=0xF0 ) ) ||
	  ( (buffer[2]&0xF0)==0xF0 )
	  );

  return (mfile->tellg()-1);
}

float MP3_Header::getMPEGType(){
  switch (version) {
  case 0: return 1.0; break;
  case 1: return 2.0; break;
  case 2: return 2.5; break;
  default: return 0.0;
  }
}

/** Mode: Mono, Stereo, Joint Stereo , etc ... */
QString MP3_Header::getMode(){
  return QString(mode_names[mode]);
}

/** string representation. */
QString MP3_Header::toString(){
  QString str;
  QTextOStream(&str)
    << "Header found at: " << long(position)
    << "\nDuration: " << duration << " secs."
    << "\nMPEG " << getMPEGType()
    << " Layer " << layer_names[layer]
    << "\nBitrate : " << bitrate << " (kbits/s)"
    << "\nFrames: " << totalframes
    << "\nFrequency: " << samplerate
    << "\nMode: " << getMode()
    << "\nError protection: " << (error_protection ? "Yes" : "No")
    << "\nCopyrighted: " << (copyright ? "Yes" : "No")
    << "\nOriginal: " << (original ? "Yes" : "No")
    << "\nEmphasis: " << emph_names[emphasis];
  return str;
}

/** print a MP3_Header. */
void MP3_Header::print(){
  cout << toString() << endl;
}

/** Keep a MP3_Header into DB. */
int MP3_Header::addRow(MysqlConnection * curConn, int fileid){
  try {
    MysqlQuery query = curConn->query();
    query << "INSERT INTO " << mp3header_table << " VALUES ("
	  << fileid << ","
	  << long(position) << ","	// HeaderAt
	  << duration << ","	//Duration in seconds
	  << version+1 << "," // MPEG Version
	  << layer+1 << "," //Layer I II III
	  << bitrate << ",'"	// kbit/sec
	  << samplerate << "'," // Frequency
	  << norm(getMode()) << ","	// Stereo ., etc
	  << error_protection +1 << "," // CRC
	  << copyright+1 << ","
	  << original+1 << ","
	  << emphasis+1 << ","
	  << totalframes << ");";
    //cout << query.preview() << endl;
    query.execute();
  } catch (MysqlBadQuery er) { // handle any connection or
    // query errors that may come up
    ShowError::display("MP3_Header::addRow():\n" + QString(er.what()));
    return -1;
  } catch (exception er) {
    ShowError::display("MP3_Header::addRow():\n" + QString(er.what()));
    return -1;
  }

  return 0;
}
