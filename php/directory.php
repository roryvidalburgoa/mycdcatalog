<html>
<head>
<?
include "mycdcatalog.inc.php";

$volname = $HTTP_GET_VARS["volname"];
$volid = $HTTP_GET_VARS["volid"];

if ((!isset($volid)) || (!isset($volname))) {
 echo "<title>Invalid request</title>\n";
 echo "</head> <body> Invalid request!\n";
 echo "<br>Give a Volume ID<br>\n";
 echo "?volid=143\n<br>and a Volume Name<br>\n&volname=CD1";
 echo "<br>volid=$volid, volname=$volname</body></html>";
 die();
}

$volname = urldecode($volname);
?>

<title>Root Directory of: <?echo $volname?></title>
</head>

<body>
<h1>RootDir of Volume: <?echo $volname?></h1>
<table border=1>

<?php

$id = $conn->connect();

$cols = "d.id, d.path, m.dt, a.dt, d.nb_dirfiles, d.readable";
$tabs = "Directory d, DateTimes m, DateTimes a";
$where = "m.id = d.date_lmodif AND a.id=d.date_access AND d.cdrom=$volid AND d.father=0";
// AND r.id=d.father";
$query = "SELECT $cols FROM $tabs WHERE $where";

$res = mysql_query ($query) or die ("Invalid Request:<BR>$query");

$head = array ("ID","Path","Last Modification","Last Access","Directories or Files", "Readable");
print_row("<th>",$head,"</th>");

while ($row = mysql_fetch_row($res)) {
  $row[1] = mk_link($rootdir . "files.php?dirid=$row[0]&dirname=". urlencode($row[1]) , $row[1]);
  print_row("<td>",$row,"</td>");
}

mysql_free_result($res);
?>

</table><br>
</body>
</html>
