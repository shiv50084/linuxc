#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <signal.h>
#include <time.h>
#include <errno.h>
#include <pthread.h>
#include <arpa/inet.h>

#include "vector_fd.h"

#undef DEBUG_INFO
#ifdef DEBUG_INFO
#define DPRINT(mesg, ...) fprintf(stderr, mesg, __VA_ARGS__)
#else
#define DPRINT(mesg, ...)
#endif

VectorFD *vfd;
int sockfd;

void sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		printf("Server closed\n");
		close(sockfd);
		destory_vector_fd(vfd);
		exit(1);
	}
}

/* print out client connect infomation */
void printout_info(struct sockaddr_in *addr)
{
	char ip[16];
	int port;

	memset(ip, 0, sizeof(ip));
	port = ntohs(addr->sin_port);
	inet_ntop(AF_INET, &addr->sin_addr.s_addr, ip, sizeof(ip));
	printf("%s(%d) connected\n", ip, port);
}

/*
 * fd对应于连接的客户端
 * 和客户端进行非阻塞双向通信
 */
void do_service(int fd)
{
	char buff[512];

	memset(buff, 0, sizeof(buff));

	/*
	 * 因为采用非阻塞方式, 若读不到数据直接返回
	 * 直接服务下一个客户端
	 * 因此不需要判断size小于0的情况
	 */
	size_t size = read(fd, buff, sizeof(buff));
	DPRINT("read fd[%d]size = %d\n", fd, size);
	if (size == 0) /* 客户端断开连接 */
	{
		printf("Client closed\n");
		/* write(STDOUT_FILENO, info, sizeof(info)); */
		remove_fd(vfd, fd);
		close(fd);
	}
	else if (size > 0)
	{
		printf("%s\n", buff);
		/* write(STDOUT_FILENO, buff, sizeof(buff)); */
		if (write(fd, buff, size) < 0)
		{
			if (errno == EPIPE) /* client close the connect */
			{
				perror("Write error");
				remove_fd(vfd, fd);
				close(fd);
			}
		}
	}
}

/*
 * travel the vfd
 * add fd into set
 * return the maxfd
 */
int add_set(fd_set *set)
{
	int i;
	int maxfd;
	int fd;

	FD_ZERO(set);

	/* assume the first one is max */
	maxfd = vfd->fd[0];

	for (i = 0; i < vfd->counter; i++)
	{
		fd = get_fd(vfd, i);
		if (fd > maxfd)
			maxfd = fd;

		/* add fd into set */
		FD_SET(fd, set);
	}

	return maxfd;
}

void *routine(void *arg)
{
	struct timeval t;
	int nr;
	int maxfd;
	fd_set rset;
	int i;
	int fd;

	/* setup timeout */
	t.tv_sec = 2;
	t.tv_usec = 0;

	/* construction the fd set */
	maxfd = add_set(&rset);

	while ((nr = select(maxfd+1, &rset, NULL, NULL, &t)) >= 0)
	{
		/* we got available fd */
		if (nr > 0)
		{
			for (i = 0; i < vfd->counter; i++)
			{
				fd = get_fd(vfd, i);
				/* kernel will set fd in nonblock mode */
				if (FD_ISSET(fd, &rset))
					do_service(fd);
			}
		}

		/* TIMEOUT : let's resetup something */
		DPRINT("Timeout...\n");

		/* 1. resetup the timeout */
		t.tv_sec = 2;
		t.tv_usec = 0;

		/* 2. reconstruction the fd set */
		maxfd = add_set(&rset);
	}

	return (void *)0;
}

int main(int argc, char *argv[])
{
	/* each client connect fd and flags */
	int fd;

	/* pthread variables */
	pthread_t tid;
	pthread_attr_t attr;

	/* server address */
	struct sockaddr_in serv_addr;

	/* client address */
	struct sockaddr_in cli_addr;
	socklen_t cli_addr_len = sizeof(cli_addr);

	if (argc < 2)
	{
		printf("Usage %s <port>\n", argv[0]);
		exit(1);
	}

	/* register a sigint handler */
	if (signal(SIGINT, sig_handler) == SIG_ERR)
	{
		perror("Signal sigint error");
		exit(1);
	}

	/* tcp socket */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		perror("socket error");
		exit(1);
	}

	/* server address setup */
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[1]));
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	/* bind server address */
	if (bind(sockfd, (struct sockaddr *)&serv_addr,
				sizeof(serv_addr)) < 0)
	{
		perror("Bind error");
		exit(1);
	}

	/* start to listen on the port */
	if (listen(sockfd, 10) < 0)
	{
		perror("Listen error");
		exit(1);
	}

	/* create vfd */
	vfd = create_vector_fd();

	/* set thread detach state */
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	if (pthread_create(&tid, &attr, routine, (void *)0) != 0)
	{
		perror("Create thread error\n");
		exit(1);
	}
	pthread_attr_destroy(&attr);

	while (1)
	{
		fd = accept(sockfd, (struct sockaddr *)&cli_addr, &cli_addr_len);
		if (fd < 0)
		{
			perror("Accept error");
			exit(1);
		}
		printout_info(&cli_addr);

		/* add each client fd into vfd */
		add_fd(vfd, fd);
	}

	return 0;
}
