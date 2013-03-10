/* 
 * File:   body_pthread.c
 * Author: fat
 *
 * Created on May 25, 2007, 1:24 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

/*
 * 
 */
int open_socket(char * hostname, int port);
char *generate_get_command(const char * url, char *buf, size_t size);

/* in more complex application (read:proxy) we'd have to put all this into 
 * a buffer state structure, and pass pointer to this structure to both 
 * reader and writer threads.
 * However here I want to converge code of different clients as much as
 * possible and make it as simple as possible. */

int s;
int lines=0;
int maxlines=25;
char buf[4096];
int lowmark=0, highmark=0;
int empty=1, full=0, eof=0;
pthread_mutex_t bufmx=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t bufcond=PTHREAD_COND_INITIALIZER;

static void *reader_thread(void *q) {
  int res;
  pthread_mutex_lock(&bufmx);
  while(!eof) { 
    while (!full) {
      pthread_cond_wait(&bufcond, &bufmx);
    }
    if (highmark>=lowmark) {
      pthread_mutex_unlock(&bufmx);
      res=read(s, buf+highmark, sizeof(buf)-highmark);
      pthread_mutex_lock(&bufmx);
      if (res==0) {
	eof=1;
	break;
      }
      highmark+=res;
      if (highmark==sizeof(buf)) highmark=0;
    } else if (highmark<lowmark) {
      int t=lowmark;
      pthread_mutex_unlock(&bufmx);
      res=read(s, buf+highmark, t-highmark);
      pthread_mutex_lock(&bufmx);
      if (res==0) {
	eof=1;
	break;
      }
    }
    if (highmark==lowmark) full=1;
    empty=0;
    pthread_cond_signal(&bufcond);
  }
  pthread_mutex_unlock(&bufmx);
  return NULL;
}

static void *writer_thread(void *q) {
  int res;
  pthread_mutex_lock(&bufmx);
  while(!(eof && empty)) {
    char *t=buf+lowmark;
    char *l;
    char tb[10];
    while(!empty) {
      pthread_cond_wait(&bufcond, &bufmx);
    }
    if (lowmark<highmark) {
      l=buf+highmark;
    } else {
      l=buf+sizeof(buf);
    }
    /* here we can implement smarter concept of 'line'
     * for example, we can get ncurses/terminfo information about screen size
     * and calculate line wrapping */
    for(; t<l && *t!='\n'; t++); /* empty loop, it does everything we need in the condition/increment */
    if (t<l) { 
      t++; /* include \n */
      lines++;
    }
    pthread_mutex_unlock(&bufmx);
    if (lines>maxlines) {
      read(0, tb, 1);
      lines=0;
    }

    res=write(1, buf+lowmark, t-(buf+lowmark));
    pthread_mutex_lock(&bufmx);
    if (res<0) {
      perror("writing to termial");
      exit(0);
    }
    lowmark+=res;
    if (lowmark>=sizeof(buf)) lowmark=0;
    if (lowmark==highmark) empty=1;
    full=0;
    pthread_cond_signal(&bufcond);
  }
  pthread_mutex_unlock(&bufmx);
  return NULL; 				
}

int client_body(char *hostname, int port, char *url) {
  pthread_t reader, writer;
	
  s=open_socket(hostname, port);
  if (s<0) return 0;
  generate_get_command(url, buf, sizeof(buf));
  write(s, buf, strlen(buf));
  pthread_create(&reader, NULL, reader_thread, NULL);
  pthread_create(&writer, NULL, writer_thread, NULL);
  pthread_join(reader, NULL);
  pthread_join(writer, NULL);
  return 0;            
}
