<html>
<head>
<?php
include "types_extensions.inc.php";
$id = $conn->connect();
?>

<title> File Types and Extensions </title>
</head>

<body>

<table border=1 align="center">

<tr>
<th>File Types</th>
<th>Extensions</th>
</tr>

<tr>

<td valign="top">
<table>
<?php print_types()?>
</table>
</td>

<td valign="top">
<table>
<?php print_extensions()?>
</table>
</td>

</tr>
</table>

</body>

</html>
