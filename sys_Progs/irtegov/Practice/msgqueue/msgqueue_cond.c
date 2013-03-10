#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "msgqueue_cond.h"

void mymsginit(queue *q) {
  q->head=NULL;
  q->tail=NULL;
  q->beingdestroyed=0;
  q->count=0;
  pthread_mutex_init(&(q->queuemx), NULL);
  pthread_cond_init(&(q->queuecond), NULL);
}

void mymsgdrop(queue *q) {
  struct queue_record *t;
  q->beingdestroyed=1;
  pthread_cond_broadcast(&q->queuecond);
  pthread_mutex_lock(&q->queuemx);
  t=q->head;
  while(t) {
    struct queue_record *t1;
    t1=t->next;
    free(t);
    t=t1;
  }
  pthread_mutex_unlock(&q->queuemx);
}

void mymsgdestroy(queue *q) {
    pthread_mutex_destroy(&q->queuemx);
    pthread_cond_destroy(&q->queuecond);
}

int mymsgput(queue *q, char * msg) {
	struct queue_record *t;
		
        pthread_mutex_lock(&q->queuemx);
        while (q->count>=10 && !q->beingdestroyed) {
            pthread_cond_wait(&q->queuecond, &q->queuemx);
        }

	if (q->beingdestroyed) {
            pthread_mutex_unlock(&q->queuemx);
            return 0;
	}
	t=malloc(sizeof(struct queue_record));
	strncpy(t->buf, msg, sizeof(t->buf)-1);
	t->buf[sizeof(t->buf)-1]='\0';
	t->prev=NULL;
	t->next=q->head;
	if (q->head==NULL) {
            q->head=q->tail=t;
	} else {
            q->head->prev=t;
            q->head=t;
	}
        if (q->count==0) pthread_cond_signal(&q->queuecond);
        q->count++;
        pthread_mutex_unlock(&q->queuemx);
        return strlen(t->buf)+1;
}

int mymsgget(queue *q, char *buf, size_t bufsize) {
	struct queue_record *t;
		
        pthread_mutex_lock(&q->queuemx);
        while(q->count==0 && !q->beingdestroyed) {
            pthread_cond_wait(&q->queuecond, &q->queuemx);
        }
        
	if (q->beingdestroyed) {
            pthread_mutex_unlock(&q->queuemx);
            return 0;
	}
        
	t=q->tail;
        assert(t!=NULL);
	if (q->head==t) {
		q->head=q->tail=NULL;
	} else {
		q->tail=t->prev;
		q->tail->next=NULL;
	}
	if (q->count==10) pthread_cond_signal(&q->queuecond);
        q->count--;
        pthread_mutex_unlock(&q->queuemx);
	strncpy(buf, t->buf, bufsize-1);
	buf[bufsize-1]='\0';
	free(t);
	return strlen(buf)+1;
}
