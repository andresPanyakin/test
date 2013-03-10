/* File:   p_c_funny.c
 * 
 * producer-consumer implementation on mutexes using cyclical lock/unlock.
 * DO NOT USE THIS IN PRODUCTION CODE, there are better way to implement producer/consumer interaction.
 * However, inventing this is a good intellectual exercise.
 * This solution relies on idle loop and generally too complex to be useful.
 * Author: Dmitry V Irtegov, NSU
 * Idea: Alexey Semenov, Unipro
 *
 * Created on May 17, 2007, 13:57 AM
 */

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

pthread_mutex_t m[3];
int printed=0;  /* flag for idle loop */

#define ITERATIONS 4

void* print_message ( void* str ){
    int i = 0;
    int k = 1;
    int err;
   
   pthread_mutex_lock( &m[2]);
   if (printed) pthread_mutex_unlock(&m[0]); /* guess why? */
   for ( i = 0; i < ITERATIONS*3; i++ ){
        if (err=pthread_mutex_lock(&m[k])) 
            printf("%s Gotcha! - lock %d, error %s\n", str, k, strerror(err));
        k=(k+1)%3;
        if (err=pthread_mutex_unlock(&m[k])) 
            printf("%s Gotcha! - unlock %d, error %s\n", str, k, strerror(err));
        if (k==2) { 
            printf("Message : %s\n", (char*)str);
            printed=1;
        }
        k=(k+1)%3;
    }
    pthread_mutex_unlock( &m[2] );    
    return NULL;
}

int main ( int argc, char* argv ){
    pthread_t pthread;
    pthread_mutexattr_t mattr;
    int i=0;
    int err;
    
    /* ensuse we do everything right and do not do bad thing to mutexes */
    pthread_mutexattr_init(&mattr);
    if (pthread_mutexattr_settype(&mattr, PTHREAD_MUTEX_ERRORCHECK)) printf("boo\n");

    for (i=0; i<3; i++) pthread_mutex_init(&m[i], &mattr);
    
    pthread_mutex_lock(&m[0]);
    if ( err = pthread_create (&pthread, NULL, print_message, (void*)"child" )){
	fprintf ( stderr, "Error in creating thread %s\n", strerror(err));
        exit(0);
    }

    /* idle loop! on multiprocessor single sched_yield() isn't enough */
    while (!printed) { sched_yield(); }

    print_message ( (void*) "parent" );

    pthread_join(pthread, NULL);
    for (i=0; i<3; i++) pthread_mutex_destroy( &m[i] );

    printf("\n");
    pthread_exit (NULL);    
	return NULL; /* for lint */
}


