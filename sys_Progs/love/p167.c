#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

void main()
{
	pid_t pid;
	pid = fork();
	if(pid > 0)
		printf("I have cild with pid: %d\n", pid);
	else if(!pid)
		printf("I am child!");
	else if(pid == -1)
		perror("fork");

}
