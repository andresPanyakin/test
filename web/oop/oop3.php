<html>
<?php 
echo "<br />";
echo Translate::lookUp();
$tmp = new Test();
echo "Test A: " . Test::$prop . "<br />";
echo "Test B: " . $tmp->get_sp() . "<br />";
echo "Test C: " . $tmp->prop .  "<br />";

class Translate 
{
	const ENGLISH=1;
	const GERMAN=2;
	static function lookUp()
	{
		echo self::GERMAN;
	}
}

class Test
{
	static $prop = "This is static property\n";	
	function get_sp()
	{
		return self::$prop;
	}
}

?>
	<head>
	</head>
		<title>
		</title>
	<body>
	</body>
</html>
