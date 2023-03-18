/***************************************************************************
                          mp3_id3.cpp  -  description
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

#include "mp3_id3.h"

#include <qtextstream.h>
#include <iostream.h>
//#include <id3/misc_support.h>

/** genres table name. */
QString genres_table = "MP3Genres";

/** album table name. */
QString album_table = "MP3Album";

/** artist table name. */
QString artist_table = "MP3Artist";

/** Comment table */
QString comment_table = "MP3Comments";

/** mp3id3 table name. */
QString mp3id3_table = "MP3ID3";

/** URLS' table */
QString mp3urls_table = "MP3URLS";

MP3_ID3::MP3_ID3(){
  album=artist=composer=copyright="";
  encodedby=original_artist=title="";
  genre=track=year="";
  pCounter = nbfr = 0;
  has_id3_v1 = has_id3_v2 = false;
  urls=0;popularimeters=0;
  eobjects = 0;pictures =0; lyrics=0;
  fileType=length=mediaType="";
  owner_ufid = "";
  ufid = "";
	comments=0;
}

MP3_ID3::~MP3_ID3(){
}

/** Print to cout */
void MP3_ID3::print() {
  cout << toString() << endl;
}

/** string representation. */
QString MP3_ID3::toString(){
  QString str;
  QTextOStream(&str)
    << "Title: " << title
    << "\nArtist: " << artist
    << "\nAlbum: " << album
    << "\nTrack: " << track
    << "\nYear: " << year
    << "\nGenre: " << genre
    << "\nComment: " << getComment()
    << "\nComposer: " << composer
    << "\nOrig. Artist: " << original_artist
    << "\nCopyright: " << copyright
//    << "\nURL: " << url
    << "\nEncoded by: " << encodedby
    << (has_id3_v1 ? "\nID3v1 found" : "")
    << (has_id3_v2 ? "\nID3v2 found" : "");
  return str;
}

/** parse id3 tags. */
int MP3_ID3::getMP3Info(const char * filename){
  fileName = QString(filename);

  streampos pos = 0;
  try { // try
    ID3_Tag myTag;
    //cerr << "MP3_ID3::getMP3Info " << filename << endl;
    pos = myTag.Link ( filename , ID3TT_ALL );
    //    cout << "POS after tag: " <<  pos << endl;

    has_id3_v1 = myTag.HasV1Tag();
    has_id3_v2 = myTag.HasV2Tag();

    getInfo(myTag);
//  } catch(ID3_Error &err) {
//    cerr << err.GetErrorFile() << " (" << err.GetErrorLine() << "): "
//	 << err.GetErrorType() << ": " << err.GetErrorDesc() << endl;
	} catch (int err) {
    return -1;
  }
  return pos;
}

/** return a normalized genre. i.e. (120)Salsa -> 120. */
QString MP3_ID3::getGenre(){
  if (genre=="") return QString("NULL");

  QString res = genre;
  short int pos = res.find('(');

  if (pos != -1) {
    res = res.mid(pos+1);
    res.truncate(res.find(')'));
  }

  res = QString::number( res.toUShort() + 1 );
  return res;
}

