#!/usr/bin/perl

#$regExp1 = "^([-+]?[0-9]+)([CF])\$";

$regExp2 = "^([-+]?[0-9]+(?:\.[0-9]+)?)\\s*([CF])\$";

print "Enter a temperature (e.g., 32F 100C):\n";
$input = <STDIN>;

#Удаляем символ новой строки.
chomp($input);

if( $input =~ m/$regExp2/i)
{
	#1-Введенная температура. 2-вид температуры.
	$inputTemp = $1;
	$type = $2;

	#Если тип темп-ры - "C" или "c", то вычисляем по фаренгейту.
	if( $type =~ m/c/i )
	{
		$celsius = $inputTemp;
		$fahrenheit = ( $celsius * 9 / 5 ) + 32;	
	}
	else
	{
		$fahrenheit = $inputTemp;
		$celsius= ( $fahrenheit -32 ) * 5 / 9;
	}
	printf "%.2f C is %.2f F\n", $celsius, $fahrenheit;
}
else
{
	print "Bad input: \"$input\"\n";
}
