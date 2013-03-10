#include <stdio.h>
#include <sched.h>

void main(void)
{
	struct timespec tp;
	int ret;
	
	ret = sched_rr_get_interval(3939, &tp);
	if(ret == -1)	
	{
		perror("sched_rr_get_interval");
		return 1;	
	}
	printf("Quan: %.2lf\n", (tp.tv_sec * 1000.0f)+ (tp.tv_nsec / 1000000.0f));
	return;
}
