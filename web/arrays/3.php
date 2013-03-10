<html>
<head>
</title>
</title>
</head>
<body>
<?php
	$p = array( 'copy' => "past", 'a' => "b", '1l' => "2" );
	$j = 0;
	$k = 0;
	echo "<pre>";
	foreach( $p as $i=>$descr)
	{
		echo "$i: $descr<br>";
	}

	while(list($it, $desc) = each($p))
		echo "$it: $desc<br>";
	echo "</pre>";
?>
</body>
</html>
