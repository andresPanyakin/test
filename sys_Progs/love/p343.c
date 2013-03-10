#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

static void sigint_handler(int signo)
{
	printf("WHy intercept sigint!\n");
	exit(EXIT_SUCCESS);
}

int main(void)
{
	if( signal(SIGINT, sigint_handler) == SIG_ERR )
	{
		fprintf(stderr, "can't handle sigint!\n");
		exit(EXIT_FAILURE);
	}
	for(;;)
		pause();
	return 0;
}


