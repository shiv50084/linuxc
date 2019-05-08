#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	pid_t pid;

	printf("current pid: %d\n", getpid());

	printf("Start to fork process...\n");
	pid = fork();
	if (pid < 0)
	{
		perror("fork error");
	}
	else if (pid > 0)
	{
		printf("%d deaded\n", getpid());
		exit(1);
	}
	else
	{
		/* make sure parent process exit done */
		sleep(4);
		printf("pid : %d, ppid : %d\n", getpid(), getppid());
	}

	return 0;
}
