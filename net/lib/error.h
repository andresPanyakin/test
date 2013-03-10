#ifndef __ERROR_H
#define __ERROR_H
#include "unp.h"

void err_ret( const char* fmt, ... );
void err_sys( const char* fmt, ... );
void err_dump( const char* fmt, ... );
void err_msg( const char* fmt, ... );
void err_quit( const char* fmt, ... );
#endif// __ERROR_H
