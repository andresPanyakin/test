<?php
require_once 'login.php';

$db_server = mysql_connect( $db_hostname, $db_username, $db_password );
if( !$db_server )
	die( "Can't connect to mysql " . mysql_error() );

$db_database = "zoopark";

mysql_select_db( $db_database )
	or die( "Can't select data base " . mysql_error() );

$query = "Insert Into cats Values(NULL, 'Char', 'Stumpy', 5)";
$result = mysql_query($query);
echo "New Id is: " . mysql_insert_id();
if(!$result)
	die("FUCK" . mysql_error()) ;

?>

