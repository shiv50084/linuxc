#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "wrap.h"

#define MAXLINE 80

/* Usage :
 * ./udp_client_broadcast 192.168.x.255
 *
 * example:
 * ./udp_client_broadcast 192.168.1.255
 */
int main(int argc, char *argv[])
{
	struct sockaddr_in dest_addr;
	char buf[MAXLINE];
	int sock_fd;
	int bytes;
	char *target_ip;
	int optval = 1;

	if (argc != 3)
	{
		printf("Usage : %s <x.x.x.255> <port>\n", argv[0]);
		exit(1);
	}

	target_ip = argv[1];

	sock_fd = Socket(AF_INET, SOCK_DGRAM, 0);

	/* set broadcast option */
	if (setsockopt(sock_fd, SOL_SOCKET, SO_BROADCAST,
				&optval, sizeof(optval)) < 0)
	{
		perror("setsockoption error");
		return -1;
	}

	/* destination address */
	bzero(&dest_addr, sizeof(dest_addr));
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(atoi(argv[2]));
	inet_pton(AF_INET, target_ip, &dest_addr.sin_addr);

	while (fgets(buf, MAXLINE, stdin) != NULL)
	{
		bytes = sendto(sock_fd, buf, strlen(buf), 0 , (struct sockaddr *)&dest_addr, sizeof(dest_addr));
		if (bytes == -1)
			perror("Send to error");
	}

	Close(sock_fd);

	return 0;
}
