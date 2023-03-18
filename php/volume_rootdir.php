<html>
<head>
<title>Volumes</title>
</head>

<body>

<h1> CDROMs in DB </h1>

<table border=1>

<?php
include "mycdcatalog.inc.php";

$idconn = $conn->connect();

$order = $HTTP_GET_VARS["order"];
$asc = $HTTP_GET_VARS["asc"];
if (!isset($order)) $order = "v.id";
if (!isset($asc)) $asc = "ASC";

$volid = $HTTP_GET_VARS["volid"];

$cols = "v.id,v.vol_id,v.sys_id,v.app_id,v.size,v.filessize,v.nbdirs,v.nbfiles,v.unread_dirs,v.unread_files,ds.msg,v.complete,m.dt,a.dt,r.nb_dirfiles,r.id";
$tabs = "Volume v, DataCDStatus ds, Directory r, DateTimes m, DateTimes a";

if (isset($volid))
 $where="v.id=$volid AND v.status=ds.id AND r.cdrom=v.id AND r.father=0 AND r.date_lmodif=m.id AND r.date_access=a.id";
else
 $where = "v.status=ds.id AND r.cdrom=v.id AND r.father=0 AND r.date_lmodif=m.id AND r.date_access=a.id";

$query = "SELECT $cols FROM $tabs WHERE $where ORDER BY $order $asc";

$res = mysql_query ($query) or die ("Invalid Request:<br>$query");

$titles = array ("ID","Volume","System","Application","Size","Sum File Sizes","Directories","Files","Unreadable Directories","Unreadable Files","Status","Complete","Last Modification","Last Access","Nb DirFiles in RootDir");

if (!isset($volid)) {
 $acols = split(',',$cols);
 $head = make_hdr_links($titles,$acols,$rootdir,"volume_rootdir.php",$asc);
} else {
 $head = $titles;
}

print_row("<th>", $head , "</th>", sizeof($head));

while ($row = mysql_fetch_row($res)) {
  $row[1] = mk_link($rootdir . "files.php?dirid=$row[15]&dirname=" . urlencode("./"), $row[1]);
  $row[4] = str_size($row[4]);
  $row[5] = str_size($row[5]);
  print_row("<td >",$row,"</td>",sizeof($row)-1);
}

mysql_free_result($res);
?>

</table>
</body>
</html>
