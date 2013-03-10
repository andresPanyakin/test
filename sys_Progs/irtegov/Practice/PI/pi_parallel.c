/* 
 * File:   pi.c
 * Author: nd159473
 *
 * Created on March 20, 2007, 6:33 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*
 * 
 */

union mynum {
		long long longlong;
		double flonum;
};

#define num_steps 200000000

int nthreads;

void * calculate(void *param) {
		double localpi=0.0;
		long long i=((union mynum *)param)->longlong;
		for (i; i< num_steps ; i+=nthreads) {
				localpi += 1.0/(i*4.0 + 1.0);
				localpi -= 1.0/(i*4.0 + 3.0);
		}
		fprintf(stderr, "Thread %lld finished, partial sum %.16f\n", 
						((union mynum *)param)->longlong,
						localpi);
		((union mynum *)param)->flonum=localpi;
		return param;
}

int
main(int argc, char** argv) {
    
    double pi = 0;
    int i;
	pthread_t * ids;
	union mynum * params;
    
	if (argc >= 1) nthreads=atol(argv[1]);
	if (nthreads < 1) { 
			fprintf(stderr, "usage: %s threadnum\n", argv[0]);
			exit(0);
	}
	
	params=malloc(nthreads*sizeof(union mynum));
	ids=malloc(nthreads*sizeof(pthread_t));				
    for(i=0; i< nthreads; i++) {
			params[i].longlong=i;
			pthread_create(ids+i, NULL, calculate, (void*)(params+i));
	}
  	
	for(i=0; i<nthreads; i++) {
			union mynum * res;
			pthread_join(ids[i], (void **)&res);
    		pi+=res->flonum;
	}
	pi *= 4.0;
	printf ("pi = %.16f\n", pi);

    return (EXIT_SUCCESS);
}

