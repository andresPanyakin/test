<html>
	<head>
	</head>
		<title>
		</title>
	<body>
		<?php 
			//Проверка существования файла
			if( file_exists("time.php") )
				echo "File Exists";
			echo "<br/>";

			if( !file_exists("trololo.txt") )
				echo "File not Exists";

			echo "<br />";
			$fh = fopen("/opt/lampp/htdocs/trololo.txt", "w") or die("Can't create file");
			$text = <<<_END
				A
				B
				C
				D
_END;
			print_r($fh);
			echo "<br />";
			//Выставляем блокировку
			flock($fh, LOCK_EX);
			fwrite( $fh, $text) or die("Can't write to file");
			//Сбрасываем блокировку
			flock($fh, LOCK_UN);
			fclose($fh);
			echo "Succes write\n";

			if(!unlink('/opt/lampp/htdocs/trololo.txt'))
				echo "can't delete fucking file";
			else
				echo "file removed\n";

			//Считывание всего файла целиком, можно задать и Url.
			echo file_get_contents("https://www.google.com");
		?>
	</body>
</html>

