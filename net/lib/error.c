#include "error.h"
#include <stdarg.h>
#include <syslog.h>

int daemonProc;
static void err_doit(int, int, const char* , va_list);

//Нефатальная ошибка связанная с системным вызовом. Выводим сообщение
//и возвращаем управление
void err_ret( const char* fmt, ... )
{
	va_list ap;
	va_start( ap, fmt );
	err_doit( 1, LOG_INFO, fmt, ap );
	va_end( ap );
	return;
}

//Фатальная ошибка, связанная с системным вызовом. Выводим сообщение и завершаем работу.
void err_sys( const char* fmt, ... )
{
	va_list ap;
	va_start( ap, fmt );
	err_doit( 1, LOG_ERR, fmt, ap );
	va_end( ap );
	exit( 1 );
}

/* 
 * Фатальная ошибка. Сохраняем дамп памяти и заканчиваем работу
 */
void err_dump( const char* fmt, ... )
{
	va_list ap;

	va_start( ap, fmt );
	err_doit( 1, LOG_ERR, fmt, ap );
	va_end( ap );
	abort();
	exit( 1 );
}

void err_msg( const char* fmt, ... )
{
	va_list ap;

	va_start( ap, fmt );
	err_doit( 1, LOG_INFO, fmt, ap );
	va_end( ap );
	return;
}


void err_quit( const char* fmt, ... )
{
	va_list ap;

	va_start( ap, fmt );
	err_doit( 0, LOG_ERR, fmt, ap );
	va_end( ap );
	exit( 1 );
}

static void err_doit( int errnoFlag, int level, const char* fmt, va_list ap )
{
	int errno_save, n;
	char buf[MAXLINE+1];

	errno_save = errno;
	#ifdef HAVE_VSNPRINTF
		vsnprintf( buf, MAXLINE, fmt, ap);
	#else
		vsprintf( buf, fmt, ap );
	#endif
	n = strlne( buf );
	if( errnoflag )
		snprintf( buf + n, MAXLINE - n, ": %s", strerror(errno_save) );
	strcat( buf, "\en" );

	if( daemonProc )
	{
		syslog( level, buf );
	}
	else
	{
		fflush( stdout );
		fputs( buf, stderr );
		fflush( stderr );
	}
	return;
}

