/* 
 * File:   pi.c
 * Author: nd159473
 *
 * Created on March 20, 2007, 6:33 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>

/*
 * 
 */

union mynum {
    long long longlong;
    double flonum;
};

#define num_steps_per_check 1000000

int nthreads;
int pleasequit=0;
long long maxiterations=0;
pthread_mutex_t maxiter_mutex=PTHREAD_MUTEX_INITIALIZER;

void * calculate(void *param) {
    double localpi=0.0;
    long long threadno=((union mynum *)param)->longlong;
    long long i=threadno;
    long long tocheck;
    pthread_mutex_lock(&maxiter_mutex);
    while(!pleasequit || i<maxiterations+threadno) {
            tocheck=i+num_steps_per_check*nthreads;
            if (tocheck>maxiterations && !pleasequit) maxiterations=tocheck;
        pthread_mutex_unlock(&maxiter_mutex);
        
        for (i; i< tocheck ; i+=nthreads) {
            localpi += 1.0/(i*4.0 + 1.0);
            localpi -= 1.0/(i*4.0 + 3.0);
        }
        fprintf(stderr, "Thread %lld working, %lld iterations passed\n", 
                    threadno,
                    i-threadno);
        
        pthread_mutex_lock(&maxiter_mutex);
    }
    
    pthread_mutex_unlock(&maxiter_mutex);
    
    fprintf(stderr, "Thread %lld finished, %lld iterations, partial sum %.16f\n", 
                    threadno,
                    i-threadno,
                    localpi);
    ((union mynum *)param)->flonum=localpi;
    return param;
}

void handlesigint2(int sig) {
    fputs("Wait, I'm quitting right now...\n", stderr);
    signal(sig, handlesigint2);
}

void handlesigint(int sig) {
    pleasequit=1;
    signal(sig, handlesigint2);
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
    signal(SIGINT, handlesigint);
    
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

