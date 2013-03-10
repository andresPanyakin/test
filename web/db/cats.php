<?php
require_once 'login.php';

$db_server = mysql_connect( $db_hostname, $db_username, $db_password );
if( !$db_server )
	die( "Can't connect to mysql " . mysql_error() );

$db_database = "zoopark";

mysql_select_db( $db_database )
	or die( "Can't select data base " . mysql_error() );

$query = "CREATE TABLE cats (
		id SMALLINT NOT NULL AUTO_INCREMENT,
		family VARCHAR(32) NOT NULL,
		name VARCHAR(32) NOT NULL,
		age TINYINT NOT NULL,
		PRIMARY KEY (id) )";
$result = mysql_query($query);
if(!$result)
	echo die("FUCK\n") . mysql_error();
?>
