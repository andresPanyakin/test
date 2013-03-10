#include <malloc.h>
#include <stdio.h>

void main(void)
{
	size_t len = 21;
	size_t size;
	char* buf;
	
	buf = malloc(len);
	if(!buf)	
	{
		perror("malloc");
		return -1;	
	}

	size = malloc_usable_size(buf);
	printf("%d\n", size);
	return ;
}
