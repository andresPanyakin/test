#include <stdio.h>
#include <unistd.h>

int my_system(const char* command)
{
	int status;
	pid_t pid;

	pid = fork();
	if(pid == -1)
	{
		perror("fork");
		return -1;
	}
	else if(pid == 0)
	{		if( execl("/bin/sh", "sh", "-c", command, NULL) == -1)
			{
				perror("execle");
				return -1;
			}
		if(waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid");
			return -1;
		}
		return status;
	}
}
