<?php
require_once 'login.php';

//Инициализация
$db_server = mysql_connect( $db_hostname, $db_username, $db_password );
if( !$db_server )
	die( "Can't connect to mysql " . mysql_error() );

mysql_select_db( $db_database )
	or die( "Can't select data base " . mysql_error() );

//Проверяем, надо ли нам что-нибудь удалить
if( isset($_POST['isbn']) )
	$isbn = get_post('isbn');

if( isset($_POST['delete']) && $isbn != "" )
{
	$query = "DELETE FROM classics WHERE isbn='$isbn'";
	if( !mysql_query($query, $db_server) )
		echo "Can't dele data: $query<br />" . mysql_error() . "<br /><br />";
}

//Сохраняем присланные параметры 
else if(isset($_POST['author']) &&
	isset($_POST['title']) &&
	isset($_POST['category']) &&	
	isset($_POST['year']) &&
	isset($_POST['isbn']) )	
{
	$author = get_post('author');
	$title  = get_post('title');
	$category = get_post('category');
	$year = get_post('year');
	$isbn = get_post('isbn');

	//Отсылаем запрос на вставку
	$query = "INSERT INTO classics VALUES" . "('$author', '$title', '$category', '$year' , '$isbn')";
	if(!mysql_query($query, $db_server))
		echo "can't insert data: $query<br />" . mysql_error();
}

//Выводим форму для добавки записей
echo <<<_END
	<form action="sqltest.php" method="post"><pre>
	Author <input type="text" name="author" />
	Title <input type="text" name="title" />
	Category <input type="text" name="category" />
	Year <input type="text" name="year" />
	ISBN <input type="text" name="isbn" />
	<input type="submit" value="ADD RECORD" />
</pre></form>
_END;

//Получаем всю таблицу
$query = "SELECT * FROM classics";
$result = mysql_query($query);
if(!$result) die("FUCK");

//Выводим все записи, а под ними кнопку "Удалить"
$rows = mysql_num_rows($result);
for($j = 0; $j < $rows; $j++)
{
	$row = mysql_fetch_row($result);
	echo <<<_END
	<pre>
	Author $row[0]
	Title $row[1]
	Category $row[2]
	Year $row[3]
	ISBN $row[4]
	</pre>
	<form action="sqltest.php" method="post">
	<input type="hidden" name="delete" value="yes" />
	<input type="hidden" name="isbn" value="$row[4]" />
	<input type="submit" value="DELETE RECORD"	/>
	</form>
_END;
}
//Завершаем работу
mysql_close($db_server);

function get_post($var)
{
	return mysql_real_escape_string($_POST[$var]);
}
?>
