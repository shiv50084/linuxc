#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <stdlib.h>
#include <signal.h>

#include "wrap.h"

#define MAXLINE 80
int sock_fd;

void sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		printf("Got signo %d\n", signo);
		Close(sock_fd);
		exit(1);
	}
}

/*
 * Usage :
 * ./udp_server_broadcast <port>
 */
int main(int argc, char *argv[])
{
	struct sockaddr_in server_addr, client_addr;
	socklen_t client_addr_len;
	char buf[MAXLINE];
	char str[INET_ADDRSTRLEN];
	int bytes;

	if (argc != 2)
	{
		fprintf(stderr, "%s <port>\n", argv[0]);
		exit(1);
	}

	/* register sigint handler */
	if (signal(SIGINT, sig_handler) == SIG_ERR)
	{
		perror("signal register error");
		exit(1);
	}

	/*
	 * AF_INET for IPv4
	 * SOCK_DGRAM for UDP
	 * protocol : 0
	 */
	sock_fd = Socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(atoi(argv[1]));

	/* bind fd and address (fixed address) */
	Bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

	printf("Accepting connecting...\n");
	while (1)
	{
		/* recv client requst */
		client_addr_len = sizeof(client_addr);
		bytes = recvfrom(sock_fd, buf, MAXLINE, 0, (struct sockaddr*)&client_addr, &client_addr_len);
		if (bytes == -1)
			perror("recvform error");

		/* print out some info of sender */
		buf[bytes-1] = '\0';
		printf("recv %s(%d) bytes from %s at port %d\n", buf, bytes-1, inet_ntop(AF_INET, &client_addr.sin_addr, str, sizeof(str)), ntohs(client_addr.sin_port));
	}

	return 0;
}
