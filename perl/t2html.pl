#!/usr/bin/perl

undef $/;
$HostNameRegEx = qr/[-\w]+(\.[-\w]+)*\.(com|edu|info)/i
$text = <>;

$text =~ s/&/&amp;/g;
$text =~ s/</&lt:/g;
$text =~ s/>/&gt:/g;
#Меняем символы конца строки на теги <p>.
$text =~ s/^\s*$/<p>/mg;

$text =~ s{
	\b(
	#Имя пользователя
	\w[-.\w]*
	\@
	#Имя хоста, важно, чтобы после точки всегда шел хотя бы один символ. 
	[-\w]+(\.[-\w]+)*
	#Домен
	\.(com|edu|info)
	)
	\b
}{<a href="mailto:$1">$1</a>}gix;

#print $text

$text =~ s{
	\b
	(
		htt(?:p|ps)://www.\w+(?:\.\w)*\.(?:com|edu|info)
		(
			/[/\w]*
		)?
	)

}{<a href="$1">$1</a>}gix;
print $text
