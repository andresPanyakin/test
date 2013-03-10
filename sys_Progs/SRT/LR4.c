#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	int outfile;	

	if( ( outfile = dup(1) ) == -1 )
		return -1;
	close(1);
	if( (outfile = open("1.dat", O_WRONLY|O_TRUNC|O_CREAT, 00644) ) >=0 )
	{
		execl("/bin/ps", NULL);
	}

	return 0;
}
