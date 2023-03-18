<?
function get_Field($table,$field,$idcomp,$id) {
 if ($id=="") return $id; // field can be NULL

 $line = get_one_line($table,$field,$idcomp,$id);
 list($result) = $line;
 return $result;
}

function get_many_lines($table, $fields, $order, $mp3id, $idcomp="mp3file") {
 $query = "SELECT $fields FROM $table WHERE $idcomp=$mp3id ORDER BY $order";
 $res = mysql_query ($query) or die ("Invalid Request:<br>$query");
 while ($row = mysql_fetch_row($res)) {
  $rows[] = $row;
 }
 return $rows;
}

function get_one_line($table, $fields, $idcomp, $mp3id) {
 $query = "SELECT $fields FROM $table WHERE $idcomp=$mp3id";
 $res = mysql_query ($query) or die ("Invalid Request:<br>$query");
 $nbrows = mysql_num_rows($res);
 if ($nbrows > 1) {
  echo "Number of rows: $nbrows in table: $table where: mp3file=$mp3id<br>";
  die("1 row spected!");
 }

 $row = mysql_fetch_row($res);
 return $row;
}

function get_id3($mp3id) {
 $id3 = get_one_line("MP3ID3", "*", "mp3file", $mp3id);
 if (!isset($id3) || ($id3=="")) return $id3;
 //echo "<br>WILL DO GETFIELD<br>";
 $id3[2] = get_Field("MP3Artist","name","id",$id3[2]);
 $id3[3] = get_Field("MP3Album","name","id",$id3[3]);
 $id3[6] = get_Field("MP3Genres","name","id",$id3[6]);
 $id3[7] = get_Field("MP3Comments","name","id",$id3[7]);
 $id3[11] = get_Field("MP3Artist","name","id",$id3[11]);
 $id3[14] = get_Field("MP3Artist","name","id",$id3[14]);

 array_shift($id3);
 return $id3;
}

function print_pictures($pics,$rootdir) {
 echo "<table align=\"center\" summary=\"pics\"><tr>\n";
 for($i=0;$i<sizeof($pics);$i++) {
  echo "<td><img alt=\"mp3image\" src=\"";
  echo "$rootdir";
  echo "mysql_image.php?";
  echo $pics[$i][0];
  echo "\"></td>\n";
 }
 echo "</tr></table>\n";
}

function print_rows($title, $nbcols, $head, $rows){
 if (isset($rows) && (sizeof($rows)>0)) {
  echo "<table width=\"85%\" border=1 cellpadding=0 cellspacing=0 align=\"center\" summary=\"rows\">\n";

  if ($title!="")
   echo "<tr> <th colspan=\"$nbcols\">$title</th> </tr>\n";

  print_row("<th class=\"atitle\" valign=\"top\">", $head, "</th>");
  for ($i=0;$i<sizeof($rows);$i++) {
   print_row("<td class=\"arow\" valign=\"top\">&nbsp;",$rows[$i],"</td>");
  }

  echo "</table><br>\n";
 }
}

function print_table($table, $cols, $order, $title, $nbcols, $head, $mp3id) {
 $rows = get_many_lines($table,$cols,$order,$mp3id);
 print_rows($title,$nbcols,$head,$rows);
}

function mk_links($urls) {
 for($i=0;$i<sizeof($urls);$i++) {
  $http = "";
  if (strncmp($urls[$i][0],"http://",7) != 0)
   $http = "http://";

  $urls[$i][0] = "<a href=\"$http" . $urls[$i][0]. "\" class=\"b\"> " . $urls[$i][0] . "</a>";
  //echo $urls[$i][0];
 }
 return $urls;
}

function norm_text($lyrics) {
 for($i=0;$i<sizeof($lyrics);$i++) {
  $lyrics[$i][0] = "<pre>" . $lyrics[$i][0] . "</pre>";
 }
 return $lyrics;
}

?>
