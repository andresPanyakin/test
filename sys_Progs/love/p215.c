#include <sched.h>
#include <stdio.h>
#include <unistd.h>
#define _GNU_SOURCE

//size_t CPU_SETSIZE;
//extern int CPU_ISSET(unsigned long cpu, cpu_set_t* set);
//extern void CPU_ZERO(cpu_set_t* set);
//extern int sched_getaffinity(pid_t pid, size_t setsize, cpu_set_t* set);

void main(void)
{
	cpu_set_t set;
	int ret, i;
	int cpu;
	CPU_ZERO(&set);
	ret = sched_getaffinity(0, sizeof(cpu_set_t), &set);

	if(ret == -1)
		perror("sched_getaffinity");

	for(i = 0; i < CPU_SETSIZE; i++)
	{
		cpu = CPU_ISSET(i, &set);
		printf("cpu=%i is %s\n", i, cpu ? "set": "unset");
		
	}
	return;
}
