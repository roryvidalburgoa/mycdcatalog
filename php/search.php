<html>
<head>
<title>Search Page</title>
</head>

<?php
include "mycdcatalog.inc.php";
$filename = $HTTP_POST_VARS["filename"];
?>

<body>
<table width="25%" border=0 cellpadding=0 cellspacing=0 align="center">
<tr><th colspan=2 align="left">Search Files:</th><tr>
<form action="<?echo "$rootdir";echo "search.php"?>" method="POST" enctype="application/x-www-form-urlencoded">

<tr>
<td colspan=2>
<input type="text" name="filename" value="<?echo $filename?>" align="top">
</td>
</tr>

<tr>
<td>
<input type="submit" name="ok" value="Search" align="center">
</td>

<td>
<input type="reset" name="reset" value="Reset" align="center">
</td>
</tr>

</form>
</table>
<br>

<?
if ($filename!="") {
 echo "<center>You want to find: <b>$filename</b></center><br>\n";
 $id = $conn->connect();

$cols = "f.id,f.name,d.path,v.vol_id,m.dt,a.dt,f.size,f.readable,t.description,t.code,e.name,d.id,v.id";
$tabs = "File f, Directory d, Volume v,DateTimes m, DateTimes a, Types t, Extension e";
$where = "d.id=f.dirpath AND v.id=f.cdrom AND m.id=f.date_lmodif AND a.id=f.date_access AND f.type=t.id AND f.ext=e.id AND f.name like '%$filename%'";

 $query = "SELECT $cols FROM $tabs WHERE $where ORDER BY f.id";
 $res = mysql_query ($query) or die ("Invalid Request:<br>$query");

 $nbrows = mysql_num_rows($res);
 echo "<center><b>$nbrows</b> files found</center><br>\n";

 if($nbrows>0){
  echo "<table border=1 align=\"center\">\n";

$query = "SELECT * from FileHandler";
$fhres = mysql_query ($query) or die ("Invalid Request:<br>$query");

while ($fhrow = mysql_fetch_array($fhres)) {
  $fhrows[] = $fhrow;
}

  //$file_cols = split(',',$cols);
  $title = array ("ID","Name","Path","CDROM","Last Modified","Last Access","Size","Readable","Type");
  //$head = mk_hdr_links($title,$file_cols,$rootdir);
  print_row("<th>",$title,"</th>",sizeof($title));

  while ($row = mysql_fetch_row($res)) {
    $script = use_filehandler( $fhrows , array( $row[8], $row[9], $row[10] ) );

    $fname = $row[1];
    ereg("(.*)($filename)(.*)",$fname,$regs);
    $fname = "$regs[1]<b>$regs[2]</b>$regs[3]";// &nbsp $regs[0]";

    if ($script != "") {
     $link = $rootdir . $script . "?id=" . $row[0] . "&filename=" . urlencode($row[1]);
     $row[1] = mk_link($link , $fname);
    } else {
     $row[1] = $fname;
    }

    $row[2] = mk_link("files.php?dirid=". $row[11]. "&dirname=" . urlencode($row[2]) , $row[2]);
    $row[3] = mk_link("volume_rootdir.php?volid=" . $row[12] , $row[3]);
    $row[6] = str_size($row[6]);
    print_row("<td>",$row,"</td>",sizeof($row)-4);

  }

  echo "</table><br>\n";
 }

}

?>

</body>

</html>
