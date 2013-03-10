<html>
<?php

$obj = new Subscriber;
$obj->name = "Fred";
$obj->password = "pword";
$obj->phone = "01235";
$obj->email = "fred@blocs.com";
$obj->display();

class User
{
	public $name, $password;
	function User()
	{
		echo "Saving user data...";
	}
}

class Subscriber extends User
{
	public $phone, $email;
	function display()
	{
		echo "name: " . $this->name . "<br />";
		echo "pass: " . $this->password . "<br />";
		echo "phone: " . $this->phone . "<br />";
		echo "email: " . $this->email. "<br />";
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
