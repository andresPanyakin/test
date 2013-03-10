#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <alloca.h>
#include <unistd.h>

#if defined(TEST_SEM)
#include <semaphore.h>
#include "msgqueue_sem.h"
#elif defined(TEST_COND)
#include "msgqueue_cond.h"
#endif

void *producer(void *pq) {
	queue *q=(queue*)pq;
	int i=0;

	for(i=0; i<1000; i++) {
		char buf[40];
	
		sprintf(buf, "Message %d from thread %d", i, pthread_self());
		if (!mymsgput(q, buf)) return NULL;
	}

	return NULL;
}

void *consumer(void *pq) {
	queue *q=(queue *)pq;
	int i=0;

	do {
		char buf[41];
		i=mymsgget(q, buf, sizeof(buf));
		if (i==0) return NULL;
		else printf("Received by thread %d: %s\n", pthread_self(), buf);
	} while(1);
	return NULL;
}

int pleasequit=0;

void siginthandler(int sig) {
	pleasequit=1;
	signal(sig, siginthandler);
}

int main(int argc, char **argv) {
	int nproducers, nconsumers;
	pthread_t *producers, *consumers;
	queue q;
        int i;

	if (argc<2) {
		fprintf(stderr, "Usage: %s nproducers nconsumers\n", argv[0]);
		return 0;
	}
	nproducers=atol(argv[1]);
	nconsumers=atol(argv[2]);
	if (nproducers==0 || nconsumers==0) {
		fprintf(stderr, "Usage: %s nproducers nconsumers\n", argv[0]);
		return 0;
	}	

	producers=alloca(sizeof(pthread_t)*nproducers);
	consumers=alloca(sizeof(pthread_t)*nconsumers);
	signal(SIGINT, siginthandler);
	mymsginit(&q);
	for(i=0; i<nproducers || i<nconsumers; i++) {
		if (i<nproducers) {
			pthread_create(producers+i, NULL, producer, &q);
		} 
		if (i<nconsumers) {
			pthread_create(consumers+i, NULL, consumer, &q);
		}
	}
	// while (!pleasequit) pause();
        sleep(10);

	mymsgdrop(&q);
	for(i=0; i<nproducers || i<nconsumers; i++) {
		if(i<nproducers) {
			pthread_join(producers[i], NULL);
		}
		if (i<nconsumers) {
			pthread_join(consumers[i], NULL);
		}
	}
	mymsgdestroy(&q);
        printf("All threads quit and queue destroyed\n");
	return 0;	
}
