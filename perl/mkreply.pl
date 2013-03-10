#!/usr/bin/perl

#Обрабатываем заголовок, который отделен от остального сообщения пустой строкой.
while( $line = <>)
{
	#Как только доходим до пустой строки, то выходим.
	if( $line =~ m/^\s*$/)
	{
		last;
	}
	#Если строка начинается с From, то мы можем выцепить адрес и имя отправителя.
	if( $line =~ m/^From: (\S+) \(([^()]*)\)/i ) 
	{
		$reply_address = $1;
		$from_name = $2;
	}

	#Если строка начинается с Subject, то можно выцепить это поле.
	if( $line =~ m/^Subject: (.*)/i)
	{
		$subject = $1;
	}

	if( $line =~ m/^Date: (.*)/i)
	{
		$date= $1;
	}

	if( $line =~ m/^Reply-To: (\S+)/i)
	{
		$reply_address= $1;
	}
}

if( not defined($reply_address) or not defined($from_name) or not defined($subject) or not defined($date) )
{
	die "couldn't get requered information!\n";
}

print "To : $reply_address ($from_name)\n";
print "From: jfriedl\@regex.info (Jeffrey Friedl)\n";
print "Subject: Re: $subject\n";
print "\n";
print "On $date $from_name wrote: \n";

#Считываем строки сообщения, при этом заменяя символ начала строки на |>
while($line = <>)
{
	$line =~ s/^/|> /;
	print $line;
}
