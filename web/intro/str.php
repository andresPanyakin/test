<html>
<?php 
include_once "test.php";
function fixNames(&$n1, &$n2, &$n3)
{
	
	$n1 = ucfirst(strtolower($n1));
	$n2 = ucfirst(strtolower($n2));
	$n3 = ucfirst(strtolower($n3));
}
?>

	<head>Trololo
	</head>
		<title>
			trololo
		</title>
	<body>
		<?php  //str.php
		$a1 = "WILLIAM";
		$a2 = "henry";
		$a3 = "gatES";
		echo strrev(" .dlrow olleH");
		echo str_repeat("Hip ", 2);
		echo strtoupper("hooray!\n");
		echo ucfirst("first letter in uppercase\n");
		echo $a1 . " " . $a2 . " " . $a3 . "\n";
		echo fixNames($a1, $a2, $a3);
		echo $a1 . " " . $a2 . " " . $a3;
echo "<br />";
	print_r($_GET);
		?>
	</body>
<html>
