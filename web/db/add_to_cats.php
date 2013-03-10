<?php
require_once 'login.php';

$db_server = mysql_connect( $db_hostname, $db_username, $db_password );
if( !$db_server )
	die( "Can't connect to mysql " . mysql_error() );

$db_database = "zoopark";

mysql_select_db( $db_database )
	or die( "Can't select data base " . mysql_error() );

$query1 = "INSERT INTO cats VALUES(NULL, 'Lion', 'Leo', 4)";
$query2 = "INSERT INTO cats VALUES(NULL, 'Cougar', 'Growler', 2)";
$query3 = "INSERT INTO cats VALUES(NULL, 'Cheetah', 'Charly', 3)";

$result = mysql_query($query1);
if(!$result)
	die("FUCK" . mysql_error()) ;

$result = mysql_query($query2);
if(!$result)
	die("FUCK" . mysql_error()) ;

$result = mysql_query($query3);
if(!$result)
	die("FUCK" . mysql_error()) ;
?>
