#include <semaphore.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

const char * semname="/printa", * semname2="/printb";
pid_t child;

void sighandler(int sig) {
	sem_unlink(semname);
	sem_unlink(semname2);
	kill(child, SIGINT);
	wait(NULL);
	exit(0);
}

int main() {

	sem_t * sem1=sem_open(semname, O_CREAT, 0600, 1);
	sem_t * sem2=sem_open(semname2, O_CREAT, 0600, 0);
	int sem1v, sem2v;

	if (child=fork()) {
		sem_t * sc1, *sc2;
		if (child<0) {
			perror("fork:");
			exit(1);
		}
		sem_close(sem1);
		sem_close(sem2);
		sc1=sem_open(semname, 0);
		if (sc1==SEM_FAILED) {
			perror("sem_open:");
			exit(1);
		}
		sc2=sem_open(semname2, 0);
		if (sc2==SEM_FAILED) {
			perror("sem_open:");
			exit(1);
		}
		while(1) {
			sem_wait(sc1);
			sem_getvalue(sc1, &sem1v);
			sem_getvalue(sc2, &sem2v);
			printf("Child %d, %d\n", sem1v, sem2v);
			sem_post(sc2);
		}
	} else {
		signal(SIGINT, sighandler);
		while(1) {
			sem_wait(sem2);
			sem_getvalue(sem1, &sem1v);
			sem_getvalue(sem2, &sem2v);
			printf("Parent %d %d\n", sem1v, sem2v); 
			sem_post(sem1);
		}
	}
}
