#include <unistd.h>

void main()
{
	int ret;
	ret = execl("/usr/bin/vim", "vim", NULL);
	if(ret == -1)
		perror("execl");
	return;
}
