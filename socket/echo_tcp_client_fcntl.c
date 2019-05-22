#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <time.h>
#include <errno.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	int sockfd;

	if (argc < 3)
	{
		printf("Usage : %s <ip> <port>\n", argv[0]);
		exit(1);
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		perror("Socket error");
		exit(1);
	}

	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[2]));

	/* 将ip地址转换成网络字节序再填入serv_addr中 */
	inet_pton(AF_INET, argv[1],
			&serv_addr.sin_addr.s_addr);

	if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		perror("Connect error\n");
		exit(1);
	}

	char buff[512];
	size_t size;
	char *propmt = ">";

	while (1)
	{
		/* get message from user input */
		memset(buff, 0, sizeof(buff));
		write(STDOUT_FILENO, propmt, 1);
		size = read(STDIN_FILENO, buff, sizeof(buff));
		if (size < 0)
			continue;
		buff[size-1] = '\0';

		/* 将数据发送给服务端 */
		if (write(sockfd, buff, sizeof(buff)) < 0)
		{
			perror("Write error\n");
			continue;
		}
		else
		{
			if (read(sockfd, buff, sizeof(buff)) < 0)
			{
				perror("Read error\n");
				continue;
			}
			printf("%s\n", buff);
		}
	}

	return 0;
}
