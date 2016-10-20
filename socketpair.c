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
		ret = write(fd, msg, strlen(msg));
		
		ret = read(fd, buf, READ_BUF_SIZE);
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
			ret = write(sockets[0], child_msg, strlen(child_msg));

			ret = read(sockets[0], buf, READ_BUF_SIZE);
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
			ret = read(sockets[1], buf, READ_BUF_SIZE);
			buf[ret] = '\0';
			printf("%s[%d]\n", buf, cnt++);

			ret = write(sockets[1], main_msg, strlen(main_msg));
		}

	}
#else
	pthread_create(&pid, NULL, start_routine, (void *)&sockets[1]);

	fd = sockets[0];

	while (1)
	{
		ret = read(fd, buf, READ_BUF_SIZE);
		buf[ret] = '\0';
		printf("%s[%d]\n", buf, cnt++);

		ret = write(fd, msg, strlen(msg));
	}
#endif
	return 0;
}
