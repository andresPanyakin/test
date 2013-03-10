<html>
<head>
</title>
</title>
</head>
<body>
<?php
	$test1 = array( "lopy","cast", "j","k", "il", "w" );
	$test2 = array( 'copy' => "past", 'a' => "b", '1l' => "2" );
	$test3 = "trololo";
	$test4 = array("z", array(1,2,3,4));

	echo "IS ARRAY------------------";
	echo "<br />";
	echo is_array($test1);
	echo "<br />";
	echo is_array($test2);
	echo "<br />";
	echo is_array($test3);
	echo "<br />";
	echo is_array($test4);
	echo "<br />";
	echo "IS ARRAY ENDS-------------";
	echo "<br />";
	echo "<br />";

	echo "COUNT------------------";
	echo "<br />";
	echo count($test1);
	echo "<br />";
	echo count($test2, 1);
	echo "<br />";
	echo count($test3);
	echo "<br />";
	//Второй параметр заставляет рекурсивно проходит все вложенные массивы
	echo count($test4, 1);
	echo "<br />";
	echo "COUNT ENDS-------------";
	echo "<br />";
	echo "<br />";

	echo "SORT------------------";
	//Есть 2 параметра: SORT_NUMERIC, SORT_STRING
	//Проведение числовой либо строковой сортировки
	echo "<br />";
	sort($test1);
	print_r($test1);
	echo "<br />";

	sort($test2, 1);
	print_r($test2);
	echo "<br />";

	sort($test4);
	print_r($test4);
	echo "<br />";
	echo "SORT ENDS-------------";
	echo "<br />";
	echo "<br />";

	echo "SHUFFLE------------------";
	echo "<br />";
	shuffle($test1);
	print_r($test1);
	echo "<br />";

	shuffle($test2);
	print_r($test2);
	echo "<br />";

	shuffle($test4 );
	print_r($test4);
	echo "<br />";
	echo "SHUFFLE ENDS-------------";
	echo "<br />";
	echo "<br />";

	echo "explode------------------";
	//Аналог сплит в питоне
	echo "<br />";
	$tmp  = explode(' ', 'ran s fdf fdas trololo afdsdaf \n');
	print_r($tmp);
	echo "<br />";
	echo "explode ENDS-------------";
	echo "<br />";
	echo "<br />";

	echo "extract------------------";
	echo "<br />";
	//Преобразует словарь в переменные
	//Если указан 2-й парам, до добавляет префикс ко всем переменным,
	//во избежание конфликта
	extract( $_GET, EXTR_PREFIX_ALL, 'fromget' );
	print_r($fromget_q);
	echo "<br />";

	echo "extract ENDS-------------";
	echo "<br />";
	echo "<br />";
	echo "compact------------------";
	echo "<br />";
	//Преобразует переменные в словарь
	$fname = "ELIZA";
	$sname = "Windzor";
	$address = "BUCH";
	$city = "LONDON";
	$newDict = compact( 'fname', 'sname', 'address', 'city', 'country');
	print_r($newDict);
	echo "<br />";

	echo "compatct ENDS-------------";
	echo "<br />";
	echo "<br />";

	echo "reset&end------------------";
	echo "<br />";
	foreach( $test1 as $iter )
	{
		echo $iter;	
		echo "<br />";
	}
	//Возвращает указатель на начало
	reset( $test1);
	echo "<br />";
	foreach( $test1 as $it )
	{
		echo $it;	
		echo "<br />";
	}
	//Перемещает указатель в конец массива
	end($test1);
	echo "<br />";
	foreach( $test1 as $itr )
	{
		echo $itr;	
		echo "<br />";
	}
	echo "resent&end ENDS-------------";
	echo "<br />";
	echo "<br />";
?>
</body>
</html>
