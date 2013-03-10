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
    /* 
     * Note that we cannot use printf(3C) on Solaris and Linux.
     * write(2) contains implicit cancellation point,
     * and printf(3C) does not.  If you need to use printf(3C),
     * use explicit pthread_testcancel(3C).
     * 
     * POSIX specification says that write(2) SHOULD contain 
     * implicit cancellation point and printf(3C) MAY contain it.
     *
     * Solaris implementation seems counterintuitive to me,
     * but this behavior is acceptable by the standard.
     * Linux probably just follows Solaris tradition.
     */
    for(;;)
        write(0, "Child\n", 6);

    return NULL; /* never reach this point */
}

/*
 * creates thread with default attributes and no parameters
 * exits with pthread_exit to make existence of other threads (if any) visible. 
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
    
    pthread_exit(NULL);   
    return (EXIT_SUCCESS);
}
