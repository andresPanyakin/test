<?php
$obj = new Tiger();
echo "Tigers has...\n";
echo "Fur: " . $obj->fur . "\n";
echo "Stripes: " . $obj->stripes . "\n";

class Wildcat
{
	public $fur;
	function __construct()
	{
		$this->fur = "TRUE";
	}
}

class Tiger extends Wildcat
{
	public $stripes;
	function __construct()
	{
		parent::__construct();
		$this->stripes="TRUE";
	}
}

//Нельзя переписать функцию со спецификатором final
class CopyRight
{
	final function copyright()
	{
		echo "This class was created by me\n";
	}
}
?>
