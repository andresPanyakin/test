<?php 
$object = new Son;
$object->test();
$object->test2();

class Dad
{
	function test()
	{
		echo "[Class dad] Iam father<br />";
	}
}

class Son extends Dad
{
	function test()
	{
		echo "[Class son] I am Luka<br />";
	}

	function test2()
	{
		parent::test();
	}
}
?>

