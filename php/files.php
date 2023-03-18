<html>
<head>
<?
$dorder = $HTTP_GET_VARS["dorder"];
$forder = $HTTP_GET_VARS["forder"];
$dirid = $HTTP_GET_VARS["dirid"];
$dirname = $HTTP_GET_VARS["dirname"];
$asc = $HTTP_GET_VARS["asc"];

if (!isset($dirid) || !isset($dirname)) {
 echo "<title>Invalid request</title>\n";
 echo "</head> <body> Invalid request!\n";
 echo "<br>Give a Directory ID<br>\n";
 echo "dirid=173\n<br>and a Directory Name<br>\ndirname=Directory1";
 echo "<br>\nYou givee: dirid=$dirid&dirname=$dirname</body></html>";
 die();
}

//$dirid = implode($argv," ");
$dirname = urldecode($dirname);
?>

<title>Directories and Files of: <?echo $dirname?></title>
</head>

<body>

<h1><?echo $dirname?></h1>

<table border=1>
<tr><th align="center" colspan="6">Directories</th></tr>
<?php

include "mycdcatalog.inc.php";
$connid = $conn->connect();

if (!isset($dorder)) $dorder = "d.id";
if (!isset($forder)) $forder="f.id";
if (!isset($asc)) $asc="ASC";

$cols = "d.id,d.path,m.dt,a.dt,d.nb_dirfiles,d.readable";
$tabs = "Directory d, DateTimes m, DateTimes a";
$where = "m.id = d.date_lmodif AND a.id=d.date_access AND d.father=$dirid";

$query = "SELECT $cols FROM $tabs WHERE $where ORDER BY $dorder $asc";
$res1 = mysql_query ($query) or die ("Invalid Request:<br>$query");

$dir_cols = split(',',$cols);
$title1 = array ("ID","Path","Last Modification","Last Access",
                "Directories or Files","Readable");
$head1 = mk_hdr_links($title1,$dir_cols,$rootdir,$dirid,$dirname,1,$forder,$asc);
print_row("<th>",$head1,"</th>");

$orders= "&dorder=$dorder&forder=$forder&asc=$asc";
while ($row1 = mysql_fetch_row($res1)) {
  $row1[1] =
   mk_link($rootdir . "files.php?dirid=$row1[0]&dirname=" . urlencode($row1[1]) . $orders , $row1[1]);
  print_row("<td>",$row1,"</td>");
}

mysql_free_result($res1);
?>

</table>

<br>

<table border=1>
<tr><th align="center" colspan="7">Files</th></tr>
<?
$query = "SELECT * from FileHandler";
$fhres = mysql_query ($query) or die ("Invalid Request:<br>$query");

while ($fhrow = mysql_fetch_array($fhres)) {
//  echo "FILE HANDLER: <br>";
//  print_keys_values($fhrow);
  $fhrows[] = $fhrow;
}

$cols = "f.id,f.name,m.dt,a.dt,f.size,f.readable,t.description,t.code,e.name";
$tabs = "File f, DateTimes m, DateTimes a, Types t, Extension e";
$where = "m.id = f.date_lmodif AND a.id=f.date_access AND f.dirpath=$dirid AND f.type=t.id AND f.ext=e.id";
$query = "SELECT $cols FROM $tabs WHERE $where ORDER BY $forder $asc";

$res2 = mysql_query ($query) or die ("Invalid Request:<br>$query");

$file_cols = split(',',$cols);
$title2 = array ("ID","Name","Last Modified","Last Access","Size","Readable","Type");
$head2 = mk_hdr_links($title2,$file_cols,$rootdir,$dirid,$dirname,0,$dorder,$asc);
print_row("<th>",$head2,"</th>",sizeof($head2)-2);

while ($row2 = mysql_fetch_row($res2)) {
  $script = use_filehandler( $fhrows , array( $row2[6], $row2[7], $row2[8] ) );
  if ($script != "") {
   $link = $rootdir . $script . "?id=" . $row2[0] . "&filename=" . urlencode($row2[1]);
   $row2[1] = mk_link($link , $row2[1]);
  }

  $row2[4] = str_size($row2[4]);
  print_row("<td>",$row2,"</td>",sizeof($row2)-2);
}

mysql_free_result($res2);
?>

</table><br>
</body>
</html>
<!--files.php-->