/** reading all ID3 frames. */
int MP3_ID3::getInfo(const ID3_Tag &myTag){
  char * buf = new char[1024];

  nbfr = myTag.NumFrames();
  ID3_Tag::ConstIterator* iter = myTag.CreateIterator();
  const ID3_Frame* myFrame = NULL;

  while (NULL != (myFrame = iter->GetNext())) { // while

      switch (myFrame->GetID()) { //switch
      case ID3FID_ENCODEDBY:
	{myFrame->Field ( ID3FN_TEXT ).Get ( buf, 1024 );
	encodedby = QString(buf);
	break;}
      case ID3FID_COPYRIGHT:
	{myFrame->Field ( ID3FN_TEXT ).Get ( buf, 1024 );
	copyright = QString(buf);
	break;}
      case ID3FID_ORIGARTIST:
	{myFrame->Field ( ID3FN_TEXT ).Get ( buf, 1024 );
	original_artist = QString(buf);
	break;}
      case ID3FID_COMPOSER:
	{myFrame->Field ( ID3FN_TEXT ).Get ( buf, 1024 );
	composer = QString(buf);
	break;}
      case ID3FID_LEADARTIST:
	{myFrame->Field ( ID3FN_TEXT ).Get ( buf, 1024 );
	artist = QString(buf);
	break;}
      case ID3FID_TITLE:
	{myFrame->Field ( ID3FN_TEXT ).Get ( buf, 1024 );
	QString tmp = QString(buf);
	if ((title == "") && (tmp != ""))
		title = QString(buf);
	break;}
      case ID3FID_CONTENTTYPE:
	{myFrame->Field ( ID3FN_TEXT ).Get ( buf, 1024 );
	genre = QString(buf);
	break;}
      case ID3FID_ALBUM:
	{myFrame->Field ( ID3FN_TEXT ).Get ( buf, 1024 );
	album = QString(buf);
	break;}
      case ID3FID_YEAR:
	{myFrame->Field ( ID3FN_TEXT ).Get ( buf, 1024 );
	buf[4] = 0;
	year = QString(buf);
	break;}
      case ID3FID_TRACKNUM:
	{
	if ((track=="") || (track=="0")) {
		myFrame->Field ( ID3FN_TEXT ).Get ( buf, 1024 );
		track = QString(buf);
	}
	break;}
      case ID3FID_COMMENT:
	{
	char *sText = ID3_GetString(myFrame, ID3FN_TEXT);
//	char *sDesc = ID3_GetString(myFrame, ID3FN_DESCRIPTION);

	if (sText) {
		if (!comments) {
			comments = new QVector<QString> (32);
			QString comment = QString(sText).simplifyWhiteSpace();

			if ((comment == "") || (comment == " ")) {}
      else comments->insert(0, new QString(comment));

		} else {
			QString comment = QString(sText).simplifyWhiteSpace();

      if ((comment == "") || (comment == " ")) {}
      else {
  			bool found = false;
    		for (uint i=0; i<comments->count(); i++) {
//				cerr << "comment: <" << comment << "> , comments[" << i << "]: <" << *(comments->at(i)) <<">"<<endl;
		  		if (*(comments->at(i)) == comment) {
			  		found = true;
				  	break;
  				}
	  		}

  			if (!found)
//			if (comments->find(comment) == -1)
        comments->insert(comments->count(), new QString(comment));
//			else delete comment;
      } // else
		}
	}

	delete [] sText;
	break;}
      case ID3FID_SONGLEN:
	{
	 myFrame->Field ( ID3FN_TEXT ).Get ( buf, 1024 );
//   cout << "\nTLEN: " << buf << " length: " << length;
	 if ((length=="") || (length=="0")) {// cout << "length = \"\" or 0" << endl;
		length = QString(buf);
   }
	 break;
  }
      case ID3FID_MEDIATYPE:
	{myFrame->Field ( ID3FN_TEXT ).Get ( buf, 1024 );
	mediaType = QString(buf);
	break;}
      case ID3FID_FILETYPE:
	{myFrame->Field ( ID3FN_TEXT ).Get ( buf, 1024 );
	fileType = QString(buf);
	break;}
      case ID3FID_GENERALOBJECT:
	{
//    char *sMimeType = NULL;
//    ID3_Field* fld = myFrame->GetField(ID3FN_TEXT);
//    if (fld) {
//      size_t nText = fld->Size();
//      sMimeType = new char[nText + 1];
//      fld->Get(sMimeType, nText + 1);
//    }

	  char
            *sMimeType = ID3_GetString(myFrame, ID3FN_TEXT),
            *sDesc = ID3_GetString(myFrame, ID3FN_DESCRIPTION),
            *sFileName = ID3_GetString(myFrame, ID3FN_FILENAME);

    ID3_Field * myField = myFrame->GetField( ID3FN_DATA );

  size_t
            nDataSize = myField->Size();

	  if (!eobjects)
	    eobjects = new QVector<MP3GEOB>(16);

	  MP3GEOB * eobj = new MP3GEOB();
	  eobj->dataSize = nDataSize;
	  if (sDesc) eobj->description = QString(sDesc);
	  if (sFileName) eobj->fileName = QString(sFileName);
	  if (sMimeType) eobj->mimeType = QString(sMimeType);

	  char * data;
    myField->Get(data,nDataSize);
	  eobj->eobject = new string(data,nDataSize);

	  eobjects->insert(eobjects->count() , eobj);

          delete [] sMimeType;
          delete [] sDesc;
          delete [] sFileName;
          break;
        }
      case ID3FID_PLAYCOUNTER:
        {
					size_t pc = myFrame->Field(ID3FN_COUNTER).Get();
					if(pc)
	          pCounter = pc;
          break;
        }
      case ID3FID_POPULARIMETER:
        {
	  MP3POPM * popm = new MP3POPM();
          char *sEmail = ID3_GetString(myFrame, ID3FN_EMAIL);

	  if (sEmail) popm->email = QString(sEmail);
    popm->counter = myFrame->Field(ID3FN_COUNTER).Get();
	  popm->rating = myFrame->Field(ID3FN_RATING).Get();

	  if(!popularimeters)
	    popularimeters = new QVector<MP3POPM> (16);

	  popularimeters->insert(popularimeters->count() , popm);
          delete [] sEmail;
          break;
        }
        case ID3FID_WWWAUDIOFILE:
        case ID3FID_WWWARTIST:
        case ID3FID_WWWAUDIOSOURCE:
        case ID3FID_WWWCOMMERCIALINFO:
        case ID3FID_WWWCOPYRIGHT:
        case ID3FID_WWWPUBLISHER:
        case ID3FID_WWWPAYMENT:
        case ID3FID_WWWRADIOPAGE:
        case ID3FID_WWWUSER:
	{
	  QString * url = new QString("");
	  char *sURL = ID3_GetString(myFrame, ID3FN_URL);
		const char *sDesc = myFrame->GetDescription();

	  if (sURL) url = new QString(sURL);

		if(myFrame->GetID() == ID3FID_WWWUSER) {
			char *tmp = ID3_GetString(myFrame, ID3FN_DESCRIPTION);
			if (tmp) sDesc = tmp;
		}

		*url = *url + "|" + sDesc;

    if (*url == "|") {}
    else {
  	  if (!urls) urls = new QVector<QString> (32);
		
	    urls->insert(urls->count(), url);
    }

	  delete [] sURL;

	  break;
	}
      case ID3FID_UNIQUEFILEID:
        {
          char *sOwner = NULL;
          size_t nDataSize = myFrame->Field(ID3FN_DATA).Size();

	  if (nDataSize) {
      sOwner = ID3_GetString(myFrame, ID3FN_TEXT);
//      ID3_Field * myField = myFrame->GetField(ID3FN_TEXT);
//      if (myField) {
//        sOwner = new char[myField->Size()];
//        myField->Get ( sOwner, myField->Size() );
//      }

	    char *data = new char[nDataSize];
	    ufid = string(data,nDataSize);
	    if (sOwner) owner_ufid = QString(sOwner);
	  }
          delete [] sOwner;
          break;
        }
      case ID3FID_PICTURE:
        {
          char
            *sMimeType = ID3_GetString(myFrame, ID3FN_MIMETYPE),
            *sDesc     = ID3_GetString(myFrame, ID3FN_DESCRIPTION),
            *sFormat   = ID3_GetString(myFrame, ID3FN_IMAGEFORMAT);

        ID3_Field * myField = myFrame->GetField(ID3FN_DATA);

          size_t
            nPicType   = myFrame->Field(ID3FN_PICTURETYPE).Get(),
            nDataSize  = myField->Size();

	  if (nDataSize) {
	    MP3APIC * pic = new MP3APIC();
	    if (sMimeType) pic->mimeType = QString(sMimeType);
	    if (sDesc) pic->description = QString(sDesc);
	    if (sFormat) pic->format = QString(sFormat);
	    pic->picType = nPicType;
	    pic->picSize = nDataSize;

//	    const uchar* bin = myFrame->Field(ID3FN_DATA).GetBinary();
      uchar* bin = new uchar[nDataSize];
      myField->Get(bin,nDataSize);

	    pic->picture = new string((char *) bin, nDataSize);

	    if (!pictures) pictures = new QVector<MP3APIC> (16);

	    pictures->insert(pictures->count(), pic);
	  }

          delete [] sMimeType;
          delete [] sDesc;
          delete [] sFormat;
          break;
        }
      case ID3FID_UNSYNCEDLYRICS:
	{
	  char
	    *sText = ID3_GetString(myFrame, ID3FN_TEXT),
	    *sDesc = ID3_GetString(myFrame, ID3FN_DESCRIPTION),
            *sLang = ID3_GetString(myFrame, ID3FN_LANGUAGE);

	  if (sText) {
	    if (!lyrics) lyrics = new QVector<MP3Lyrics> (16);
	    MP3Lyrics * lyric = new MP3Lyrics();
	    lyric->lyrics = QString(sText);
	    lyric->description = QString(sDesc);
	    lyric->lang = QString(sLang);
	    lyrics->insert(lyrics->count(), lyric);
	  }

          delete [] sText;
          delete [] sDesc;
          delete [] sLang;
          break;
        }
      default:
	{cout << fileName << ":\n   ID3 Unsupported FrameID: " << myFrame->GetTextID()
	      << "\n   Description: " << myFrame->GetDescription() << endl;
	break;}
      }
    }

  delete buf;

  return 0;
}

