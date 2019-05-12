#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char *cmd1 = "ls";
char *cmd2 = "/bin/ls";
char *argv1 = "-al";
char *argv2 = "/etc/passwd";
char *const argvs[4] = {"ls", "-al", "/etc/group", NULL};

int main(int argc, char *argv[])
{
	pid_t pid;

	/* execl example */
	if ((pid = fork()) < 0)
	{
		perror("fork error");
		exit(1);
	}
	else if (pid == 0)
	{
		/* child process call exec run new program */
		if (execl(cmd2, cmd1, argv1, argv2, NULL) < 0)
		{
			perror("execl error");
			exit(1);
		}
		else
			printf("execl success\n");
	}
	else /* parent */
	{
		wait(NULL);
	}

	/* execvp example */
	if ((pid = fork()) < 0)
	{
		perror("fork error");
		exit(1);
	}
	else if (pid == 0)
	{
		/* child process call exec run new program */
		if (execvp(cmd1, argvs) < 0)
		{
			perror("execl error");
			exit(1);
		}
		else
			printf("execl success\n");
	}
	else /* parent */
	{
		wait(NULL);
	}

	return 0;
}
