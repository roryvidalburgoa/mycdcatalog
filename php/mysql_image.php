<?php
include "mycdcatalog.inc.php";

$picid = implode($argv," ");

$id = $conn->connect();

$res = mysql_query ("SELECT mimeType,picture FROM MP3APIC where id=$picid")
    or die ("Requete invalide");

list($mime,$pic) = mysql_fetch_row($res);

Header("Content-type: $mime");
print ($pic);

mysql_free_result($res);
?>
