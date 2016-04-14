#include <stdio.h>

/* Ctrl-D表示EOF */
/*
 * Usage:
 * gcc -o upper upper.c
 * ./upper < file.txt
 */
int main(int argc, char *argv[])
{
	int ch;

	/* 从标准输入中读入数据转化为大写输出到标准输出 */
	while ((ch = getchar()) != EOF)
		putchar(toupper(ch));

	return 0;
}
