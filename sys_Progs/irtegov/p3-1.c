#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

void* thread_body(void* param)
{
	sleep(1);
	printf("Child\n");
}

int main(int argc, char* argv[])
{
	pthread_t thread;
	int code, i;

	code = pthread_create(&thread, NULL, thread_body, NULL);
	if( code != 0 )
	{
		char buf[256];
		strerror_r( code, buf, sizeof(buf) );
		fprintf(stderr, "%s: creating thread: %s\n", argv[0], buf);
		exit(1);
	}
	sleep(5);
	return ( EXIT_SUCCESS );
}
