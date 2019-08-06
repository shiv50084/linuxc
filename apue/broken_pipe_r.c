#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/* 读一个写端已经关闭的管道 */
int main(int argc, char *argv[])
{
	int fd[2];
	int pid;

	if (pipe(fd) < 0)
	{
		perror("pipe error");
		exit(1);
	}

	if ((pid = fork()) < 0)
	{
		perror("fork error");
		exit(1);
	}
	else if (pid > 0) /* parent process, read */
	{
		/* 父进程从不完整管道(写端关闭)读取数据 */
		sleep(5); /* 让子进程将写端关闭 */

		close(fd[1]);

		while (1)
		{
			char c;

			if (read(fd[0], &c, 1) == 0)
			{
				printf("\nwrite-end of pipe closed\n");
				break;
			}
			else
				printf("%c", c);

		}
		close(fd[0]);
		wait(0);
	}
	else /* child process, write */
	{
		close(fd[0]);

		char *s = "abcd";
		write(fd[1], s, strlen(s));
		close(fd[1]);
	}

	return 0;
}
