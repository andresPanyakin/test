#include <aio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <setjmp.h>


const char req[]="GET / HTTP/1.0\r\n\r\n";
sigjmp_buf toexit;

void sigiohandler(int signo, siginfo_t *info, void *context) {
	struct aiocb * req;
	if (signo!=SIGIO || info->si_signo!=SIGIO) return;

	req=(struct aiocb *)info->si_value.sival_ptr;
	if (aio_error(req)==0) {
			/* it's complete!!! */
		size_t size;
		size=aio_return(req);
		if (size==0) {
				/* EOF */
				siglongjmp(toexit, 1);
		}
		write(1, (const void *)req->aio_buf, size);
		/* schedule next read */
		aio_read(req);
	}
}

int main() {
	int s;
	static struct aiocb readrq;
	/* static const struct aiocb *readrqv[2]={&readrq, NULL}; */
	char buf[4096];
	struct sockaddr_in addr;
	struct hostent *srv;
	struct sigaction sigiohandleraction;
	sigset_t set;

	s=socket(PF_INET, SOCK_STREAM, 0);
	srv=gethostbyname("www.nsu.ru");
	addr.sin_family=AF_INET;
	addr.sin_port=htons(80);
    if (srv) {
		memcpy(&addr.sin_addr.s_addr, srv->h_addr, sizeof(srv->h_addr));
	} else {
#ifdef linux
		inet_aton("193.124.215.195", &addr.sin_addr);
#else
		inet_pton(AF_INET, "193.124.215.195", &addr.sin_addr);
#endif
	}
	if (connect(s, (struct sockaddr*)&addr, sizeof addr)) {
		perror("connecting to server");
		exit(1);
	}

	/* block SIGIO from happening at wrong time */
	sigemptyset(&set);
	sigaddset(&set, SIGIO);
	sigprocmask(SIG_BLOCK, &set, NULL);
	
	/* set SIGIO handler */
	sigiohandleraction.sa_sigaction=sigiohandler;
	sigiohandleraction.sa_flags=SA_SIGINFO;
	sigiohandleraction.sa_mask=set;
	sigaction(SIGIO, &sigiohandleraction, NULL);
	
	/* form AIO request */
	readrq.aio_fildes=s;
	readrq.aio_buf=buf;
	readrq.aio_nbytes=sizeof buf;
	readrq.aio_sigevent.sigev_notify=SIGEV_SIGNAL;
	readrq.aio_sigevent.sigev_signo=SIGIO;
	readrq.aio_sigevent.sigev_value.sival_ptr=&readrq;
	if (aio_read(&readrq)) {
		perror("aio_read");
		exit(1);
	}
	
	/* Everything ready, send HTTP request */
	write(s, req, (sizeof req)-1);

	/* main loop :) */
	if (!sigsetjmp(toexit, 1)) {
			while(1) sigpause(SIGIO);
	}
	write(2, "That's all, folks\n", 18); 
	return 0;
}
