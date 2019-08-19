#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
 * read write file at specifiy position
 *
 * pread/pwrite不管当前文件位置,使用的是pos提供的值
 * 1. 这两个调用更加简单
 * 2. 操作完成时不修改文件位置指针
 * 3. 避免了任何在使用lseek时可能出现的潜在竞争
 * 由于线程共享文件描述符,可能一个线程调用lseek后,尚未进行读写操作前,
 * 另外一个线程修改文件位置, 就可以使用pread/pwrite来避免这样的竞争
 */
int main(int argc, char *argv[])
{
	int fd;
	char buf[100];
	int start_pos;
	int rlen;
	int i;

	if (argc < 4)
	{
		fprintf(stderr, "%s <file> <start_pos> <len>\n", argv[0]);
		exit(1);
	}

	fd = open(argv[1], O_CREAT | O_RDWR);
	if (fd < 0)
	{
		perror("open error\n");
		exit(1);
	}

	start_pos = strtol(argv[2], NULL, 0);
	rlen = strtol(argv[3], NULL, 0);

	/* read rlen start from position start_pos */
	pread(fd, buf, rlen, start_pos);
	buf[rlen] = '\0';
	printf("buf << %s\n", buf);

	/* write buf to start position */
	for (i = 0; i < rlen; i++)
	{
		if (isupper(buf[i]))
			buf[i] = tolower(buf[i]);
		else
			buf[i] = toupper(buf[i]);
	}
	printf("buf >> %s\n", buf);

	pwrite(fd, buf, rlen, start_pos);

	close(fd);

	return 0;
}
