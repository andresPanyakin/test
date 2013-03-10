<html>
	<head>
	</head>
		<title>
		</title>
	<body>
		<?php  //str.php
			echo "GLOBALS: ";
			for ($j=0; $j<4; ++$h)
				echo "$j: $GLOBALS[$j]<br>";
			echo "<br />";
			echo "<br />";
			echo "SERVER: ";
			print_r($_SERVER);
			echo "<br />";
			echo "<br />";
			echo "GET: ";
			print_r($_GET);
			echo "<br />";
			echo "<br />";
			echo "POST: ";
			print_r($_POST);
			echo "<br />";
			echo "<br />";
			echo "FILES: ";
			print_r($_FILES);
			echo "<br />";
			echo "<br />";
			echo "COOKIE: ";
			print_r($_COOKIE);
			echo "<br />";
			echo "<br />";
			echo "SESSION: ";
			print_r($_SESSION);
			echo "<br />";
			echo "<br />";
			echo "REQUEST: ";
			print_r($_REQUEST);
			echo "<br />";
			echo "<br />";
			echo "ENV: ";
			print_r($_ENV);
			echo "<br />";
			echo "<br />";
		?>
	</body>
<html>
