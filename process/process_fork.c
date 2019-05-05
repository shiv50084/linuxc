#include <stdio.h>
#include <unistd.h>

/* global value in data section */
int g_v = 10;

int main(int argc, char *argv[])
{
	/* (automatic value)local value in stack */
	int a_v = 10;

	/* static value in data section */
	static int s_v = 10;

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
		/* parent */
		printf("This is parent pid: %d, my child id: %d\n", getpid(), pid);
		g_v = 20;
		a_v = 20;
		s_v = 20;
		printf("g_v:%d(%p), a_v:%d(%p), s_v:%d(%p)\n",
				g_v, &g_v, a_v, &a_v, s_v, &s_v);
	}
	else
	{
		/* child */
		printf("This is child pid: %d, my parent id: %d\n", getpid(), getppid());

		/*
		 * child process will copy the whole
		 * parent's virtual memory address
		 * so, the g_v, a_v, s_v address is the
		 * same with parent which is virtual address
		 * but different in physical address
		 */
		g_v = 30;
		a_v = 30;
		s_v = 30;
		printf("g_v:%d(%p), a_v:%d(%p), s_v:%d(%p)\n",
				g_v, &g_v, a_v, &a_v, s_v, &s_v);
	}

	printf("g_v:%d, a_v:%d, s_v:%d\n", g_v, a_v, s_v);

	return 0;
}
