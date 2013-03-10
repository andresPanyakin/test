<html>
	<head>
	</head>
		<title>
		</title>
	<body>
		<?php 
			$cmd = "ls -al";

			exec( escapeshellcmd( $cmd ), $output, $status );
			if( $status ) echo "Can't exeec";
			else
			{
				echo "<pre>";
				foreach( $output as $line ) echo "$line\n";
			}
		?>
	</body>
</html>
