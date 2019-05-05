#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int g_v = 10;

int main(int argc, char *argv[])
{
	FILE *fp = NULL;
	int fd;
	pid_t pid;
	int a_v = 10;
	static int s_v = 10;

	printf("current pid: %d\n", getpid());

	/* IO with buffer */
	fp = fopen("test_fp.txt", "w");
	if (NULL == fp)
	{
		perror("Open file error");
		return -1;
	}

	/* no buffer IO */
	fd = open("test_fd.txt",
			O_WRONLY | O_CREAT | O_TRUNC,
			S_IRWXU | S_IRWXG);
	if (fd < 0)
	{
		perror("open file error");
		return -2;
	}

	char tmp[1024];
	const char *s = "hello process";

	/* call in parent */
	/*
	 * stand IO function(with full buffer)
	 * write data into buffer first
	 * the buffer is in stack
	 * when fork new process, child will copy the stack
	 */
	fprintf(fp, "s:%s, pid:%d", s, getpid());

	/*
	 * system IO call (no buffer)
	 * write data into file immediately
	 */
	sprintf(tmp, "s:%s, pid:%d", s, getpid());
	write(fd, tmp, strlen(tmp));

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
	}
	else
	{
		/* child */
		printf("This is child pid: %d, my parent id: %d\n", getpid(), getppid());

	}

	/* both parent and child will call this */
	/* write data into buffer */
	fprintf(fp, "-->pid:%d, g_v:%d, a_v:%d, s_v:%d\n", getpid(), g_v, a_v, s_v);

	/* write data into file immediately */
	sprintf(tmp, "-->pid:%d, g_v:%d, a_v:%d, s_v:%d\n", getpid(), g_v, a_v, s_v);
	write(fd, tmp, strlen(tmp));

	/* without close file */
	//fclose(fp);
	//close(fd);

	return 0;
}
