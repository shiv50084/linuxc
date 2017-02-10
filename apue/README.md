# Advanced Programming in the UNIX Environment

## IPC

### 例子1

创建一个从父进程到子进程的管道,并且父进程向子进程传递数据

```c
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
```

### 例子2

下面程序每次显示一页数据,由于more具有这个功能,所以可以将输出的数据传递给more

```c
#include <sys/wait.h>
#include "apue.h"

/* default pager program */
#define DEF_PAGER "/bin/more"

int main(int argc, char *argv[])
{
	int rbyte;
	int fd[2];
	pid_t pid;
	char *pager;
	char *argv0;
	char line[MAXLINE];
	FILE *fp;

	if (argc != 2)
		err_quit("Usage: %s <filename>", argv[0]);

	if ((fp = fopen(argv[1], "r")) == NULL)
		err_sys("can't open %s", argv[1]);

	if (pipe(fd) < 0)
		err_sys("pipe error");

	if ((pid = fork()) < 0)
	{
		err_sys("fork error");
	}
	else if (pid > 0) /* parent */
	{
		close(fd[0]);

		while (fgets(line, MAXLINE, fp) != NULL)
		{
			rbyte = strlen(line);
			if (write(fd[1], line, rbyte) != rbyte)
				err_sys("write to pipe error");
		}
		if (ferror(fp))
			err_sys("fgets error");

		close(fd[1]);

		if (waitpid(pid, NULL, 0) < 0)
			err_sys("waitpid error");

		exit(0);
	}
	else /* child */
	{
		close(fd[1]);

		/* dup fd0 to stdin */
		if (fd[0] != STDIN_FILENO)
		{
			if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO)
			{
				err_sys("dup2 error");
			}
			close(fd[0]);
		}

		/* get argument for execl */
		if ((pager = getenv("PAGER")) == NULL)
			pager = DEF_PAGER;

		if ((argv0 = strrchr(pager, '/')) != NULL)
			argv0++;
		else
			argv0 = pager;

		if (execl(pager, argv0, (char *)0) < 0)
			err_sys("execl error for %s", pager);
	}

	exit(0);
}
```

### 例子3

函数popen先执行fork,然后调用exec执行cmdstring
并且返回一个标准I/O文件指针
如果type是"r",则文件指针连接到cmdstring的标准输出
如果type是"w",则文件指针连接到cmdstring的标准输入

![popen](./popen.png)

```c
#include <sys/wait.h>
#include "apue.h"

/* environment variable or default(more) */
#define PAGER "${PAGER:-more}"

int main(int argc, char *argv[])
{
	char line[MAXLINE];
	FILE *fpin, *fpout;

	if (argc != 2)
		err_quit("Usage : %s <filename>", argv[0]);

	if ((fpin = fopen(argv[1], "r")) < 0)
		err_sys("can't open %s", argv[1]);

	if ((fpout = popen(PAGER, "w")) == NULL)
		err_sys("popen error");

	/* copy argv[1] to pager */
	while (fgets(line, MAXLINE, fpin) != NULL)
	{
		if (fputs(line, fpout) == EOF)
			err_sys("fputs to pipe error");
	}

	if (ferror(fpin))
		err_sys("fgets error");

	if (pclose(fpout) == -1)
		err_sys("pclose error");

	exit(0);
}
```

### 例子4

下面程序,向标准输出写一个提示
然后从标准输入读入1行,使用popen可以在应用程序
和输入之间插入一个程序以对输入进行处理,
下面代码的处理程序是将大写字母转换为小写

![popen1](./popen1.png)

```c
#include <sys/wait.h>
#include "apue.h"

int main(int argc, char *argv[])
{
	char line[MAXLINE];
	FILE *fpin;

	if ( (fpin = popen("./myuclc", "r")) == NULL )
		err_sys("popen error");

	for (;;)
	{
		fputs("prompt> ", stdout);
		fflush(stdout);

		/* read from pipe */
		if (fgets(line, MAXLINE, fpin) == NULL)
			break;

		if (fputs(line, stdout) == EOF)
			err_sys("fputs error to pipe");
	}

	if (pclose(fpin) == -1)
		err_sys("pclose error");

	putchar('\n');
	exit(0);
}
```
