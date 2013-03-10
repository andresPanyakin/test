/* 
 * File:   forwarder.c
 * Author: fat
 *
 * Created on May 20, 2007, 4:08 PM
 */

#include	<sys/types.h>	/* basic system data types */
#include	<sys/socket.h>	/* basic socket definitions */
#include	<sys/time.h>	/* timeval{} for select() */
#include	<time.h>		/* timespec{} for pselect() */
#include	<netinet/in.h>	/* sockaddr_in{} and other Internet defns */
#include	<fcntl.h>		/* for nonblocking */
#include	<netdb.h>
#include	<signal.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<sys/uio.h>		/* for iovec{} and readv/writev */
#include	<unistd.h>
#include        <assert.h>

/*
 * 
 */

#define BUFSIZE 4096

char * usage_format="Usage: %s listen_port remote_host remote_port\n";

struct connection_descriptor {
    int client_socket, forwarding_socket;
    struct connection_descriptor *prev, *next;
    ssize_t data_c_f, data_f_c; /* data counters.  -1 designates closed target connection */
    char buf_c_f[BUFSIZE]; /* data from client to forward */
    char buf_f_c[BUFSIZE]; /* data from forward to client */
};

struct connection_descriptor *head, *tail;

int nfds=0;

void check_socket_against_nfds(int s) {
    if (s>=FD_SETSIZE) {
        fprintf(stderr, "Socket number out of range for select\n");
        exit(0);
    }
    if (s+1>nfds) nfds=s+1;
}

struct connection_descriptor *add_connection(int client_socket, struct sockaddr_in *servaddr) {
    struct connection_descriptor *t;
    t=malloc(sizeof(struct connection_descriptor));
    t->client_socket=client_socket;
    t->forwarding_socket=socket(AF_INET, SOCK_STREAM, 0);
    check_socket_against_nfds(t->forwarding_socket);
    if (connect(t->forwarding_socket, (struct sockaddr *)servaddr, sizeof(*servaddr))) {
        perror("Connecting to server:");
        close(t->client_socket);
        free(t);
        return NULL;
    }
    t->prev=NULL;
    t->next=head;
    if (head==NULL) {
        tail=t;
    } else {
        head->prev=t;
    }
    head=t;
    t->data_f_c=t->data_c_f=0;
    memset(t->buf_c_f, 0, sizeof(t->buf_c_f));
    memset(t->buf_f_c, 0, sizeof(t->buf_f_c));

    return t;
}

void drop_connection(struct connection_descriptor *t) {
    if (t==head && t==tail) { 
        /* it was only record in the list */
        head=tail=NULL;
    } else if (t==head) {
        head=t->next;
        head->prev=NULL;
    } else if (t==tail) {
        tail=t->prev;
        tail->next=NULL;
    } else {
        assert(t->next!=NULL);
        assert(t->prev!=NULL);
        t->prev->next=t->next;
        t->next->prev=t->prev;
    }
    close(t->client_socket);
    close(t->forwarding_socket);
    free(t);
}

void form_select_masks(fd_set *readfs, fd_set *writefs, int listenfd) {
    struct connection_descriptor *t;
    
    FD_ZERO(readfs); FD_ZERO(writefs);
    FD_SET(listenfd, readfs);
    t=head;
    while(t) {
        struct connection_descriptor *t1;
        t1=t->next;
        if((t->data_c_f<0 && t->data_f_c<=0) ||
           (t->data_f_c<0 && t->data_c_f<=0)) {
            drop_connection(t);
        } else {
            if(t->data_c_f==0) 
                FD_SET(t->client_socket, readfs);
            if(t->data_f_c==0) 
                FD_SET(t->forwarding_socket, readfs);
            if(t->data_c_f>0) 
                FD_SET(t->forwarding_socket, writefs);
            if(t->data_f_c>0) 
                FD_SET(t->client_socket, writefs);
        }
        t=t1;
    }
}

