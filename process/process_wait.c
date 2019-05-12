#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

void out_status(int status)
{
	/* normal exit ? */
	if (WIFEXITED(status))
		printf("Normal exit: %d\n", WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		printf("Terminated: %d\n", WTERMSIG(status));
	else if (WIFSTOPPED(status))
		printf("Stopped: %d\n", WSTOPSIG(status));
	else
		printf("unknow sig");
}

/*
 * call wait/waitpid to avoid zombe process
 * 如何避免僵尸进程
 * 1. 让僵尸进程的父进程调用wait/waitpid来通知内核回收
 * 2. 采用信号SIGCHLD通知处理,并在信号处理程序中调用wait函数
 * 3. 让僵尸进程称为孤儿进程(杀死其父进程),有init进程回收
 */
int main(int argc, char *argv[])
{
	int status;
	pid_t pid;

	/* child normal exit example */
	if ((pid = fork()) < 0)
	{
		perror("fork error");
		exit(1);
	}
	else if (pid == 0)
	{
		/* child process */
		printf("pid : %d, ppid : %d\n", getpid(), getppid());
		exit(3); /* child exit with 3 which means unusal status */
	}
	else /* parent process */
	{
		/*
		 * parent call wait and blocked
		 * to get chiild exit status
		 */
		wait(&status);
		out_status(status);
	}

	/* child terminate exit example */
	if ((pid = fork()) < 0)
	{
		perror("fork error");
		exit(1);
	}
	else if (pid == 0)
	{
		/* child process */
		printf("pid : %d, ppid : %d\n", getpid(), getppid());
		int i = 3, j = 0;
		int k = i / j;
		printf("k = %d\n", k); /* cause terminate */
	}
	else /* parent process */
	{
		/*
		 * parent call wait and blocked
		 * to get chiild exit status
		 */
		wait(&status);
		out_status(status);
	}

	/* child stop exit example */
	if ((pid = fork()) < 0)
	{
		perror("fork error");
		exit(1);
	}
	else if (pid == 0)
	{
		/* child process */
		printf("pid : %d, ppid : %d\n", getpid(), getppid());

		/* kill -19 to this process */
		pause(); /* wait a signal to wakeup this process */

		//while (1)
		//	sleep(3);
	}
	else /* parent process */
	{
		/* if child once stopped, must using waitpid */
#ifdef BLOCK_VERSION
		waitpid(pid, &status, WUNTRACED); /* blocked call */
#else
		/* none blocked version */
		do {
			pid = waitpid(pid, &status, WNOHANG | WUNTRACED);
			if (pid == 0)
				sleep(2);
		} while (pid == 0);
#endif
		out_status(status);
	}

	return 0;
}
