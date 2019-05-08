#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/*
 * create a process link as below
 * parent->child->child->...>child
 *
 * using `pstree` to check
 */
int main(int argc, char *argv[])
{
	int counter = 0;
	int i;
	pid_t pid;

	if (argc < 2)
		counter = 2;
	else
		counter = atoi(argv[1]);

	/* i = 1, ignore the main proces */
	for (i = 1; i < counter; i++)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("fork error");
			exit(1);
		}
		else if (pid > 0)
		{
			/* parent exit the loop */
			printf("This is parent pid: %d, my child id: %d\n", getpid(), pid);
			break;
		}
		else
		{
			/* child continue fork loop */
			printf("This is child pid: %d, my parent id: %d\n", getpid(), getppid());
		}
	}

	while (1)
		sleep(2);

	return 0;
}
