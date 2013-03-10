/* 
 * File:   httpclient_main.c
 * Author: fat
 *
 * Created on May 25, 2007, 12:26 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <regex.h>
#include <strings.h>
#include <assert.h>
#include	<sys/socket.h>	/* basic socket definitions */
#include	<sys/time.h>	/* timeval{} for select() */
#include	<time.h>		/* timespec{} for pselect() */
#include	<netinet/in.h>	/* sockaddr_in{} and other Internet defns */
#include	<fcntl.h>		/* for nonblocking */
#include	<netdb.h>

/* helper function for regexp parser */
char * copy_bras(const char *string, regmatch_t match[], int brasno) {
    /* regmatch_t on Solaris has pointers to match string, but let's stick to documented POSIX API */
    int length;
    char * t;
    if (match[brasno].rm_so==-1 || match[brasno].rm_so==match[brasno].rm_eo) return NULL;
    length=match[brasno].rm_eo-match[brasno].rm_so;
    assert(length>0);
    t=malloc(length+1);
    memcpy(t, string+match[brasno].rm_so, length);
    t[length]='\0';
    return t;
}

/* regexp-based URL parser.  
 * We use POSIX regexp, this is supposed to be most portable solution
 * and regexp syntax is more adequate to our needs 
 * THREAD UNSAFE!!!!
 * Here we call it before any thread is created, so this is not a problem even in pthread client
 * go figure yourself how to use this in multithreaded proxies */
int parse_url(char  * url, char  **protocol, char  **user,
              char  **port, char  **hostname, char  ** uri) {
                  
    const char *url_regexp="^([a-z]+)://((.*)@)?([a-zA-Z][-a-zA-Z0-9.]*)(:([0-9]+))?(.*)$";
    static regex_t compiled_regexp;
    regmatch_t match[10];
    int nb;
    if (compiled_regexp.re_nsub==0) nb=regcomp(&compiled_regexp, url_regexp, REG_EXTENDED);
    if (nb) {
        /* fatal - this is OUR error, wrong regexp */
        fprintf(stderr, "regerrno %s\n", regerror(nb, &compiled_regexp, NULL, 0));
        
        exit(1);
    }

    nb=regexec(&compiled_regexp, url, 10, match, 0);
    if (nb) {
	fprintf(stderr, "regexp match: %s\n", regerror(nb, &compiled_regexp, NULL, 0));
        return -1;
    }
    *protocol=copy_bras(url, match, 1);
    *user=copy_bras(url, match, 3); /* match 2 contains @ */
    *hostname=copy_bras(url, match, 4);
    *port=copy_bras(url, match, 6); /* match 5 contains : */
    *uri=copy_bras(url, match, 7); 
    return 0;
}
/* at build time might point to different implementations of body: select-based, aio-based and pthread-based */
extern int client_body(char  *hostname, int port, char  *url);

/*
 * General socket-opening function
 * because we do not care about blocks in this function, it is completely architecture-independent
 * 
 */
int open_socket(char * hostname, int port) {
    int s;
    struct hostent *server_host;
    struct sockaddr_in	servaddr;
    int res;

    server_host=getipnodebyname(hostname, AF_INET, 0, &res);
    if(server_host==NULL) {
        char *errors[]={ "Host not found", "Non-authoritative", "Request Refused", "No address records", "Unknown Error" };
        char *err;
        if (res==HOST_NOT_FOUND) err=errors[0];
        else if (res==TRY_AGAIN) err=errors[1];
        else if (res==NO_RECOVERY) err=errors[2];
        else if (res==NO_DATA) err=errors[3];
        else err=errors[4];
        
        fprintf(stderr, "nslookup for %s fail: %s\n", hostname, err);
        return -1;
    }
    
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    memcpy(&servaddr.sin_addr.s_addr, server_host->h_addr_list[0], sizeof(struct in_addr));
    servaddr.sin_port=htons(port);
    freehostent(server_host);
    s=socket(AF_INET, SOCK_STREAM, 0);
    if (connect(s, (struct sockaddr *)&servaddr, sizeof(servaddr))) {
        perror("Connecting to server:");
        return -1;
    }
    return s;
}

char *generate_get_command(const char * url, char *buf, size_t size) {
    char *pattern="GET %.*s HTTP/1.0\r\n\r\n";
    sprintf(buf, pattern, size-strlen(pattern), url); /* dangerous, but we've counted the size before */
    return buf;
}


int
main(int argc, char** argv) {
    char *protocol, *user, *port_string, *hostname, *uri;
    int port;
    if (argc<1) {
        fprintf(stderr, "Usage: %s url\n", argv[0]);
        return 0;
    }
    if (parse_url(argv[1], &protocol, &user, &port_string, &hostname, &uri)==-1) {
        fprintf(stderr, "Cannot parse URL\n");
        return 0;
    }
    if (strcmp(protocol, "http")) {
        fprintf(stderr, "Only HTTP protocol is supported\n");
        return 0;
    }
    if(user!=NULL) {
        fprintf(stderr, "HTTP authentication is not supported\n");
        return 0;
    }
    
    if (port_string!=NULL) port=atol(port_string);
    else port=80;
    
    if (port==0) {
        fprintf(stderr, "URL format error, port must be numeric\n");
        return 0;
    }
    client_body(hostname, port, argv[1]);
    return (EXIT_SUCCESS);
}

