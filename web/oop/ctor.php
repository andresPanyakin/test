<html>
<?php 

$object1 = new User1("a", "b");
$object2 = new User2("c", "d");

$object1->name = "Joe";
$object2->name = "Amy";

echo "object1 name = " . $object1->name . "<br>";
echo "object2 name = " . $object2->name . "<br>";
$object2->password = "Mr. TROLL";
User2::pwdString();
echo $object2->getPasswd();

class User1
{
	public $name, $password;
	function User1( $param1, $param2)
	{
		echo "Saving user data...". $param1 . " " . $param2 . " ";
	}
}

class User2
{
	public $name, $password;
	function getPasswd()
	{
		return $this->password;
	}

	function __construct( $param1, $param2)
	{
		echo "Saving user data...". $param1 . " " . $param2 . " ";
	}
	function __destruct( )
	{
		echo "Fuck i die\n";
	}
	static function pwdString()
	{
		echo "Please enter password:\n";
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
