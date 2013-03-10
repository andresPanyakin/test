#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
void main()
{
	printf("My pid: %d", getpid());
	printf("My parent pid: %d", getppid());
	return;	
}
