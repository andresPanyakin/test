<?php
require_once 'login.php';

$db_server = mysql_connect( $db_hostname, $db_username, $db_password );
if( !$db_server )
	die( "Can't connect to mysql " . mysql_error() );

$db_database = "zoopark";

mysql_select_db( $db_database )
	or die( "Can't select data base " . mysql_error() );

$query = "DELETE FROM cats WHERE name='Growler'";
$result = mysql_query($query);
if(!$result)
	die("FUCK" . mysql_error()) ;

?>

