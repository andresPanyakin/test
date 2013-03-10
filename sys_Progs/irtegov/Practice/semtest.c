#include <semaphore.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

const char * semname="/printa", * semname2="/printb";
pid_t child;

void cleanup(void) {
	sem_unlink(semname);
	sem_unlink(semname2);
}

void sighandler(int sig) {
	kill(child, SIGTERM);
	exit(0);
}

int main() {
	sem_t * sem1, *sem2;
	int sem1v, sem2v;
  
	atexit(cleanup);
	sem1=sem_open(semname, O_CREAT | O_EXCL, 0600, 0);

	if (sem1==SEM_FAILED) {
		perror("sem_open");
		exit(0);
	}
	sem2=sem_open(semname2, O_CREAT | O_EXCL, 0600, 1);

	if (sem2==SEM_FAILED) {
		perror("sem_open");
		exit(0);
	}

	if (child=fork()) {
		signal(SIGINT, sighandler);
		while(1) {
			sem_wait(sem1);
			sem_getvalue(sem1, &sem1v);
			sem_getvalue(sem2, &sem2v);
			printf("Child %d, %d\n", sem1v, sem2v);
			sem_post(sem2);
		}
	} else {
		if (child<0) {
			perror("fork:");
			exit(1);
		}
		signal(SIGINT, SIG_IGN);
		while(1) {
			sem_wait(sem2);
			sem_getvalue(sem1, &sem1v);
			sem_getvalue(sem2, &sem2v);
			printf("Parent %d %d\n", sem1v, sem2v); 
			sem_post(sem1);
		}
	}
}
