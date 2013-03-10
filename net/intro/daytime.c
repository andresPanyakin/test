#include "error.h"
#include "unp.h"

int main( int argc, char** argv )
{
	int sockFd, n;
	char recvLine[ MAXLINE+1 ];
	struct sockaddr_in servAddr;

	if( argc != 2 )
		err_quit( "usage: %s <IP addr>\n" );	

	//Вставляем пробел между двумя открывающимися скобками, чтобы 
	//указать на то, что левая часть операции сравнения содержит операцию присванивания
	//Создаем потоковый сокет Интернета (TCP-сокет)
	if( ( sockFd = socket( AF_INET, SOCK_STREAM, 0 ) ) < 0 )
		err_sys( "Socket error\n" );

	//Используем ее а не memset, т.к. случайная 
	//перестановка аргументов будет выявлена компилятором
	bzero( &servAddr, sizeof(servAddr) );
	//Заполняем структуру адреса сокета Интернета
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons( 13 ); //Порт

	//presentation to numeric:преобразует символы ASCII(1.1.1.1) в двоичный формат
	if( inet_pton( AF_INET, argv[1], &servAddr.sin_addr ) <= 0 )
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

