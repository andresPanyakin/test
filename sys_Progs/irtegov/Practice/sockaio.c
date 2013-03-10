#include <aio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netdb.h>

const char req[]="GET / HTTP/1.0\r\n\r\n";

int main() {
	int s;
	static struct aiocb readrq;
	static const struct aiocb *readrqv[2]={&readrq, NULL};
	char buf[4096];
	char buf2[4096];
	size_t size;
	struct sockaddr_in addr;
	struct hostent *srv;

	s=socket(PF_INET, SOCK_STREAM, 0);
	srv=gethostbyname("www.nsu.ru");
	addr.sin_family=AF_INET;
	addr.sin_port=htons(80);
    if (srv) {
		addr.sin_addr.s_addr=*((unsigned long*)srv->h_addr);
	} else {
		inet_aton("193.124.215.195", &addr.sin_addr);
	}
	if (connect(s, (struct sockaddr*)&addr, sizeof addr)) {
		perror("connecting to server");
		exit(1);
	}

	memset(&readrq, 0, sizeof readrq);
	readrq.aio_fildes=s;
	readrq.aio_buf=buf;
	readrq.aio_nbytes=sizeof buf;
	if (aio_read(&readrq)) {
		perror("aio_read");
		exit(1);
	}
	write(s, req, (sizeof req)-1);

	while(1) {
		aio_suspend(readrqv, 1, NULL);
		size=aio_return(&readrq);
		if (size>0) {
			write(1, buf, size);
			aio_read(&readrq);
		} else if (size==0) {
			break;
		} else {
			perror("reading from socket");
		}
	}
}
