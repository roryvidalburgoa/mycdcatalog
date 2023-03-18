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

#include "sqlmanager.h"

#include <qdatetime.h>
#include <qtextstream.h>

#include <strstream.h>
#include <iostream>

//#include <iomanip>
//#include <vector>
//#include <custom.hh>

QString SQLManager::datetimes_table = "DateTimes";
QString SQLManager::extension_table = "Extension";

/** Constructor */
SQLManager::SQLManager(){
	last_vol_id = 0;
}

/** Destructor */
SQLManager::~SQLManager(){
	con = 0;
}

/** Make a connection to a mysql unix socket. */
int SQLManager::connect (const char * db, const char * socket , const char * user,
 const char * passwd){
//	cerr << "connect (db,user,passwd,socket)" << endl;
//	cerr << socket << endl;
	return real_connect (db,user,passwd,socket,0,0);
}

/** Make a connection to a mysql server:port. */
int SQLManager::connect(const char *db,const char *server,
	unsigned short int port,const char *user,const char *passwd){
//	cerr << "connect (db,user,passwd,0,server,port)" << endl;
//	cerr << server << ":" << port << endl;
	return real_connect (db,user,passwd,0,server,port);
}

/* real connection */
int SQLManager::real_connect (const char * db, const char * user,
	 const char * passwd, const char * socket,
	 const char * server, unsigned int port) {

	try {
		con = new MysqlConnection(db,server,user,passwd,port,0,60,true,socket,0);
  } catch (MysqlBadQuery er) { // handle any connection or
                          // query errors that may come up
#ifdef USE_STANDARD_EXCEPTION
    ShowError::display("SQLManager::real_connect() :\n" + QString(er.what()));
#else
		ShowError::display("SQLManager::real_connect() :\n" + QString(er.error));
#endif
    return -1;
#ifdef USE_STANDARD_EXCEPTION
  } catch (exception er) {
    ShowError::display("SQLManager::real_connect() :\n" + QString(er.what()));
    return -1;
#endif
  }

	return 0;
}

int SQLManager::addRow (Volume * vol){
  try {
		MysqlQuery query = con->query();
		query << "SELECT * FROM " << Volume::table_name << " WHERE vol_id=\""
			<< vol->vol_id << "\" AND size=" << vol->size << ";";

//cout << query.preview() << endl;

		MysqlRes res = query.store();

		if (res.size() > 0) {
			QString str;
			QTextOStream * qts = new QTextOStream(&str);
			*qts << "This CDROM exists in DB:\nID: " << vol->vol_id
				  << "\nSize: " << vol->size / 1048576.0 << " Mb." << endl;

			Row row = *(res.begin());
			if (QString((const char *)row["complete"]) == "Yes")
				*qts << "CDROM complete!";
			else {
				uint cd_id = uint(row["id"]);
				delete_volume(cd_id);
				*qts << "CDROM incomplete then deleted!";
			}

			throw MysqlBadQuery(str.latin1());
		}
    else {
			query << "INSERT INTO " << Volume::table_name
				<< " VALUES (NULL,"
				<< norm(vol->vol_id) << ","
				<< norm(vol->sys_id) << ","
				<< norm(vol->app_id) << ","
				<< vol->size << ","
        << "NULL, NULL , NULL , NULL , NULL ,"
				<< vol->status << ",'No');" ;
//cout << query.preview() << endl;
			query.execute();
			last_vol_id = vol->mysql_id = con->insert_id();
		}

	} catch (MysqlBadQuery er) { // handle any connection or
                          // query errors that may come up
#ifdef USE_STANDARD_EXCEPTION
    ShowError::display("SQLManager::addRow(Volume*) :\n" + QString(er.what()));
#else
    ShowError::display("SQLManager::addRow(Volume*) :\n" + QString(er.error));
#endif
    return -1;
  } catch (MysqlBadConversion er) { // handle bad conversions
#ifdef USE_STANDARD_EXCEPTION
		ShowError::display("SQLManager::addRow(Volume*) :\n" + QString(er.what()) + "\"."
         + " retrieved data size: " + er.retrieved
         + " actual data size: " + er.actual_size);
#else
    ShowError::display("SQLManager::addRow(Volume*) :\nTried to convert \"" +
			er.data + "\" to a \"" + er.type_name + "\".");
#endif
    return -1;
#ifdef USE_STANDARD_EXCEPTION
  } catch (exception er) {
    ShowError::display("SQLManager::addRow(Volume*) :\n" + QString(er.what()));
    return -1;
#endif
  }

	return 0;
}

