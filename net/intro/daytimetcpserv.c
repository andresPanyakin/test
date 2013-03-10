#include "unp.h"
#include <time.h>

int main( int argc, char** argv )
{
	int listenFd, connFd;
	struct sockaddr_in servAddr;
	char buf[MAXLINE];
	time_t ticks;

	listenFd = Socket( AF_INET, SOCK_STREAM, 0 );
	bzero( &servAddr, sizeof(servAddr) );
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl( IN_ADDR_ANY ); //Принимаем соединение на любом интерфейсе
	servAddr.sin_port = htons( 13 );

	//Связывание порта сервера(13) связывается с сокетом listenFd
	Bind( listenFd, (SA*)&servAddr, sizeof(servAddr) );
	//Преобразуем сокет в прослушивающий сокет.
	Listen( listenFd, LISTENQ );

	for(;;)
	{
		//Блокируемся до прихода соединения
		//Вернет нам присоединенный дескритор
		//мы можем использовать его для связи с новым клиентом
		connFd = Accept( listenFd, (SA*)NULL, NULL );
		ticks = time( NULL );
		snprintf( buf, sizeof(buf), "%.24s\r\n", ctime( &ticks ) );
		Write( connFd, buf, strlen( buf ) );
		Close( connFd );
	}
	return 0;
}

