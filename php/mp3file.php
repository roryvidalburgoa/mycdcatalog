<!--DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0//EN"-->
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<link REL="stylesheet" HREF="./style.css" TYPE="text/css">

<?php
include "mycdcatalog.inc.php";

$filename = $HTTP_GET_VARS["filename"];
$mp3id = $HTTP_GET_VARS["id"];

if (!isset($filename) || !isset($mp3id)) {
 echo "<title>Invalid request </title>\n";
 echo "</head> <body> Invalid request!\n";
 echo "<br>Give a filename and a mp3id <br>\n";
 echo "id=173&filename=file.mp3</body></html>";
 die();
}

include "mp3handler.inc.php";
$id = $conn->connect();
?>

<title><?echo $filename?></title>

</head>

<body>

<h1 align="center"><?echo $filename?></h1><br>

<?
$pics = get_many_lines("MP3APIC","id","id",$mp3id);
if (isset($pics) && (sizeof($pics)>0) && ($pics!="")){
 print_pictures($pics,$rootdir);
}
?>

<?
$hdr = get_one_line("MP3Header", "*", "mp3file", $mp3id);
if (isset($hdr) && (sizeof($hdr)>1) && ($hdr!="")){
 $head = array("Header Found at", "Duration", "MPEG", "Layer", "Bitrate",
                "Frequency","Stereo Mode", "CRC", "Copyright", "Original",
                "Emphasis", "Frames");
 array_shift($hdr);
 $hdr[0] = str_size($hdr[0]);
 $hdr[1] = $hdr[1] . " secs";
 $hdr[4] = $hdr[4] . " kbps";
 $hdr[5] = $hdr[5] . " hz";
 $hdrs[] = $hdr;
 print_rows("MPEG Header",12,$head,$hdrs);
}
?>

<?
$id3 = get_id3($mp3id);

if (isset($id3) && (sizeof($id3)==18) && ($id3!="")) {
// $id3s[] = $id3;
 $id3l[] = array_slice($id3, 0, 9);
 $head = array("Title","Artist","Album","Year","Track","Genre","Comment",
        "Tag ID3v1","Tag ID3v2");
 print_rows("ID3 Tag", 9, $head, $id3l);

 $id3r[] = array_slice($id3, 9);
 $head = array("Frames in Tag","Composer","Original Artist","Copyright",
                "Encoded By","Length (ms)","Media Type","File Type","Play Counter");
 print_rows("ID3 Tag", 9, $head, $id3r);
}
?>

<?
$head = array("Description","File Name","Mime Type","Data Size");
print_table("MP3GEOB","description,fileName,mimeType,dataSize", "dataSize",
        "General encapsulated objects",4,$head,$mp3id);
?>

<?
$head = array("E-Mail","Rating","Counter");
print_table("MP3POPM","email,rating,counter","rating","Popularimeters",3,$head,$mp3id);
?>

<?
$ufid = get_one_line("MP3UFID", "owner,identifier", "mp3file", $mp3id);
if (isset($ufid) && (sizeof($ufid)==2) && ($ufid!="")){
 $head = array("Owner","Identifier");
 $ufid[1] = bin2hex($ufid[1]);
 $ufidr[] = $ufid;
 print_rows("Unique file identifier",2,$head,$ufidr);
}
?>

<?
$head = array("Link", "Description");
$urls = get_many_lines("MP3URLS","link,description","link",$mp3id);
$urls = mk_links($urls);
print_rows("URLS",2,$head,$urls);
?>

<?
$head = array("Text", "Description", "Language");
$lyrics = get_many_lines("MP3USLT","lyric,description,lang","lyric",$mp3id);
$lyrics = norm_text($lyrics);
print_rows("Lyrics",3,$head,$lyrics);
?>

</body>
</html>
