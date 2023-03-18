<?php
include "mycdcatalog.inc.php";

$id = $conn->connect();

$res = mysql_query ("SELECT id FROM MP3APIC")
    or die ("Requete invalide");

print ("<html><body>\n<ul>");
while (list($mp3id) = mysql_fetch_row($res)) {
  print ("<li> <img src=\"/mycdcatalog/mysql_image.php?$mp3id\"> </li>\n");
}
print ("\n</ul></body></html>");

mysql_free_result($res);
?>
