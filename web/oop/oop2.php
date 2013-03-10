<html>
<?php 
$object1 = new User();
$object1->name = "Joe";
$object2 = clone $object1;
$object2->name = "Amy";
echo "object1 name = " . $object1->name . "<br>";
echo "object2 name = " . $object2->name . "<br>";

class User
{
	public $name, $password;
	function save_user()
	{
		echo "Saving user data...";
	}
}
?>

	<head>Trololo
	</head>
		<title>
			trololo
		</title>
	<body>
	</body>
<html>
