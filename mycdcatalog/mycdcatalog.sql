CREATE TABLE DataCDStatus (
  id tinyint(3) unsigned NOT NULL default '0',
  code varchar(16) binary default NULL,
  msg varchar(32) binary default NULL
);

INSERT INTO DataCDStatus VALUES ('1', 'CDS_DATA_1', 'Data MODE1 2048 user bytes/frame');
INSERT INTO DataCDStatus VALUES ('2', 'CDS_DATA_2', 'Data MODE2 2324 user bytes/frame');
INSERT INTO DataCDStatus VALUES ('3', 'CDS_XA_2_1', 'Mixed Data MODE2 Form1 2048 user');
INSERT INTO DataCDStatus VALUES ('4', 'CDS_XA_2_2', 'Mixed Data MODE2 Form2 2324 user');
INSERT INTO DataCDStatus VALUES ('5', 'CDS_MIXED', 'Mixed Audio/Data Disc');

CREATE TABLE DateTimes (
  id mediumint(8) unsigned NOT NULL auto_increment,
  dt datetime NOT NULL default '0000-00-00 00:00:00',
  PRIMARY KEY  (id),
  KEY dt (dt)
);

CREATE TABLE Directory (
  id mediumint(8) unsigned NOT NULL auto_increment,
  path varchar(255) binary NOT NULL default '',
  date_lmodif mediumint(8) unsigned ,
  date_access mediumint(8) unsigned ,
  nb_dirfiles smallint(5) unsigned default NULL,
  readable enum('No','Yes') default NULL,
  father mediumint(8) unsigned default NULL,
  cdrom smallint(5) unsigned NOT NULL default '0',
  PRIMARY KEY  (id)
);

CREATE TABLE Extension (
  id smallint(5) unsigned NOT NULL auto_increment,
  name varchar(16) NOT NULL default '',
  PRIMARY KEY  (id),
  KEY name (name)
);

CREATE TABLE File (
  id mediumint(8) unsigned NOT NULL auto_increment,
  name varchar(128) binary NOT NULL default '',
  date_lmodif mediumint(8) unsigned ,
  date_access mediumint(8) unsigned ,
  size int(10) unsigned default NULL,
  type smallint(5) unsigned NOT NULL default '0',
  ext smallint(5) unsigned NOT NULL default '0',
  readable enum('No','Yes') default NULL,
  dirpath mediumint(8) unsigned NOT NULL default '0',
  cdrom smallint(5) unsigned NOT NULL default '0',
  PRIMARY KEY  (id)
);

CREATE TABLE FileHandler (
  akey varchar(32) binary NOT NULL default '',
  script varchar(32) binary NOT NULL default ''
) COMMENT='Represents keys recognized by a file handler and their respectif PHP script';

INSERT INTO FileHandler VALUES ('MP', 'mp3file.php');
INSERT INTO FileHandler VALUES ('ID3', 'mp3file.php');
INSERT INTO FileHandler VALUES ('mp3', 'mp3file.php');

CREATE TABLE Types (
  id smallint(5) unsigned NOT NULL auto_increment,
  code varchar(32) binary NOT NULL default '',
  description varchar(64) binary default NULL,
  PRIMARY KEY  (id),
  KEY code (code,description)
);

CREATE TABLE Volume (
  id smallint(5) unsigned NOT NULL auto_increment,
  vol_id varchar(128) binary NOT NULL default '',
  sys_id varchar(128) binary default NULL,
  app_id varchar(128) binary default NULL,
  size int(10) unsigned default NULL,
  filessize int(10) unsigned default NULL,
  nbdirs smallint(5) unsigned default NULL,
  nbfiles smallint(5) unsigned default NULL,
  unread_dirs smallint(5) unsigned default NULL,
  unread_files smallint(5) unsigned default NULL,
  status tinyint(3) unsigned NOT NULL default '0',
  complete enum('No','Yes') NOT NULL default 'No',
  PRIMARY KEY  (id)
);

