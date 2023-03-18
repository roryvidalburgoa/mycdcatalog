<?
class Connection {
  var $username;
  var $password;
  var $host;
  var $port;
  var $socket;
  var $db;

  // Default values
  function Connection (
        $u="your username",
        $p="your password",
        $h="your host",
        $po="your mysql port",
        $s="/var/lib/mysql/mysql.sock",
        $d="your database name") {

    $this->username = $u;
    $this->password = $p;
    $this->host = $h;
    $this->port = $po;
    $this->socket = $s;
    $this->db = $d;
    //$this->toprint();
  }

  function toprint() {
    echo "Username: \"$this->username\"<br>";
    echo "Password: \"$this->password\"<br>";
    echo "Host: \"$this->host\"<br>";
    echo "Port: \"$this->port\"<br>";
    echo "Socket: \"$this->socket\"<br>";
    echo "Database: \"$this->db\"<br>";
  }

  function connect () {
    //$this->toprint();
    if ($this->host != "") {
      if ($this->port != "") {
         $this->port = 3306;
      }

      $id = mysql_connect("$this->host:$this->port", $this->username, $this->password)
       || die ("Can't connect to MySQL server: \"$this->host:$this->port\"");
       //echo "host:port\n";
    } else {
      $id = mysql_connect(":$this->socket", $this->username, $this->password)
       || die ("Can't connect to MySQL server: \"$this->socket\"");
       //echo ":socket\n";
    }

    if(!mysql_select_db($this->db)) die ("DB \"$this->db\" isn't in MySQL server");

    //echo "ID: $id<BR>";
    return $id;
  }
}

function print_row ($open,$row,$close,$size=0) {
  $vals = array_values($row);
  if ($size == 0) $size = sizeof($vals);

  echo "<tr>";
  $i = 0;
  while ($i<$size) {
    echo "$open $vals[$i] $close\n";
    $i++;
  }
  echo "</tr>\n";
}

function print_array($_array) {
 $_size = sizeof($_array);
 $i=0;
 while ($i<$_size) {
  echo "$i/$_size: $_array[$i]<br>";
  $i++;
 }
}

function print_arow ($open,$row,$close,$size=0) {
  if ($size == 0) $size = count($row)/2;
  $tmp = count($row);
  echo "<tr>";
  $i = 0;
  while ($i<$size) {
    echo "$i/$size/$tmp $open $row[$i] $close\n";
    $i++;
  }
  echo "</tr>\n";
}

function print_keys_values($anArray) {
 while (list($key, $val) = each($anArray)) {
   echo "$key => $val<br>";
 }
}

function mk_link($link,$label) {
//echo urlencode($link); echo "<br>";
 return "<a href=\"" . $link . "\">" . $label . "</a>";
}

function str_size($aSize) {
  if (!isset($aSize) || ($aSize=="")) {
   return $aSize;
  }

  if ($aSize < 1024) {
    return "$aSize Bytes";
  }

  if ($aSize < 1048576) {
   $kbytes = $aSize / 1024.0;
   $size = sprintf("%.2lf KBytes", $kbytes);
  } else {
   $mbytes = $aSize / 1048576.0;
   $size = sprintf("%.2lf MBytes", $mbytes);
  }
  return $size;
}

function use_filehandler( $fhrows , $keys ) {
  $script="";
  $found = 0;

  while (list($i, $row) = each ($fhrows)) {
  //echo "I=$i <br>";
   while (list($j, $key) = each ($keys)) {
    //echo "J=$j : key=$key : rowkey="; echo $row["akey"];echo "<br>";
    if ($row["akey"] == $key) {
      $found = 1;
      $script = $row["script"];
      break;
    }
   }
   if ($found>0) break;
   reset($keys);
  }

  return $script;
}

function make_hdr_links($titles,$acols,$rootdir,$script,$asc="ASC") {
 if ($asc=="ASC") $asc = "DESC";
 else $asc = "ASC";

 $tmp = $roodir . "$script?asc=$asc&order=";

 for($i=0;$i<sizeof($titles);$i++) {
  $res[] = mk_link($tmp . $acols[$i] , $titles[$i]);
 }

 return $res;
}

function mk_hdr_links($titles,$acols,$rootdir,$dirid,$dirname,$isdir,$order,$asc="ASC") {
 $dirname = urlencode($dirname);
 if ($asc=="ASC") $asc = "DESC";
 else $asc = "ASC";

 $tmp = $roodir . "files.php?dirid=$dirid&dirname=$dirname&asc=$asc&";

 if ($isdir==1)
  $tmp .= "forder=$order&dorder=";
 else
  $tmp .= "dorder=$order&forder=";

 for($i=0;$i<sizeof($acols);$i++) {
  $res[] = mk_link($tmp . $acols[$i] , $titles[$i]);
 }
 return $res;
}

$conn = new Connection();
$rootdir = "/mycdcatalog/";
//print ("CFG");
?>
