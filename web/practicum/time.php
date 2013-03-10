<html>
	<head>
	</head>
		<title>
		</title>
	<body>
		<?php 
			//Время с эпохи Unix
			echo time();
			echo time() + 7 * 24 * 60 * 60;

			//Генерация метки для заданной даты
			echo mktime( 0, 0, 0, 1, 1, 2000 );

			//Форматная строка для date
			//l:День недели полностью 
			//F: Название месяца
			//j:День месяца без лидирующих нулей
			//S:Суффикс для дня месяца
			//Y:Год - 4 цифры
			//g:Час суток (12-часовой формат)
			//i:Минуты
			//a:До или после полудния (am, pm)
			$format = "l F jS, Y - g:ia";
			$timestamp = time();
			echo date( $format, $timestamp );
			
			//Вывод в формате, используемом в RSS-потоке
			echo date( $DATE_RSS );
			echo "<br />";
			//Вывод в формате cookie, устанавливаемый веб-сервером
			//или JavaScript
			echo date( $DATE_COOKIE ) ;
			echo "<br />";
			//Вывод в формате WWW
			echo date( $DATE_W3C );
			echo "<br />";

			echo "checkdata:\n";
			echo "<br />";
			checkdate( 9, 31, 2012 )? print "OK" : print "FUck";
			echo "<br />";
		?>
	</body>
</html>

