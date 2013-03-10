#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(void)
{
	int pid;
	puts("Who is there?");
	pid=fork();
	if(pid == 0)
	{
		printf("I'm child pid[%d]\n", getpid());
	}

	else if(pid > 0)
	{
		sleep(5);
		printf("I'm parent pid[%d]\n", getpid());
	}
	else{
		perror("For error");
		return -1;
	}
	wait(pid);
	return 0;
}
