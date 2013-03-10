#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int pid = 0;
	pid = fork();
	if(!pid)	
	printf("123");
	else
	printf("456");
	return 0;
}
