<?php
echo <<<_END
<html><head><title><PHP form for upload></title></head><body><form method='post' action='secupload.php' enctype='multipart/form-data'>Choose file: <input type='file' name='filename', size='10'/>
<input type='submit' value=Upload /></form>
_END;

if ($_FILES)
{
	$name = $_FILES['filename']['name'];
	switch($_FILES['filename']['type'])
	{
		case 'image/jpeg': $ext = 'jpg'; break;
		case 'image/gif': $ext = 'gif'; break;
		case 'image/png': $ext = 'png'; break;
		case 'image/tiff': $ext = 'tif'; break;
		default:	  $ext = '';break;
	}

	if($ext)
	{
		$name = "image.$ext";
		move_uploaded_file($_FILES['filename']['tmp_name'], "/img/".$name );
		echo "Uploaded image '$name' under the name: '$name':<br />";
		echo "<img src='/img/$name' />";
	}
	else echo "'$name' - fucking file";
}
else echo "Can't load img";
echo "</body></html>";
?>