int SQLManager::addRow (Directory * dir){
//	cerr << "addRow(Directory*): " << dir->filePath() << endl;
  try {
		int id_lm = getOrCreate(dir->lastModified());
		int id_a = getOrCreate(dir->lastRead());

		MysqlQuery query = con->query();

		query << "INSERT INTO " << Directory::table_name
			<< " VALUES (NULL,"
			<< norm(dir->filePath()) << ","
			<< id_lm << ","
			<< id_a << ","
			<< dir->NbDirFiles << ","
			<< dir->readable +1 << ","
			<< dir->parent_id << ","
			<< last_vol_id << ");" ;

			query.execute();
			dir->id = con->insert_id();

	} catch (MysqlBadQuery er) { // handle any connection or
                          // query errors that may come up
#ifdef USE_STANDARD_EXCEPTION
    ShowError::display("SQLManager::addRow(Directory *):\n" + QString(er.what()));
#else
    ShowError::display("SQLManager::addRow(Directory *):\n" + QString(er.error));
#endif
    return -1;
  } catch (MysqlBadConversion er) { // handle bad conversions
#ifdef USE_STANDARD_EXCEPTION
		ShowError::display("SQLManager::addRow(Directory *): " + QString(er.what()) + "\"."
         + "retrieved data size: " + er.retrieved
         + " actual data size: " + er.actual_size);
#else
    ShowError::display("SQLManager::addRow(Directory *):\nTried to convert \"" +
			er.data + "\" to a \"" + er.type_name + "\".");
#endif
    return -1;
#ifdef USE_STANDARD_EXCEPTION
  } catch (exception er) {
    ShowError::display("SQLManager::addRow(Directory *):\n" + QString(er.what()));
    return -1;
#endif
  }

	return 0;
}

int SQLManager::addRow (File * file){
//	cerr << "addRow(File*)" << file->filePath() << endl;
  try {
		int id_lm = getOrCreate(file->lastModified());
		int id_a = getOrCreate(file->lastRead());
		int id_type = getOrCreate(file->filetype);
		int id_ext = getOrCreate(file->filetype->extension);

		MysqlQuery query = con->query();
		query << "INSERT INTO " << File::table_name
			<< " VALUES (NULL, "
			<< norm(file->fileName()) << ","
			<< id_lm << ","
			<< id_a << ","
			<< file->size() << ","
			<< id_type << ","
			<< id_ext << ","
			<< file->readable +1<< ","
			<< file->parent_id << ","
			<< last_vol_id << ");" ;

			query.execute();
      file->id = con->insert_id();

	} catch (MysqlBadQuery er) { // handle any connection or
                          // query errors that may come up
#ifdef USE_STANDARD_EXCEPTION
    ShowError::display("SQLManager::addRow(File *):\n" + QString(er.what()));
#else
    ShowError::display("SQLManager::addRow(File *):\n" + QString(er.error));
#endif
    return -1;
  } catch (MysqlBadConversion er) { // handle bad conversions
#ifdef USE_STANDARD_EXCEPTION
		ShowError::display("SQLManager::addRow(File *):\n" + QString(er.what()) + "\"."
         + "retrieved data size: " + er.retrieved
         + " actual data size: " + er.actual_size);
#else
    ShowError::display("SQLManager::addRow(File *):\nTried to convert \"" +
			er.data + "\" to a \"" + er.type_name + "\".");
#endif
    return -1;
#ifdef USE_STANDARD_EXCEPTION
  } catch (exception er) {
    ShowError::display("SQLManager::addRow(File *):\n" + QString(er.what()));
    return -1;
#endif
  }

	return 0;
}

void SQLManager::close (  ){
	delete con;
}

