#include <stdio.h>
#include <unistd.h>

/*
 * 查看终端对应的设备文件名
 * 在图形终端窗口下运行这个程序结果可能是/dev/pts/0
 * 用 Ctrl-Alt-F1 切换到字符终端运行这个程序结果是/dev/tty1
 */

int main(int argc, char *argv[])
{
	printf("fd 0 : %s\n", ttyname(0));
	printf("fd 1 : %s\n", ttyname(1));
	printf("fd 2 : %s\n", ttyname(2));
	return 0;
}
