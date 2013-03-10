#include <semaphore.h>
#include <stdio.h>

int main(int argc, char ** argv) {
	if (argc <= 1) {
		fprintf(stderr, "Usage: %s semaphore\n", argv[0]);
		return 0;
	}
	if (sem_unlink(argv[1])) {
		perror("sem_unlink");
	}
	return 0;
}