/** updates a volume */
int SQLManager::update(Volume * vol){
  try {
		MysqlQuery query = con->query();
		query << "UPDATE " << Volume::table_name
			<< " SET nbdirs="	<< vol->nbDirs
			<< ", nbfiles=" << vol->nbFiles
      << ", unread_dirs=" << vol->unreadable_dirs
			<< ", unread_files=" << vol->unreadable_dirfiles - vol->unreadable_dirs
			<< ", complete=" << vol->complete +1
			<< ", filessize=" << vol->filesSize
			<< " WHERE id=" << vol->mysql_id;

		query.execute();

} catch (MysqlBadQuery er) { // handle any connection or
                          // query errors that may come up
#ifdef USE_STANDARD_EXCEPTION
    ShowError::display("SQLManager::update(Volume *):\n" + QString(er.what()));
#else
    ShowError::display("SQLManager::update(Volume *):\n" + QString(er.error));
#endif
    return -1;
  } catch (MysqlBadConversion er) { // handle bad conversions
#ifdef USE_STANDARD_EXCEPTION
		ShowError::display("SQLManager::update(Volume *):\n" + QString(er.what()) + "\"."
         + "retrieved data size: " + er.retrieved + " actual data size: " + er.actual_size);
#else
    ShowError::display("SQLManager::update(Volume *):\nTried to convert \"" + er.data +
			"\" to a \"" + er.type_name + "\".");
#endif
    return -1;
#ifdef USE_STANDARD_EXCEPTION
  } catch (exception er) {
    ShowError::display("SQLManager::update(Volume *):\n" + QString(er.what()));
    return -1;
#endif
  }

	return 0;
}

/** Converts from a QDateTime to a the mysql datetime format */
QString SQLManager::datetime(const QDateTime & qdt){
	QTime time = qdt.time();
	QDate date = qdt.date();
	QString str;
  QTextOStream(&str) << date.year() << "-" << date.month() << "-"
		<< date.day() << " " << time.toString();
	return str;
}

/** get or create a file type entry */
int SQLManager::getOrCreate(FileType * ft){
	int id;
	try{
		MysqlQuery query = con->query();
		query << "SELECT * FROM " << FileType::types_table << " WHERE code ="
			<< norm(ft->code) << " AND description =" << norm(ft->description) << ";";

		MysqlRes res = query.store();
		if (res.size() > 0) {
			Row row;
			MysqlRes::iterator i = res.begin();
			row = *i;
			id =  row["id"];
		}
		else {
			query << "INSERT INTO " << FileType::types_table << " VALUES (NULL,"
				<< norm(ft->code) << "," << norm(ft->description) << ");";
			query.execute();
			id = con->insert_id();
		}
	} catch (MysqlBadQuery er) {
    ShowError::display("SQLManager::getOrCreate(FileType *):\n" + QString(er.what()));
    return -1;
  } catch (exception er) {
    ShowError::display("SQLManager::getOrCreate(FileType *):\n" + QString(er.what()));
//cerr << "code: <" << ft->code << "> desc: <" << ft->description << ">" << endl;
    return -1;
 }
	return id;
}

/** get or create a extension entry */
int SQLManager::getOrCreate(QString ext){
	int id;

	try{
		MysqlQuery query = con->query();
		query << "SELECT * FROM " << extension_table << " WHERE name='"
			<< ext << "';";
//cerr << query.preview() << endl;
		MysqlRes res = query.store();
		if (res.size() > 0) {
			Row row;
			MysqlRes::iterator i = res.begin();
			row = *i;
			id =  row["id"];
		}
		else {
			query << "INSERT INTO " << extension_table << " VALUES (NULL,'"
				<< ext << "');";
//cerr << query.preview() << endl;
			query.execute();
			id = con->insert_id();
		}
	} catch (MysqlBadQuery er) {
    ShowError::display("SQLManager::getOrCreate(QString):\n" + QString(er.what()));
    return -1;
#ifdef USE_STANDARD_EXCEPTION
  } catch (exception er) {
    ShowError::display("SQLManager::getOrCreate(QString):\n" + QString(er.what()));
    return -1;
#endif
 }
	return id;
}

