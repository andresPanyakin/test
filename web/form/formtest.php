<?php
if( isset( $_POST['name'] ) )
	$name = $_POST[ 'name' ];
else 
	$name = "Not entered";

//$name = htmlentities($name);
//$name = stripslashes($name);
$name = strip_tags($name);
echo <<<_END
<html>
	<head>
		<title>Form Test</title>
	</head>
	<body>
		Your name: $name <br />
		<form method="post" action="formtest.php" />
			FUck!
		<input type="text" name="name" value="Hui"/>
		<br />
		<textarea name="Name" cols="5" rows="5" wrap="soft">
		TROLOLOLO
		</textarea>
		<br />
		I agree <input type="checkbox" name="A[]" value="agree" />
		I not<input type="checkbox" name="A[]" value="not agree" />
		I fuck<input type="checkbox" name="A[]" value="Fuck" checked="checked" />
		<br />
		<label>8.00-12.00<input type="radio" name="time" value="1" /></label>|
		12.00-16.00<input type="radio" name="time" value="2" checked="checked" />|
		16.00-20.00<input type="radio" name="time" value="3" />|
		<input type="submit" value="TROLOLO" src="1.jpg"/>
		<br />
		TTTT<br /><select name="CHOOSE" size="1" multiple="multiple">
		<option value="GOROG">GOROG</option>
		<option value="TROLL">TROLL</option>
		<option value="SDFSd">SDFSd</option>
		<option selected="selected" value="GGGGGG">GGGGGG</option>
		<option value="GORO">GORO</option>
		</select>


		</form>
	</body>
</html>
_END;

if( isset($_POST['A']) )
	foreach($_POST['A'] as $item)
		echo "$item<br />";

?>
