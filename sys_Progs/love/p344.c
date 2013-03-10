#include <stdlib.h> 
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

static void signal_handler(int signo)
{
	if( signo == SIGINT)
		printf("Intercept SIGINT!\n");
	else if( signo == SIGTERM)
		printf("Intercept SIGTERM!\n");
	else
	{
		fprintf(stderr, "Unwaited signal!\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

int main(void)
{
	if( signal(SIGINT, signal_handler) == SIG_ERR)
	{
		fprintf(stderr, "can't handle sigint!\n");
		exit(EXIT_FAILURE);
	}

	if( signal(SIGTERM, signal_handler) == SIG_ERR)
	{
		fprintf(stderr, "can't handle sigterm!\n");
		exit(EXIT_FAILURE);
	}

	if(signal(SIGPROF, SIG_DFL) == SIG_ERR)
	{
		fprintf(stderr, "can't handle sigprof!\n");
		exit(EXIT_FAILURE);
	}

	if( signal(SIGHUP, SIG_IGN) == SIG_ERR)
	{
		fprintf(stderr, "can't handle sighup!\n");
	}
	for(;;)
		pause();
	return 0;
}
