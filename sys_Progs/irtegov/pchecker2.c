#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

pthread_cond_t fileopen_cond=PTHREAD_COND_INITIALIZER; 
pthread_mutex_t fileopen_mutex=PTHREAD_MUTEX_INITIALIZER; 

void main(void)
{
	int ret = 0;
#if defined(_LIBC_REENTRANT) 
	   printf("_LIBC_REENTRANT defined as %d\n", _LIBC_REENTRANT); 
	    #endif 

	    #if defined(_REENTRANT) 
	      printf("_REENTRANT defined as %d\n", _REENTRANT); 
	       #endif 

	       #if defined(_TS_ERRNO) 
	         printf("_TS_ERRNO defined as %d\n", _TS_ERRNO); 
		  #endif 

		  #if defined(_POSIX_C_SOURCE)
		    printf("_POSIX_C_SOURCE defined as %d\n", _POSIX_C_SOURCE); 
		     #endif 
		
		    ret = open_with_wait("/home/andres/nohup.out", O_WRONLY, 0644);
		    if(ret < 0)
			    perror("open_with_wait");
		    printf("ret: %d\n", ret);
		    ret = close_with_wakeup(ret);
		    if(ret < 0)
			    perror("close_with_wake_up");
		    return;

}
int open_with_wait(const char *pathname, int flags, mode_t mode) { 
	   int code;
	      pthread_mutex_lock(&fileopen_mutex);
	         do {
		      code=open(pathname, flags, mode);
			           if (code < 0 && errno==EMFILE) {
					           pthread_cond_wait(&fileopen_cond, &fileopen_mutex); 
						        } 
							   } while (code < 0 && errno==EMFILE);
							      pthread_mutex_unlock(&fileopen_mutex); 
							         return code; 
} 

int close_with_wakeup(int handle) { 
	   int code;
	      code=close(handle); 
	         pthread_cond_signal(&fileopen_cond); 
		    return code; 
}

