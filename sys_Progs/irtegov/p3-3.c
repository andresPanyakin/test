#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void* thread_body(void* unused)
{
	pthread_t self;
	int code;
	self = pthread_self();

	code = pthread_join(self, NULL);
	printf( "Joining self before detach, error code = %d, message %s\n", code, strerror(code) );
	pthread_detach(self);
	code = pthread_join(self, NULL);
	printf( "Joinig self after detach, error code = %d, message %s\n", code, strerror(code) );
	return NULL;
}

int main(void)
{
	pthread_t thread;
	pthread_create(&thread, NULL, &thread_body, NULL);
	pthread_exit(NULL);
	return 0;
}
