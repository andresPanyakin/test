<?php
require_once 'login.php';

//1-Подключаемся к СУБД mySql
$db_server = mysql_connect( $db_hostname, $db_username, $db_password );
if( !$db_server )
	die( "Can't connect to mysql " . mysql_error() );
else
	echo "Everything is OK";


//2-Теперь выбираем базу данных
mysql_select_db( $db_database )
	or die( "Can't select data base " . mysql_error() );

//3 - Теперь можем делать запросы к БД
$query = "SELECT * FROM classics";
$result = mysql_query($query); //Переменная result содержит ресурс, из которого 
			       //мы можем извлечь, все что нужно

if(!$result)
	die("Error while access to data base: " . mysql_error() );

//Получаем число строк в результате
$rows = mysql_num_rows($result);
for( $j = 0; $j < $rows; ++$j )
{
	//Извлекаем из 1ресурса 3графу в 2строке
	echo "Author: " . mysql_result($result, $j, 'author') . "<br />";
	echo "Title: " . mysql_result($result, $j, 'titile') . "<br />";
	echo "Category: " . mysql_result($result, $j, 'type') . "<br />";
	echo "Year: " . mysql_result($result, $j, 'year') . "<br />";
	echo "ISBN: " . mysql_result($result, $j, 'isbn') . "<br /><br />";
}

$res = mysql_query($query); //Переменная result содержит ресурс, из которого 
			       //мы можем извлечь, все что нужно
//2 способ - извлекаем всю строку и затем разбираем ее графы;
for( $j = 0; $j < $rows; $j++ )
{
	$row = mysql_fetch_row($res);
	echo "Author: "   . $row[0] . "<br />";
	echo "Title: " 	  . $row[1] . "<br />";
	echo "Category: " . $row[2] . "<br />";
	echo "Year: " 	  . $row[3] . "<br />";
	echo "ISBN: " 	  . $row[4] . "<br />";
}
mysql_close( $db_server);
?>
