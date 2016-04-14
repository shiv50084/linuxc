#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int fd;
	if (argc != 2) {
		fputs("usage: wrapper file\n", stderr);
		exit(1);
	}
	fd = open(argv[1], O_RDONLY);
	if(fd<0) {
		perror("open");
		exit(1);
	}

	/* 将标准输入重定向到这个文件 */
	dup2(fd, STDIN_FILENO);
	close(fd);

	/*
	 * 原来打开的文件描述符仍然是打开的,upper 程序只负责从标准
	 * 输入读入字符转成大写,并不关心标准输入对应的是文件还是终端
	 */
	execl("./upper", "upper", NULL);
	perror("exec ./upper");
	exit(1);
}

