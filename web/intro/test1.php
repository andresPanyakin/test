<html>
<?php 
function longdate($timestamp)
{
	
	$temp = date( "l F js Y ", $timestamp );
	return "Дата: $temp";
}

?>

	<head>Trololo
	</head>
		<title>
			trololo
		</title>
	<body>
		<?php  //test1.php
		echo __LINE__;
		echo "\n";
		echo __FILE__;
		echo "\n";
		echo __DIR__;
		echo "\n";
		echo __FUNCTION__;
		echo "\n";
		echo __METHOD__;
		echo "\n";
		echo __NAMESPACE__;
		echo longdate(time());
		echo "\n";
		echo __NAMESPACE__;
		echo "a:[" . (20 > 9) . "]<br />";
		echo "b:[" . (5 == 6) . "]<br />";
		echo "c:[" . (1 == 0) . "]<br />";
		echo "d:[" . (1 == 1) . "]<br />";
		$a="1000";
		$b="+1000";
		echo !$a;
		echo "<br />";
		if($a==$b) echo "1";
		if(!$a===!$b) echo "2";
		
		?>
	</body>
<html>
