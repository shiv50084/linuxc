#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

char *cmd1[3] = {"/bin/cat", "/etc/passwd", NULL};
char *cmd2[3] = {"/bin/grep", "root", NULL};

int main(int argc, char *argv[])
{
	int fd[2];
	int i;
	int pid;

	if (pipe(fd) < 0)
	{
		perror("pipe error");
		exit(1);
	}

	/*
	 * 创建进程扇
	 *		p
	 *	   / \
	 *	 c1   c2
	 *
	 *		cat /etc/fstab    |  grep root
	 *	 c1------------------PIPE------------>c2
	 *
	 *	 cat命令默认输出是标准输出(屏幕)
	 *	 将标准输出重定向(dup2)到管道写端
	 *	 dup2将标准输入和标准输出进行重定向
	 *
	 *	 grep默认从标准输入获取数据
	 *	 dup2将标准输入定向为管道读端后
	 *	 grep将从管道读端获取数据
	 */
	for (i = 0; i < 2; i++)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("fork error");
			exit(1);
		}
		else if (pid == 0) /* child process */
		{
			/* 第一个子进程往管道写数据 */
			if (i == 0)
			{
				/* 关闭读端 */
				close(fd[0]);

				/*
				 * 将标准输出重定向到管道写端
				 * 让命令执行结果写入到管道
				 */
				if (dup2(fd[1], STDOUT_FILENO) != STDOUT_FILENO)
				{
					perror("dup2 error");
					exit(1);
				}
				close(fd[1]);

				/* 执行的命令结果将输出到管道写端 */
				if (execvp(cmd1[0], cmd1) < 0)
				{
					perror("execvp error");
					exit(1);
				}
				break;
			}

			/* 第二个子进程负责从管道读数据 */
			if (i == 1)
			{
				/* 关闭写端 */
				close(fd[1]);

				/* 将标准输入重定向位管道读端 */
				if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO)
				{
					perror("dup2 error");
					exit(1);
				}
				close(fd[0]);

				/* 执行的命令将从管道读端获取数据 */
				if (execvp(cmd2[0], cmd2) < 0)
				{
					perror("execvp error");
					exit(1);
				}
				break;
			}
		}
		else
		{
			/* 父进程必须等到所有子进程全部创建完毕才回收 */
			if (i == 1)
			{
				close(fd[0]);
				close(fd[1]);
				wait(0);
				wait(0);
			}
		}
	}
	return 0;
}
