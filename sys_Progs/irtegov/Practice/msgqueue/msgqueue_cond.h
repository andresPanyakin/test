/* 
 * File:   msgqueue_cond.h
 * Author: Dmitry V Irtegov
 *
 * Created on May 15, 2007, 12:28 AM
 */

#ifndef _msgqueue_cond_H
#define	_msgqueue_cond_H

#ifdef	__cplusplus
extern "C" {
#endif

struct queue_record {
  struct queue_record * next, *prev;
  char buf[81];
};

typedef struct myqueue {
  struct queue_record *head, *tail;
  int count;
  pthread_mutex_t queuemx;
  pthread_cond_t queuecond;
  int beingdestroyed;
} queue;

void mymsginit(queue *);
void mymsgdrop(queue *);
void mymsgdestroy(queue *);
int mymsgput(queue *, char * msg);
int mymsgget(queue *, char * buf, size_t bufsize);

#ifdef	__cplusplus
}
#endif

#endif	/* _msgqueue_cond_H */

