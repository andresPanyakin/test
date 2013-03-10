/* 
 * File:   pthread_create.c
 * Author: Dmitry V Irtegov
 *
 * Created on March 9, 2007, 11:32 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

/*
 * Thread body
 * param is ignored
 */

void * thread_body(void * param) {
    for(;;)
        write(0, "Child\n", 6);
}

/*
 * creates thread with default attributes and no parameters
 * exits with pthread_exit to allow thread execution
 */
int main(int argc, char *argv[]) {
    pthread_t thread;
    int code;
    void * result;
    
    code=pthread_create(&thread, NULL, thread_body, NULL);
    if (code!=0) {
        char buf[256];
        strerror_r(code, buf, sizeof buf);
        fprintf(stderr, "%s: creating thread: %s\n", argv[0], buf);
        exit(1);
    }
    
    sleep(2);
   
    code=pthread_cancel(thread);
    if (code!=0) {
        char buf[256];
        strerror_r(code, buf, sizeof buf);
        fprintf(stderr, "%s: cancelling thread: %s\n", argv[0], buf);
        exit(1);
    }

    pthread_join(thread, &result);
    printf("Cancelled, result %p\n", result);
    
    pthread_exit(NULL);   
    return (EXIT_SUCCESS);
}

