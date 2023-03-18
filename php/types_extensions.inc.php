<?php
include "mycdcatalog.inc.php";

//$types_tab = "Types";
//$ext_tab = "Extension";

function print_types() {
 $cols = "t.id, t.description, count(*)";
 $tabs = "Types t, File f";
 $where = "t.id = f.type";
 $group = "t.description";
 $query = "SELECT $cols FROM $tabs WHERE $where GROUP BY $group";

 $res = mysql_query ($query) or die ("Invalid Request:<BR>$query");

 while ($row = mysql_fetch_row($res)) {
        if ($row[2]>1) $files = " files";
        else $files = " file";

        echo "<tr> <td> $row[1] </td> <td> ($row[2] $files) </td> <tr>\n";
 }

}

function print_extensions() {
 $cols = "e.id, e.name, count(*)";
 $tabs = "Extension e, File f";
 $where = "e.id = f.ext";
 $group = "e.name";
 $query = "SELECT $cols FROM $tabs WHERE $where GROUP BY $group";

 $res = mysql_query ($query) or die ("Invalid Request:<BR>$query");

 while ($row = mysql_fetch_row($res)) {
         if ($row[2]>1) $files = " files";
        else $files = " file";

        echo "<tr> <td> $row[1] </td> <td> ($row[2] $files) </td> <tr>\n";
 }

}

?>