/** Get or create an access or last modified date time. */
int SQLManager::getOrCreate (QDateTime dt){
	int id;
	QString adatetime = datetime(dt);
try {
	MysqlQuery query = con->query();

	query << "SELECT * FROM " << datetimes_table << " WHERE dt = \""
		<< adatetime << "\";";

	MysqlRes res = query.store();

	if (res.size() > 0) {
		Row row;
		MysqlRes::iterator i = res.begin();
		row = *i;
		
		id =  row["id"];
	}
	else {
		query << "INSERT INTO " << datetimes_table
			<< " VALUES (NULL,"
			<< norm(adatetime) << ");";
		query.execute();
		id = con->insert_id();
	}

	} catch (MysqlBadQuery er) {
    ShowError::display("SQLManager::getOrCreate(QDateTime):\n" + QString(er.what()));
    return -1;
#ifdef USE_STANDARD_EXCEPTION
  } catch (exception er) {
    ShowError::display("SQLManager::getOrCreate(QDateTime):\n" + QString(er.what()));
    return -1;
#endif
 }
	return id;
}

/** returns the current connection. */
MysqlConnection * SQLManager::getConnection(){
	return con;
}

/** delete files of a CDROM. */
void SQLManager::delete_files(int cd_id){
	MysqlQuery query = con->query();

	query << "SELECT id FROM " << File::table_name << " WHERE cdrom= " << cd_id;

	MysqlRes res = query.store();

	char * tables[8] =
	{
		"MP3APIC", "MP3GEOB", "MP3Header", "MP3ID3",
		"MP3POPM", "MP3UFID", "MP3URLS", "MP3USLT"
	};

//cout << cd_id << ": Rows found: " << res.size() << endl;
  MysqlRow row;
  MysqlRes::iterator i;

	for (i = res.begin(); i != res.end(); i++) {
    row = *i;
		uint fileid = (uint) row["id"];
		
		for (uint j=0; j<8; j++) {
			query << "DELETE FROM " << tables[j] << " WHERE mp3file= " << fileid;
//cout << query.preview() << endl;
			query.execute();
		}
	}

	query << "DELETE FROM " << File::table_name << " WHERE cdrom= " << cd_id;
	query.execute();
}

/** Just do test rows in Volume and Directory. */
void SQLManager::mk_test_rows(const uint TESTID){
	try{
		MysqlQuery query = con->query();
		query << "SELECT id FROM " << Volume::table_name << " WHERE id=" << TESTID;
		MysqlRes res = query.store();

  	last_vol_id = TESTID;

		if (res.size() > 0) {
		}
		else {
			query << "INSERT INTO " << Volume::table_name
			<< " VALUES (" << TESTID << ","
			<< "'TEST VOLUME' , NULL , NULL, NULL, NULL, NULL, NULL, NULL, NULL, 5, 'YES');";
//cout << query.preview() << endl;
			query.execute();
		}

		query << "SELECT id FROM " << Directory::table_name << " WHERE id=" << TESTID;
		res = query.store();

		if (res.size() > 0) {
		}
		else {
			query << "INSERT INTO " << Directory::table_name
			<< " VALUES (" << TESTID << ","
			<< "'/TEST_DIR', 1, 2, NULL, NULL, 0,"
			<< TESTID << ");";
//cout << query.preview() << endl;
			query.execute();
		}

	} catch (MysqlBadQuery er) {
    ShowError::display("SQLManager::mk_test_rows(uint):\n" + QString(er.what()));
    return;
#ifdef USE_STANDARD_EXCEPTION
  } catch (exception er) {
    ShowError::display("SQLManager::mk_test_rows(uint):\n" + QString(er.what()));
    return;
#endif
 }
}

/** Deletes a volume row and their directories and their files. */
void SQLManager::delete_volume(uint cd_id){
try {
	MysqlQuery query = con->query();
	query << "DELETE FROM " << Directory::table_name << " WHERE cdrom= " << cd_id;
	query.execute();

	delete_files(cd_id);

	query << "DELETE FROM " << Volume::table_name << " WHERE id= " << cd_id;
	query.execute();
	} catch (MysqlBadQuery er) {
    ShowError::display("SQLManager::mk_test_rows(uint):\n" + QString(er.what()));
    return;
#ifdef USE_STANDARD_EXCEPTION
  } catch (exception er) {
    ShowError::display("SQLManager::mk_test_rows(uint):\n" + QString(er.what()));
    return;
#endif
 }
}
