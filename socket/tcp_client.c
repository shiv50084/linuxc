#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAXLINE 80
#define SERVER_PORT 8000

/* client ip 192.168.1.100 */
#define DESTINATION_IP	"192.168.1.224"

int main(int argc, char *argv[])
{
	struct sockaddr_in dest_addr;
	char buf[MAXLINE];
	int sock_fd;
	int bytes;
	char *str;

	if (argc != 2)
	{
		printf("Usage : %s <message>\n", argv[0]);
		exit(1);
	}

	str = argv[1];

	sock_fd = socket(AF_INET, SOCK_STREAM, 0);

	/* destination address */
	bzero(&dest_addr, sizeof(dest_addr));
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(SERVER_PORT);
	inet_pton(AF_INET, DESTINATION_IP, &dest_addr.sin_addr);

	/* connect server */
	connect(sock_fd, (struct sockaddr *)&dest_addr, sizeof(dest_addr));

	/* send request to server */
	bytes = write(sock_fd, str, strlen(str));

	/* recv the answer from server */
	bytes = read(sock_fd, buf, MAXLINE);
	printf("Response from serve %s\n", buf);

	close(sock_fd);

	return 0;
}