void test_and_process_masks(fd_set *readfs, fd_set *writefs) {
    /* listendf socket is tested outside of this and after this */
    struct connection_descriptor *t;
    
    t=head;
    while(t) {
        if(t->data_c_f==0 && FD_ISSET(t->client_socket, readfs)) {
            t->data_c_f=read(t->client_socket, t->buf_c_f, sizeof(t->buf_c_f));
            if(t->data_c_f==0) t->data_c_f=-1;
        }
        if(t->data_f_c==0 && FD_ISSET(t->forwarding_socket, readfs)) {
            t->data_f_c=read(t->forwarding_socket, t->buf_f_c, sizeof(t->buf_f_c));
            if(t->data_f_c==0) t->data_f_c=-1;
        }
        if(t->data_c_f>0 && FD_ISSET(t->forwarding_socket, writefs)) {
            int res=write(t->forwarding_socket, t->buf_c_f, t->data_c_f);
            if (res==-1) t->data_f_c=-1;
            else t->data_c_f=0;  /* assume that write always sucessful with full size */
        }
        if(t->data_f_c>0 && FD_SET(t->client_socket, writefs)) {
            int res=write(t->client_socket, t->buf_f_c, t->data_f_c);
            if (res==-1) t->data_c_f=-1;
            else t->data_f_c=0;
        }
            
        t=t->next;
    }
}    
        

int
main(int argc, char** argv) {
    int listenfd;
    int nready, addrlen, res;
    fd_set	readfs, writefs;
    struct hostent *forward_host;
    struct sockaddr_in	servaddr, forwaddr, cliaddr;
    int listen_port, remote_port;

    if(argc<3) {
        fprintf(stderr, usage_format, argv[0]);
        return 0;
    }
    
    listen_port=atoi(argv[1]);
    remote_port=atoi(argv[3]);

    if(listen_port<=0 && remote_port<=0) {
        fprintf(stderr, usage_format, argv[0]);
        return 0;
    }
    
    forward_host=getipnodebyname(argv[2], AF_INET, 0, &res);
    if(forward_host==NULL) {
        char *errors[]={ "Host not found", "Non-authoritative", "Request Refused", "No address records", "Unknown Error" };
        char *err;
        if (res==HOST_NOT_FOUND) err=errors[0];
        else if (res==TRY_AGAIN) err=errors[1];
        else if (res==NO_RECOVERY) err=errors[2];
        else if (res==NO_DATA) err=errors[3];
        else err=errors[4];
        
        fprintf(stderr, "%s: %s %s\n", argv[0], argv[2], err);
        return 0;
    }

    memset(&forwaddr, 0, sizeof(forwaddr));
    forwaddr.sin_family = AF_INET;
    memcpy(&forwaddr.sin_addr.s_addr, forward_host->h_addr_list[0], sizeof(struct in_addr));
    forwaddr.sin_port=htons(remote_port);
    freehostent(forward_host);
    
    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    check_socket_against_nfds(listenfd);
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(listen_port);

    if (bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr))) {
        perror(argv[0]);
        return 0;
    }

    signal(SIGPIPE, SIG_IGN);
    listen(listenfd, SOMAXCONN);
    
    while(1) {
        form_select_masks(&readfs, &writefs, listenfd );
        nready=select(nfds, &readfs, &writefs, NULL, NULL);
        if (nready<0) {
            perror(argv[0]);
            break;
        }
        if (nready==0) continue;
        test_and_process_masks(&readfs, &writefs);
        if (FD_ISSET(listenfd, &readfs)) {
            int client_connection;
            addrlen=sizeof(cliaddr);
            client_connection=accept(listenfd, (struct sockaddr *)&cliaddr, &addrlen);
            if (client_connection < 0) {
                perror(argv[0]);
                break;
            }
            check_socket_against_nfds(client_connection);
            if (!add_connection(client_connection, &forwaddr)) {
                perror(argv[0]);
                break;
            }
        }
    }
    
    return (EXIT_SUCCESS);
}

