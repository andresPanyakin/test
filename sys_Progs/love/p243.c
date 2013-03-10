#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int is_on_physical_device(int fd)
{
	struct stat sb;
	int ret;

	ret = fstat(fd, &sb);
	if(ret)
	{
		perror("fstat");
		return -1;
	}
	return gnu_dev_major(sb.st_dev);
}

int main(int argc, char* argv[])
{
	struct stat sb;
	int ret;
	int fd;
	fd = open("/home/andres/sys_Progs/buccaneer.txt", O_RDONLY);
	if(fd == -1)
	{
		perror("open");
		return -1;
	}

	printf("Sec: %d", is_on_physical_device(fd));
	close(fd);
	return 0;
}
