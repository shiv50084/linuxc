#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork error");
	}
	else if (pid == 0)
	{
		/*
		 * child became a zombe process
		 * ps aux | grep process_zombe
		 */
		printf("This is child pid: %d, my parent id: %d\n", getpid(), getppid());
		exit(0);
	}
	else
	{
		/*
		 * parent must call wait to collect the child resource
		 * to avoid the zombe process
		 */
		//wait(NULL);

		printf("This is parent pid: %d, my child id: %d\n", getpid(), pid);
		while (1)
			sleep(3);
	}

	return 0;
}
