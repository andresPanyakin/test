#ifndef __unp_h
#define __unp_h

#include "../config.h"

#include <sys/types.h> 		//Основные системные типы данных
#include <sys/socket.h> 	//Основные определения сокетов
#include <sys/time.h> 		//Структура timeval{} для select()	
#include <time.h>		//Структура timespec{} для pselect()		
#include <netinet/in.h>		//Структура sockadd_in{} и другие сетевые определения
#include <arpa/inet.h>		//inet(3) функции
#include <errno.h>
#include <fcntl.h>		//для неблокируемых сокетов
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/un.h>		//Для доменных сокетов UNIX

#ifndef HAVE_BZERO
#define bzero(ptr,n) 	memset( ptr, 0, n)
#endif

#define MAXLINE 4096
#define BUFFSIZE 8192
#define SERV_PORT 9877
#define SERV_PORT_STR "9877"

#define SA struct sockaddr

#endif //__unp_h
