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
    
    s=open_socket(hostname, port);
    if (s<0) return 0;
    generate_get_command(url, buf, sizeof(buf));
    write(s, buf, strlen(buf));
    while(1) {
        fd_set readfs, writefs;
        int res;
        
        FD_ZERO(&readfs); 
        FD_ZERO(&writefs);
        if (!full && !eof) 
            FD_SET(s, &readfs);
        if (!empty && lines<maxlines) 
            FD_SET(1, &writefs);
        if (lines>=maxlines) 
            FD_SET(0, &readfs);
        res=select(s+1, &readfs, &writefs, NULL, NULL);
        if (res<0) {
            perror("select");
            exit(0);
        }
        if (res==0) continue; /* ??? */
        if (!full && !eof && FD_ISSET(s, &readfs)) {
            if (highmark>=lowmark) {
                res=read(s, buf+highmark, sizeof(buf)-highmark);
                if (res==0) {
                    eof=1;
                } else {
                    highmark+=res;
                    if (highmark==sizeof(buf)) highmark=0;
                    if (highmark==lowmark) full=1;
                    empty=0;
                }
            } else if (highmark<lowmark) {
                res=read(s, buf+highmark, lowmark-highmark);
                if (res==0) {
                    eof=1;
                } else {
                    highmark+=res;
                    if (highmark==lowmark) full=1;
                    empty=0;
                }
            }
        }
        if (!empty && lines<maxlines && FD_ISSET(1, &writefs)) {
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
            res=write(1, buf+lowmark, t-(buf+lowmark));
            if (res<=0) {
                perror("writing to terminal");
                return 0;
            }
            lowmark+=res;
            full=0;
            if (lowmark==sizeof(buf)) lowmark=0;
            if (lowmark==highmark) { empty=1;}
        }
        
        if (eof && empty) break;

        if (lines>=maxlines && FD_ISSET(0, &readfs)) {
            char tb[10];
            read(0, tb, 1);
            lines=0;
        }
    }   
    return 0;            
}
    
    
