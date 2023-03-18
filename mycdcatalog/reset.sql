DROP TABLE `DataCDStatus`, `DateTimes`, `Directory`, `Extension`, `File`, `FileHandler`, `MP3APIC`, `MP3Album`, `MP3Artist`, `MP3GEOB`, `MP3Genres`, `MP3Header`, `MP3ID3`, `MP3POPM`, `MP3UFID`, `MP3URLS`, `MP3USLT`, `MP3Comments`, `Types`, `Volume`;

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

CREATE TABLE MP3APIC (
  id smallint(5) unsigned NOT NULL auto_increment,
  mp3file mediumint(8) unsigned NOT NULL default '0',
  mimeType varchar(64) binary default NULL,
  format varchar(16) binary default NULL,
  picType varchar(16) binary default NULL,
  description varchar(64) binary default NULL,
  picSize mediumint(9) default NULL,
  picture blob,
  PRIMARY KEY (id)
);

CREATE TABLE MP3Album (
  id smallint(5) unsigned NOT NULL auto_increment,
  name varchar(96) binary default NULL,
  PRIMARY KEY  (id),
  KEY name (name)
);

CREATE TABLE MP3Artist (
  id mediumint(8) unsigned NOT NULL auto_increment,
  name varchar(96) binary default NULL,
  PRIMARY KEY  (id),
  KEY name (name)
);

CREATE TABLE MP3Comments (
  id mediumint(8) unsigned NOT NULL auto_increment,
  name text default NULL,
  PRIMARY KEY (id)
);

CREATE TABLE MP3GEOB (
  mp3file mediumint(8) unsigned NOT NULL default '0',
  description varchar(128) binary default NULL,
  fileName varchar(128) binary default NULL,
  mimeType varchar(64) binary default NULL,
  dataSize smallint(5) unsigned default NULL,
  eobject blob
);

CREATE TABLE MP3Genres (
  id tinyint(3) unsigned NOT NULL auto_increment,
  name varchar(32) binary default NULL,
  PRIMARY KEY  (id),
  KEY name (name)
);

CREATE TABLE MP3Header (
  mp3file mediumint(8) unsigned NOT NULL default '0',
  header_at mediumint(8) unsigned default NULL,
  duration smallint(5) unsigned default NULL,
  version enum('MPEG 1','MPEG 2','MPEG 2.5') default NULL,
  layer enum('I','II','III') default NULL,
  bitrate smallint(5) unsigned default NULL,
  frequency enum('44100','48000','32000','22050','24000','16000','11025','12000','8000') default NULL,
  mode enum('Stereo','Joint Stereo','Dual Channel','Single Channel','Multi Channel') default NULL,
  protection enum('No','Yes') default NULL,
  copyright enum('No','Yes') default NULL,
  original enum('No','Yes') default NULL,
  emphasis enum('None','50/15 ms','reserved','CCIT J.17') default NULL,
  frames smallint(5) unsigned default NULL
);

CREATE TABLE MP3ID3 (
  mp3file mediumint(8) unsigned NOT NULL default '0',
  title varchar(64) binary default NULL,
  artist mediumint(8) unsigned default NULL,
  album smallint(5) unsigned default NULL,
  aYear year(4) default NULL,
  track tinyint(3) unsigned default NULL,
  genre tinyint(3) unsigned default NULL,
  comment mediumint(8) unsigned default NULL,
  v1Tag enum('No','Yes') default NULL,
  v2Tag enum('No','Yes') default NULL,
  frames tinyint(3) unsigned default NULL,
  composer mediumint(8) unsigned default NULL,
  copyright varchar(32) binary default NULL,
  encodedby varchar(32) binary default NULL,
  origartist mediumint(8) unsigned default NULL,
  length mediumint(8) unsigned default NULL,
  mediaType varchar(32) binary default NULL,
  fileType varchar(32) binary default NULL,
  pcounter mediumint(8) unsigned default NULL
);

CREATE TABLE MP3POPM (
  mp3file mediumint(8) unsigned NOT NULL default '0',
  email varchar(128) binary default NULL,
  rating smallint(5) unsigned default NULL,
  counter smallint(5) unsigned default NULL
);

CREATE TABLE MP3UFID (
  mp3file mediumint(8) unsigned NOT NULL default '0',
  owner varchar(128) binary default NULL,
  identifier blob
);

CREATE TABLE MP3URLS (
  mp3file mediumint(8) unsigned NOT NULL default '0',
  link varchar(128) binary default NULL,
  description varchar(128) binary default NULL
);

CREATE TABLE MP3USLT (
  mp3file mediumint(8) unsigned NOT NULL default '0',
  lyric text,
  description varchar(64) binary default NULL,
  lang varchar(16) binary default NULL
);

