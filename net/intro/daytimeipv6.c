
#include "error.h"
#include "unp.h"

int main( int argc, char** argv )
{
	int sockFd, n;
	char recvLine[ MAXLINE+1 ];
	struct sockaddr_in6 servAddr;

	if( argc != 2 )
		err_quit( "usage: %s <IP addr>\n" );	

	if( ( sockFd = socket( AF_INET6, SOCK_STREAM, 0 ) ) < 0 )
		err_sys( "Socket error\n" );

	bzero( &servAddr, sizeof(servAddr) );
	servAddr.sin6_family = AF_INET6;
	servAddr.sin_port = htons( 13 ); //Порт

	if( inet_pton( AF_INET6, argv[1], &servAddr.sin6_addr ) <= 0 )
		err_quit( "inet_pton error for %s\n", argv[1] );

	if( connect( sockFd, (SA*)&servAddr, sizeof(servAddr) ) < 0 )
		err_sys( "Connect error\n" );

	//Считываем циклическик, потому что данные могут прийти за неск. раз
	while( ( n = read( sockFd, recvLine, MAXLINE ) ) > 0 )
	{
		recvLine[n] = 0;
		if( fputs(recvLine, stdout) == EOF )
			err_sys( "fputs error\n" );
	}

	if( n < 0 )
		err_sys( "read error\n" );
	//Заодно закроем все сокеты.
	exit(0);
}