/** Put into MP3UFID table an unique file identifier. */
int MP3_ID3::addRow(string ufid, QString owner_ufid){
  try {
    MysqlQuery query = curConn->query();
    ostrstream strbuf;
    strbuf.clear();

    strbuf << "INSERT INTO MP3UFID VALUES ("
	   << fileid << "," << norm( owner_ufid ) << ","
	   << "\"" << mysql_escape << ufid << "\""
	   << ");" << ends;

    //cout << strbuf.str() << endl;
    query.exec(strbuf.str());
  } catch (MysqlBadQuery er) { // handle any connection or
    // query errors that may come up
    ShowError::display("MP3_ID3::addRow(UFID):\n" + QString(er.what())
		       //			+ " " + eobj->toString());
		       );
    return -1;
  } catch (exception er) {
    ShowError::display("MP3_ID3::addRow(UFID):\n" + QString(er.what()));
    return -1;
  }

  return 0;	
}

/** Store an URL into DB. */
int MP3_ID3::addRow(const QString & url){
  try {
    MysqlQuery query = curConn->query();

	  int pos = url.find('|');
		QString a_url="",a_desc="";

		if (pos < 0) a_url = url;
		else {
			a_url = url.left(pos);
			a_desc = url.right(url.length()-pos-1);
		}

    query << "INSERT INTO " << mp3urls_table
			<< " VALUES ("
			<< fileid << ","
			<< norm( a_url ) << ","
			<< norm( a_desc )
			<< ");" << ends;

    query.execute();
  } catch (MysqlBadQuery er) { // handle any connection or
    // query errors that may come up
    ShowError::display("MP3_ID3::addRow(QString):\n" + QString(er.what()));
    return -1;
  } catch (exception er) {
    ShowError::display("MP3_ID3::addRow(QString):\n" + QString(er.what()));
    return -1;
  }

  return 0;	
}