INSERT INTO MP3Genres VALUES
 (NULL, 'Blues'),
 (NULL, 'Classic Rock'),
 (NULL, 'Country'),
 (NULL, 'Dance'),
 (NULL, 'Disco'),
 (NULL, 'Funk'),
 (NULL, 'Grunge'),
 (NULL, 'Hip-Hop'),
 (NULL, 'Jazz'),
 (NULL, 'Metal'),
 (NULL, 'New Age'),
 (NULL, 'Oldies'),
 (NULL, 'Other'),
 (NULL, 'Pop'),
 (NULL, 'R&B'),
 (NULL, 'Rap'),
 (NULL, 'Reggae'),
 (NULL, 'Rock'),
 (NULL, 'Techno'),
 (NULL, 'Industrial'),
 (NULL, 'Alternative'),
 (NULL, 'Ska'),
 (NULL, 'Death Metal'),
 (NULL, 'Pranks'),
 (NULL, 'Soundtrack'),
 (NULL, 'Euro-Techno'),
 (NULL, 'Ambient'),
 (NULL, 'Trip-Hop'),
 (NULL, 'Vocal'),
 (NULL, 'Jazz+Funk'),
 (NULL, 'Fusion'),
 (NULL, 'Trance'),
 (NULL, 'Classical'),
 (NULL, 'Instrumental'),
 (NULL, 'Acid'),
 (NULL, 'House'),
 (NULL, 'Game'),
 (NULL, 'Sound Clip'),
 (NULL, 'Gospel'),
 (NULL, 'Noise'),
 (NULL, 'AlternRock'),
 (NULL, 'Bass'),
 (NULL, 'Soul'),
 (NULL, 'Punk'),
 (NULL, 'Space'),
 (NULL, 'Meditative'),
 (NULL, 'Instrumental Pop'),
 (NULL, 'Instrumental Rock'),
 (NULL, 'Ethnic'),
 (NULL, 'Gothic'),
 (NULL, 'Darkwave'),
 (NULL, 'Techno-Industrial'),
 (NULL, 'Electronic'),
 (NULL, 'Pop-Folk'),
 (NULL, 'Eurodance'),
 (NULL, 'Dream'),
 (NULL, 'Southern Rock'),
 (NULL, 'Comedy'),
 (NULL, 'Cult'),
 (NULL, 'Gangsta'),
 (NULL, 'Top 40'),
 (NULL, 'Christian Rap'),
 (NULL, 'Pop/Funk'),
 (NULL, 'Jungle'),
 (NULL, 'Native American'),
 (NULL, 'Cabaret'),
 (NULL, 'New Wave'),
 (NULL, 'Psychadelic'),
 (NULL, 'Rave'),
 (NULL, 'Showtunes'),
 (NULL, 'Trailer'),
 (NULL, 'Lo-Fi'),
 (NULL, 'Tribal'),
 (NULL, 'Acid Punk'),
 (NULL, 'Acid Jazz'),
 (NULL, 'Polka'),
 (NULL, 'Retro'),
 (NULL, 'Musical'),
 (NULL, 'Rock & Roll'),
 (NULL, 'Hard Rock'),
--winamp_genres--
 (NULL, 'Folk'),
 (NULL, 'Folk-Rock'),
 (NULL, 'National Folk'),
 (NULL, 'Swing'),
 (NULL, 'Fast Fusion'),
 (NULL, 'Bebob'),
 (NULL, 'Latin'),
 (NULL, 'Revival'),
 (NULL, 'Celtic'),
 (NULL, 'Bluegrass'),
 (NULL, 'Avantgarde'),
 (NULL, 'Gothic Rock'),
 (NULL, 'Progressive Rock'),
 (NULL, 'Psychedelic Rock'),
 (NULL, 'Symphonic Rock'),
 (NULL, 'Slow Rock'),
 (NULL, 'Big Band'),
 (NULL, 'Chorus'),
 (NULL, 'Easy Listening'),
 (NULL, 'Acoustic'),
 (NULL, 'Humour'),
 (NULL, 'Speech'),
 (NULL, 'Chanson'),
 (NULL, 'Opera'),
 (NULL, 'Chamber Music'),
 (NULL, 'Sonata'),
 (NULL, 'Symphony'),
 (NULL, 'Booty Bass'),
 (NULL, 'Primus'),
 (NULL, 'Porn Groove'),
 (NULL, 'Satire'),
 (NULL, 'Slow Jam'),
 (NULL, 'Club'),
 (NULL, 'Tango'),
 (NULL, 'Samba'),
 (NULL, 'Folklore'),
 (NULL, 'Ballad'),
 (NULL, 'Power Ballad'),
 (NULL, 'Rhythmic Soul'),
 (NULL, 'Freestyle'),
 (NULL, 'Duet'),
 (NULL, 'Punk Rock'),
 (NULL, 'Drum Solo'),
 (NULL, 'Acapella'),
 (NULL, 'Euro-House'),
 (NULL, 'Dance Hall'),
 (NULL, 'Goa'),
 (NULL, 'Drum & Bass'),
 (NULL, 'Club-House'),
 (NULL, 'Hardcore'),
 (NULL, 'Terror'),
 (NULL, 'Indie'),
 (NULL, 'BritPop'),
 (NULL, 'Negerpunk'),
 (NULL, 'Polsk Punk'),
 (NULL, 'Beat'),
 (NULL, 'Christian Gangsta Rap'),
 (NULL, 'Heavy Metal'),
 (NULL, 'Black Metal'),
 (NULL, 'Crossover'),
 (NULL, 'Contemporary Christian'),
 (NULL, 'Christian Rock'),
 (NULL, 'Merengue'),
 (NULL, 'Salsa'),
 (NULL, 'Thrash Metal'),
 (NULL, 'Anime'),
 (NULL, 'JPop'),
 (NULL, 'Synthpop');
