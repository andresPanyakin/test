#!/usr/bin/perl
$input = <STDIN>;

$input =~ s/(\.\d\d[1-9]?)\d*/$1/;
print "$input\n";