/** Keep a MP3_ID3 into DB. */
int MP3_ID3::addRow(MysqlConnection *_curConn, int _fileid){
  fileid = _fileid;
  curConn = _curConn;

  try {
    uint artist_id = getOrCreate(artist, artist_table);
    uint album_id = getOrCreate(album, album_table);
    uint composer_id = getOrCreate(composer, artist_table);
    uint origartist_id = getOrCreate(original_artist, artist_table);
		uint comm_id = getOrCreate(getComment(), comment_table);

    MysqlQuery query = curConn->query();
    query << "INSERT INTO " << mp3id3_table
	  << " VALUES (" << fileid << ","
	  << norm(title) << ","
	  << norm(artist_id) << ","
	  << norm(album_id) << ","
	  << norm(year) << ","
	  << norm(track) << ","
	  << getGenre() << ","
	  << norm(comm_id) << ","
	  << (has_id3_v1 ? "\"Yes\"" : "\"No\"") << ","
	  << (has_id3_v2 ? "\"Yes\"" : "\"No\"") << ","
	  << nbfr << ","
	  << norm(composer_id) << ","
	  << norm(copyright) << ","
	  << norm(encodedby) << ","
	  << norm(origartist_id) << ","
	  << norm(length) << ","
	  << norm(mediaType) << ","
	  << norm(fileType) << ","
	  << norm(pCounter) <<  ");";

    //cout << query.preview() << endl;
    query.execute();

    // add MP3GEOB
    if (eobjects) {
      uint total = eobjects->count();
      for(uint i=0; i<total ; i++) {
	MP3GEOB * eobj = eobjects->at(i);
	eobj->addRow(curConn,fileid);
      }
    }

    // add MP3POPM
    if (popularimeters) {
      uint total = popularimeters->count();
      for(uint i=0; i<total ; i++) {
	MP3POPM * popm = popularimeters->at(i);
	popm->addRow(curConn,fileid);
      }
    }

    // add URLS
    if (urls) {
      uint total = urls->count();
      for(uint i=0; i<total ; i++) {
				QString * url = urls->at(i);
				addRow(*url);
      }
    }

    // add Universal file ID
    if (ufid != "") {
      addRow(ufid, owner_ufid);
    }

    // add Lyrics
    if (lyrics) {
      uint total = lyrics->count();
      for(uint i=0; i<total ; i++) {
	MP3Lyrics * lyric = lyrics->at(i);
	lyric->addRow(curConn,fileid);
      }
    }

    // add Pictures
    if (pictures) {
      uint total = pictures->count();
      for(uint i=0; i<total ; i++) {
	MP3APIC * picture = pictures->at(i);
	picture->addRow(curConn,fileid);
      }
    }

  } catch (MysqlBadQuery er) { // handle any connection or
    // query errors that may come up
    ShowError::display("MP3_ID3::addRow(MP3_ID3 *):\n" + QString(er.what()));
    return -1;
  } catch (exception er) {
    ShowError::display("MP3_ID3::addRow(MP3_ID3 *):\n" + QString(er.what()));
    return -1;
  }

  return 0;	
}

