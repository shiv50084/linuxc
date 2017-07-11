#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAXLINE 80
#define SERVER_PORT 8000

int main(int argc, char *argv[])
{
	struct sockaddr_in server_addr, client_addr;
	socklen_t client_addr_len;
	int listen_fd, connect_fd;
	char buf[MAXLINE];
	char str[INET_ADDRSTRLEN];
	int i, bytes;

	/*
	 * AF_INET for IPv4
	 * SOCK_STREAM for TCP
	 * protocol : 0
	 */
	listen_fd = socket(AF_INET, SOCK_STREAM, 0);

	/* server address for bind */
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(SERVER_PORT);

	/* bind fd and address (fixed address) */
	bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

	/* listen fd */
	listen(listen_fd, 20);

	printf("Accepting connecting...\n");
	while (1)
	{
		client_addr_len = sizeof(client_addr);
		connect_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &client_addr_len);

		/* recv client requst */
		bytes = read(connect_fd, buf, MAXLINE);
		printf("recv from %s at port %d\n", inet_ntop(AF_INET, &client_addr.sin_addr, str, sizeof(str)), ntohs(client_addr.sin_port));

		/* do something for client */
		for (i = 0; i < bytes; i++)
		{
			buf[i] = toupper(buf[i]);
		}

		/* answer client request */
		write(connect_fd, buf, bytes);

		close(connect_fd);
	}

	return 0;
}
