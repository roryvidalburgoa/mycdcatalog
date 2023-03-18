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
if (!isset($order)) $order = "v.id";

$cols = "v.id,v.vol_id,v.sys_id,v.app_id,v.size,v.filessize,v.nbdirs,";
$cols = $cols . "v.nbfiles,v.unread_dirs,v.unread_files,ds.msg,v.complete";
$tabs = "Volume v, DataCDStatus ds";
$where = "v.status=ds.id";
$query = "SELECT $cols FROM $tabs WHERE $where ORDER BY $order";

$res = mysql_query ($query) or die ("Invalid Request:<br>$query");

$titles = array ("ID","Volume","System","Application","Size","Sum File Sizes","Directories","Files","Unreadable Directories","Unreadable Files","Status","Complete");
$acols = split(',',$cols);
$head = make_hdr_links($titles,$acols,$rootdir,"volume.php");

print_row("<th>", $head , "</th>");

while ($row = mysql_fetch_row($res)) {
  $row[1] = mk_link($rootdir . "directory.php?volid=$row[0]&volname=" . urlencode($row[1]), $row[1]);
  $row[4] = str_size($row[4]);
  $row[5] = str_size($row[5]);
  print_row("<td valign=\"top\">",$row,"</td>");
}

mysql_free_result($res);
?>

</table>
</body>
</html>
