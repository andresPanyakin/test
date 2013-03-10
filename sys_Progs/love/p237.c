#include <sys/resource.h>
#include <sys/types.h>
#include <stdio.h>
void main(void)
{
	struct rlimit rlim;
	int ret;

	ret = getrlimit(RLIMIT_MSGQUEUE, &rlim);
	if(ret == -1)
	{
		perror("getrlim");
		return;
	}
	printf("Limit: %ld, %ld", rlim.rlim_cur, rlim.rlim_max);
	return;
}
