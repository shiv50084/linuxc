#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

/*
 * Usage:
 * gcc socketpair.c -lpthread
 */

#define READ_BUF_SIZE 512

/*
 * 父子线程通过socketpair来通信
 * child --- say hello to ---> main
 * main  --- reply to ---> child
 */

void *start_routine(void *argv)
{
	int cnt = 0;
	int fd = *(int *)argv;
	int ret;
	const char *msg = "Child thread";
	char buf[READ_BUF_SIZE];
	
	while (1)
	{
		ret = write(fd, msg, strlen(msg));
		
		ret = read(fd, buf, READ_BUF_SIZE);
		buf[ret] = '\0';
		printf("%s[%d]\n", buf, cnt++);
		
		sleep(2);
	}
}

int main(int argc, char *argv[])
{
	int cnt = 0;
	int ret;
	pthread_t pid;
	int sockets[2];
	int fd;
	char buf[READ_BUF_SIZE];
	const char *msg = "Main thread";

	socketpair(AF_UNIX, SOCK_SEQPACKET, 0, sockets);
	pthread_create(&pid, NULL, start_routine, (void *)&sockets[1]);
	fd = sockets[0];

	while (1)
	{
		ret = read(fd, buf, READ_BUF_SIZE);
		buf[ret] = '\0';
		printf("%s[%d]\n", buf, cnt++);

		ret = write(fd, msg, strlen(msg));
	}

	return 0;
}
