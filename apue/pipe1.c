#include "apue.h"

const char *msg1 = "This is parent speaking\n";

int main(int argc, char *argv[])
{
	int rbyte;
	int fd[2];
	pid_t pid;
	char line[MAXLINE];

	if (pipe(fd) < 0)
		err_sys("pipe error");

	if ((pid = fork()) < 0)
	{
		err_sys("fork error");
	}
	else if (pid > 0) /* parent */
	{
		close(fd[0]);
		write(fd[1], msg1, strlen(msg1));
	}
	else /* child */
	{
		close(fd[1]);
		rbyte = read(fd[0], line, MAXLINE);
		write(STDOUT_FILENO, line, rbyte);
	}

	exit(0);
}
