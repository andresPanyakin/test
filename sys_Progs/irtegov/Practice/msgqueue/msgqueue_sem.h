/*
 * message queue interface
 * implemented with the semaphore
 */

#ifndef _msgqueue_sem_H
#define	_msgqueue_sem_H

#ifdef	__cplusplus
extern "C" {
#endif
    
struct queue_record {
  struct queue_record * next, *prev;
  char buf[81];
};

typedef struct myqueue {
  struct queue_record *head, *tail;
  sem_t headsem, tailsem, queuesem;
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

#endif	/* _msgqueue_sem_H */

