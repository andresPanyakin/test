<?php
require_once 'login.php';

$db_server = mysql_connect( $db_hostname, $db_username, $db_password );
if( !$db_server )
	die( "Can't connect to mysql " . mysql_error() );

$db_database = "zoopark";

mysql_select_db( $db_database )
	or die( "Can't select data base " . mysql_error() );

$query = "SELECT * FROM cats;";
$result = mysql_query($query);
if(!$result)
	die("FUCK" . mysql_error()) ;

$rows = mysql_num_rows($result);
echo "<table><tr> <th>Id</th> <th>Family</th>
	<th>Name</th><th>Age</th></tr>";
for($j = 0; $j < $rows; $j++)
{
	$row = mysql_fetch_row($result);
	echo "<tr>";
	for($k = 0; $k < 4; $k++)
		echo "<td>$row[$k]</td>";
	echo "</tr>";
}
echo "</table>";
?>
