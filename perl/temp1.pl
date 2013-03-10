#!/usr/bin/perl
print "Enter a temperature in celsius\n";

#Устанавливаем, что в строке только число.
$regExp1 = "^[0-9]+\$";

#В строке может быть дробное и знаковое число.
$regExp2 =  "^[-+]?[0-9]+(\.[0-9]+)?\$";

$celsius = <STDIN>;
#Удалить завершающия символ новой строки
chomp($celsius);

if( $celsius =~ m/$regExp2/)
{
	$fahreheit = ( $celsius * 9 / 5 ) +32;
	print "$celsius C is $fahreheit F\n";
}
else
{
	print "Expecting a number!Your input: \"$celsius\"\n"
}