/** get or create a row with item into table. */
uint MP3_ID3::getOrCreate(QString item, QString table) {
  uint id;

  if (!item || (item == "")) return 0;

  try{
    MysqlQuery query = curConn->query();
    query << "SELECT * FROM " << table << " WHERE name = "
	  << norm(item) << ";";

    MysqlRes res = query.store();
    if (res.size() > 0) {
      Row row;
      MysqlRes::iterator i = res.begin();
      row = *i;
      id =  row["id"];
    }
    else {
      query << "INSERT INTO " << table << " VALUES (null, "
	    << norm(item) << ");";
      query.execute();
      id = curConn->insert_id();
    }
  } catch (MysqlBadQuery er) { // handle any connection or
    // query errors that may come up
    ShowError::display("MP3_ID3::getOrCreate(QString,QString):\n" + QString(er.what()));
    return 0;
  } catch (exception er) {
    ShowError::display("MP3_ID3::getOrCreate(QString,QString):\n" + QString(er.what()));
    return 0;
  }

  return id;
}

/** returns the comment. */
QString MP3_ID3::getComment(){
	QString * comment = new QString("");
	if (comments) {
		uint total = comments->count();
		if (total > 0) {
			uint i=0;
			do {
	 			comment = comments->at(i);
				i++;
			} while ((*comment == "") && (i<total));

			for (uint j=i; j<total; j++) {
				QString * tmp = comments->at(j);
				if (*tmp != "")
					*comment = *tmp + " , " + *comment;
			}
		}
	}

	return *comment;
}

/** replaces ID3_GetString from misc_support.h */
char * MP3_ID3::ID3_GetString(const ID3_Frame *frame, ID3_FieldID fldName)
{
  char * text = 0;
  if (frame)
  {
    ID3_Field* fld = frame->GetField(fldName);
    if (fld) {
      ID3_TextEnc enc = fld->GetEncoding();
      fld->SetEncoding(ID3TE_ASCII);
      size_t nText = fld->Size();
      text = new char[nText + 1];
      fld->Get(text, nText + 1);
      fld->SetEncoding(enc);
    }
  }
    return text;
}

