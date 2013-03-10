<html>
<?php 
$object = new User;
print_r($object); echo "<br />";
$object->name = "Joe";
$object->password = "mypass";
print_r($object); echo "<br />";
$object->save_user();

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
