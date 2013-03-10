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

void cancel_handler(void * arg) {
    /* 
     * generally, mixing printf and write on same stream is bad idea
     * however, in this program we never will call printf from inside of write. 
     * that's what DEFERRED_CANCEL was invented for.
     */
    printf("%s\n", (char*)arg);
    /* put your cleanup code here */
}

void * thread_body(void * param) {

    pthread_cleanup_push(cancel_handler, (void *)"We are being cancelled!!!");
    
    for(;;)
        write(0, "Child\n", 6);
    
    /* 
     * We never will get here in this program, compiler gives warning about this. 
     * But we need to match pthread_cleanup_push(3C) with pthread_cleanup_pop(3C)
     * check pthread.h source to see why.
     * Or just comment out next line and try to compile.
     */
    pthread_cleanup_pop(0);
	return NULL;
}

/*
 * creates thread with default attributes and no parameters
 * exits with pthread_exit to allow thread execution
 */
int main(int argc, char *argv[]) {
    pthread_t thread;
    int code;
    
    code=pthread_create(&thread, NULL, thread_body, NULL);
    if (code!=0) {
        char buf[256];
        strerror_r(code, buf, sizeof buf);
        fprintf(stderr, "%s: creating thread: %s\n", argv[0], buf);
        exit(1);
    }
    
    sleep(2);
   
    printf("Trying to cancel\n");
    code=pthread_cancel(thread);
    if (code!=0) {
        char buf[256];
        strerror_r(code, buf, sizeof buf);
        fprintf(stderr, "%s: cancelling thread: %s\n", argv[0], buf);
        exit(1);
    }

    pthread_join(thread, NULL);
    printf("Cancelled\n");
    
    /* this is to demonstrate that thread is ended by pthread_cancel(3C),
     * not by exit(2) */
    pthread_exit(NULL);   
    return (EXIT_SUCCESS);
}
