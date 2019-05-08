#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

/*
 * Test :
 * touch file.txt
 * 1. tail -f file.txt in one terminal
 * 2. open a new terminal to execute
 * process_append file.txt
 */
int main(int argc, char *argv[])
{
	int fd;
	pid_t pid;

	printf("current pid: %d\n", getpid());

	if (argc < 2)
	{
		fprintf(stderr, "Usage : %s <file>\n", argv[0]);
		exit(1);
	}

	/* no buffer IO */
	fd = open(argv[1], O_WRONLY);
	if (fd < 0)
	{
		perror("open file error, try touch a file");
		return -1;
	}

	printf("Start to fork process...\n");
	pid = fork();
	if (pid < 0)
	{
		perror("fork error");
		exit(1);
	}
	else if (pid > 0)
	{
		/* parent do file seek */
		printf("This is parent pid: %d, my child id: %d\n", getpid(), pid);

		/* seek to end of file */
		if (lseek(fd, 0L, SEEK_END) < 0)
		{
			perror("seek file error");
			exit(1);
		}
	}
	else
	{
		/* child do writing data */
		printf("This is child pid: %d, my parent id: %d\n", getpid(), getppid());

		const char *str = "\nEND MESSAGE\n";
		ssize_t size = strlen(str) * sizeof(char);

		/* make sure parent run first */
		sleep(3);

		/* fd is a copy of parent's fd */
		if (write(fd, str, size) != size)
		{
			perror("write data error");
			exit(1);
		}
	}

	/* parent and child close fd */
	close(fd);

	return 0;
}
