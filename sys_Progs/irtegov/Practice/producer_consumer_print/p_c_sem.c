#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <string.h>

sem_t s1;
sem_t s2;


void* print_message ( void* str ){
    int i = 0;
    for ( i = 0; i < 10; i++ ){
	sem_wait(&s2);	
	printf ( "Message : %s\n",(char*) str );
	sem_post(&s1);	
    }
    return NULL;
}

int main ( int argc, char* argv ){
    pthread_t thread;
    int i = 0;
    int err;

    sem_init ( &s1, 0, 0 );
    sem_init ( &s2, 0, 1 );

    if ( err = pthread_create (&thread, NULL, print_message, (void*)"child" )){
	fprintf ( stderr, "Error in creating thread: %s\n", strerror(err));
    }

    for ( i = 0; i < 10; i++ ){
	sem_wait(&s1);
	printf ( "Message : parent\n" );
	sem_post(&s2);
    }

    pthread_join(thread, NULL);

    sem_destroy(&s1);
    sem_destroy(&s2);
    pthread_exit (NULL);    
	return NULL; /* for lint */
}
