<?php
echo <<<_END
<html><head><title>Upload php form</title></head><body><form method='post' action='upload.php' enctype='multipart/form-data'>Choose file: <input type='file' name='filename' size='10'/><input type='submit' value='upload' /></form>
_END;
	if($_FILES)
	{
		$name = $_FILES['filename']['name'];
		$path = "/img/".$name;
		move_uploaded_file($_FILES['filename']['tmp_name'], $path);
		echo "Downloaded image $name <br/><img src='$path' />";
	}
	echo "</body></html>";
?>

