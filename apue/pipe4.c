#include <signal.h>
#include "apue.h"

void sig_pipe(int signo)
{
	printf("SIGPIPE caught\n");
	exit(1);
}

int main(int argc, char *argv[])
{
	int n;
	int fd1[2]; /* for write */
	int fd2[2]; /* for read */
	pid_t pid;
	char line[MAXLINE];

	if (signal(SIGPIPE, sig_pipe) == SIG_ERR)
		err_sys("signal error");

	if (pipe(fd1) < 0 || pipe(fd2) < 0)
		err_sys("pipe error");

	if ( (pid = fork()) < 0 )
		err_sys("fork error");
	else if (pid > 0) /* parent */
	{
		close(fd1[0]);
		close(fd2[1]);

		/* parent read from stdin */
		while (fgets(line, MAXLINE, stdin) != NULL)
		{
			n = strlen(line);

			/* write to coprocess */
			if (write(fd1[1], line, n) != n)
				err_sys("write to pipe error");

			/* read result from coprocess */
			if ( (n = read(fd2[0], line, MAXLINE)) < 0 )
				err_sys("read from pipe error");

			if (0 == n)
			{
				err_msg("coprocess closed pipe");
				break;
			}

			/* null terminate */
			line[n] = 0;

			if (fputs(line, stdout) == EOF)
				err_sys("fputs error");
		}
		if (ferror(stdin))
			err_sys("fgets error on stdin");
		exit(0);
	}
	else /* coprocess */
	{
		close(fd1[1]);
		close(fd2[0]);

		/* redirection pipe to stdin and stdout */
		if (fd1[0] != STDIN_FILENO)
		{
			if (dup2(fd1[0], STDIN_FILENO) != STDIN_FILENO)
				err_sys("dup2 error to stdin");
			close(fd1[0]);
		}

		if (fd2[1] != STDOUT_FILENO)
		{
			if (dup2(fd2[1], STDOUT_FILENO) != STDOUT_FILENO)
				err_sys("dup2 error to stdout");
			close(fd2[1]);
		}

		if (execl("./add2", "add2", (char *)0) < 0)
			err_sys("execl error");
	}

	exit(0);
}
