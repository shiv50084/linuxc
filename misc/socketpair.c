#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

/*
 * Usage:
 * thread version:
 * 	gcc socketpair.c -lpthread
 *
 * process version:
 * 	gcc socketpair.c -DFORK_VERSION
 */

#define READ_BUF_SIZE 512

/*
 * 父子(进程)线程通过socketpair来通信
 * child --- say hello to ---> main
 * main  --- reply to ---> child
 */

#ifdef FORK_VERSION
#else
void *start_routine(void *argv)
{
	int cnt = 0;
	int fd = *(int *)argv;
	int ret;
	const char *msg = "Child thread";
	char buf[READ_BUF_SIZE];

	while (1)
	{
		ret = send(fd, msg, strlen(msg), MSG_WAITALL);

		ret = recv(fd, buf, READ_BUF_SIZE, MSG_WAITALL);
		buf[ret] = '\0';
		printf("%s[%d]\n", buf, cnt++);

		sleep(2);
	}
}
#endif

int main(int argc, char *argv[])
{
	int cnt = 0;
	int ret;
	pthread_t pid;
	int sockets[2];
	int fd;
	char buf[READ_BUF_SIZE];
#ifdef FORK_VERSION
#else
	const char *msg = "Main thread";
#endif

	socketpair(AF_UNIX, SOCK_SEQPACKET, 0, sockets);

#ifdef FORK_VERSION
	pid = fork();
	if (pid == 0)
	{
		/* Child Process */
		const char *child_msg = "Child Process";
		while (1)
		{
			ret = send(sockets[0], child_msg, strlen(child_msg), MSG_WAITALL);

			ret = recv(sockets[0], buf, READ_BUF_SIZE, MSG_WAITALL);
			buf[ret] = '\0';
			printf("%s[%d]\n", buf, cnt++);

			sleep(2);
		}
	}
	else /* Main Process */
	{
		const char *main_msg = "Main Process";
		while (1)
		{
			ret = recv(sockets[1], buf, READ_BUF_SIZE, MSG_WAITALL);
			buf[ret] = '\0';
			printf("%s[%d]\n", buf, cnt++);

			ret = send(sockets[1], main_msg, strlen(main_msg), MSG_WAITALL);
		}

	}
#else
	pthread_create(&pid, NULL, start_routine, (void *)&sockets[1]);

	fd = sockets[0];

	while (1)
	{
		ret = recv(fd, buf, READ_BUF_SIZE, MSG_WAITALL);
		buf[ret] = '\0';
		printf("%s[%d]\n", buf, cnt++);

		ret = send(fd, msg, strlen(msg), MSG_WAITALL);
	}
#endif
	return 0;
}
