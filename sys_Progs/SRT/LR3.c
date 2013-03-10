#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int pid2, pid3, st;	
	printf("I'm parent: %d\n", getpid() );
	pid2 = fork();

	if(pid2 == 0)
	{
		printf("I'm first child, my pid: %d\n", getpid() );
		pid3 = fork();

		if(pid3 == 0)
		{
			printf("I'm sec child: my pid: %d\n", getpid());
			sleep(5);
			printf("sec child is finished\n");
			return 0;
		}

		if(pid3 < 0)
			printf("Can't create process 3: error %d\n");
		sleep(2);
		printf("First child is finished\n");
		wait(&st);
		printf("Final exit second: %d\n", st);
		return -10;
	}

	else {
		printf("Parent is finished\n");
		if(pid2 < 0)
			printf("can't create process 2: error %d\n", pid2);
	}
	wait(&st);
	printf("Final exit first: %d\n", st);
	return 0;
}
