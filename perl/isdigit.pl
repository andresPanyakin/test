#!/usr/bin/perl

print "Input string: \n";
$input = <STDIN>;
#m/../поиск совпадения, / - границы регулярного выражения.
# =~ - связывает команду поиска со строкой.
if( $input =~ m/^[0-9]+$/ )
{
	print "only digits\n";
}
else
{
	print "not only digits\n";
}
