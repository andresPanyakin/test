#include <pthread.h>
#include <unistd.h>
#include <malloc.h>
#include <string.h>

#define MAXLEN 80
#define TIMEOUT 5
#define BUFSIZE 4096

struct node_t {
  int length;
  char data[MAXLEN];
  struct node_t *next;
  pthread_mutex_t mut;
} head;


void* sort_loop(void* param) {
  struct node_t *prev, *cur0, *cur1;
  int mess;
  while (1) {
    sleep(TIMEOUT);
    mess = 1;
    while (mess) {
      mess = 0;
      prev = &head;
      pthread_mutex_lock(&(prev->mut));
      cur0 = head.next;
      if (cur0) {
	pthread_mutex_lock(&(cur0->mut));
	cur1 = cur0->next;
	while (cur1) {
	  pthread_mutex_lock(&(cur1->mut));
	  if (strcmp(cur1->data, cur0->data) < 0) {
	    mess = 1;
	    cur0->next = cur1->next;
	    prev->next = cur1;
	    cur1->next = cur0;
	    cur0 = cur1;
	    cur1 = cur0->next;
	  }
	  pthread_mutex_unlock(&(prev->mut));
	  prev = cur0;
	  cur0 = cur1;
	  cur1 = cur1->next;
	}
	pthread_mutex_unlock(&(cur0->mut));
      }
      pthread_mutex_unlock(&(prev->mut));
    }
  }
  return 0;
}

int main() {
  char buffer[BUFSIZE];
  int buflen = 0, bufpos = 0;
  struct node_t *cur, *pos, *prev;
  pthread_t sorting_thread;
  cur = (struct node_t*)malloc(sizeof(struct node_t));
  pthread_mutex_init(&(cur->mut),0);
  cur->length = 0;
  pthread_mutex_init(&(head.mut), 0);
  head.next = 0;
  head.length = 0;
  pthread_create(&sorting_thread, 0, sort_loop, 0);
  while (1) {
    while (1) {
      if (bufpos == buflen) {
	buflen = read(0, buffer, BUFSIZE);
	if (buflen < 1) {
	  break;
	}
	bufpos = 0;
      }
      if ((cur->data[cur->length] = buffer[bufpos++])=='\n') break;
      cur->length++;
      if (cur->length == MAXLEN) break;
    }

    if (!cur->length) {
      prev = &head;
      pthread_mutex_lock(&(prev->mut));
      pos = prev->next;
      while (pos) {
	pthread_mutex_lock(&(pos->mut));
	pthread_mutex_unlock(&(prev->mut));
	write(1, pos->data, pos->length);
	write(1, "\n", 1);
	prev = pos;
	pos = pos->next;		
      }
      pthread_mutex_unlock(&(prev->mut));
    } else {
      pthread_mutex_lock(&(head.mut));
      cur->next = head.next;
      head.next = cur;
      pthread_mutex_unlock(&(head.mut));
      cur = (struct node_t*)malloc(sizeof(struct node_t));
      pthread_mutex_init(&(cur->mut),0);
      cur->length = 0;
    }
  }
  return 0;
}
