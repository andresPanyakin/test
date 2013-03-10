#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>

void main(void)
{
	int ret;
	ret = getpriority(PRIO_PROCESS, 0);	
	if(ret == -1)
	{
		perror("getpriority");	
		return;
	}
	printf("My prio: %d", ret);
}
