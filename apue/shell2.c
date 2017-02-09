#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "apue.h"

void sig_int(int signo)
{
	printf("Interrupt\n");
}

int main(int argc, char *argv[])
{
	char buf[MAXLINE];
	pid_t pid;
	int status;

	if (signal(SIGINT, sig_int) == SIG_ERR)
		err_sys("signal error");

	printf("%% ");
	while (fgets(buf, MAXLINE, stdin) != NULL)
	{
		/* replace newline with null */
		buf[strlen(buf) - 1] = 0;

		if ((pid = fork()) < 0)
		{
			err_sys("fork eror");
		}
		else if (pid == 0) /* child */
		{
			execlp(buf, buf, (char *)0);
			err_ret("could't execute %s", buf);
			exit(127);
		}

		/* parent */
		if ((pid = waitpid(pid, &status, 0)) < 0)
			err_sys("waitpid error");

		printf("%% ");
	}

	exit(0);
}
