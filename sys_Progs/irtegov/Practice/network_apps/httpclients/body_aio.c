/* 
 * File:   body_select.c
 * Author: fat
 *
 * Created on May 25, 2007, 1:24 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <aio.h>
#include <errno.h>
#include <assert.h>

/*
 * 
 */
int open_socket(char * hostname, int port);
char *generate_get_command(const char * url, char *buf, size_t size);

int client_body(char *hostname, int port, char *url) {
    int s;
    int lines=0;
    int maxlines=25;
    char buf[4096];
    int lowmark=0, highmark=0;
    int empty=1, full=0, eof=0;
	struct aiocb readrq, writerq, termreadrq;
	struct aiocb *rqv[4]={ NULL, NULL, NULL, NULL};
	int rqt;
	int res;
	char tb[10];
    
    s=open_socket(hostname, port);
    if (s<0) return 0;
    generate_get_command(url, buf, sizeof(buf));
    write(s, buf, strlen(buf));
	memset(&readrq, 0, sizeof readrq);
	readrq.aio_fildes=s;
	memset(&writerq, 0, sizeof writerq);
	writerq.aio_fildes=1;
	memset(&termreadrq, 0, sizeof termreadrq);
	termreadrq.aio_fildes=0;
	termreadrq.aio_buf=tb;
    while(1) {
		memset(rqv, 0, sizeof(rqv));
		rqt=0;
        if (!full && !eof) {
			readrq.aio_buf=buf+highmark;
            if (highmark>=lowmark) {
				readrq.aio_nbytes=sizeof(buf)-highmark;
            } else if (highmark<lowmark) {
				readrq.aio_nbytes=lowmark-highmark;
            }
			aio_read(&readrq);
			rqv[rqt++]=&readrq;
        } else {
			readrq.aio_nbytes=0;
		}
		
        if (!empty && lines<maxlines) {
            char *t=buf+lowmark;
            char *l;
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
			writerq.aio_buf=buf+lowmark;
			writerq.aio_nbytes=t-(buf+lowmark);
			aio_write(&writerq);
			rqv[rqt++]=&writerq;
        } else {
			writerq.aio_nbytes=0;
		}
        
        if (lines>=maxlines ) {
			termreadrq.aio_nbytes=1;
            aio_read(&termreadrq);
			rqv[rqt++]=&termreadrq;
        } else {
			termreadrq.aio_nbytes=0;
		}
		
		aio_suspend((const struct aiocb const * const *)rqv, rqt, NULL);

        if (readrq.aio_nbytes!=0 && aio_error(&readrq)!=EINPROGRESS) {
			res=aio_error(&readrq);
			if (res) {
				fprintf(stderr, "reading: %s\n", strerror(res));
				exit(0);
			}
			res=aio_return(&readrq);
			if (res==0) {
				eof=1;
			} else {
				highmark+=res;
				if (highmark==sizeof(buf)) highmark=0;
				if (highmark==lowmark) full=1;
				empty=0;
			}
		}
		if (writerq.aio_nbytes && aio_error(&writerq)!=EINPROGRESS) {
			res=aio_error(&writerq);
			if (res) {
				fprintf(stderr, "writing to terminal: %s\n", strerror(res));
				exit(0);
			}
			res=aio_return(&writerq);
			assert(res!=0);
			lowmark+=res;
			if (lowmark==sizeof(buf)) lowmark=0;
			if (lowmark==highmark) empty=1;
			full=0;
		}
		if (termreadrq.aio_nbytes && aio_error(&termreadrq)!=EINPROGRESS) {
			res=aio_error(&termreadrq);
			if (res) {
				/* ??? */
				fprintf(stderr, "reading from terminal: %s\n", strerror(res));
				exit(0);
			}
			lines=0;
		}

        if (eof && empty) break;

    }   
    return 0;            
}
    
    
