#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

static jmp_buf buf;

int main(int argc, char *argv[])
{
	volatile int b = 3;
	int longjmp_ret = 1;

	if (setjmp(buf) != 0)
	{
		printf("==>%d\n", b);
		exit(0);
	}

	printf("let's make value b equal to 5, and longjmp\n");
	printf("after longjmp, the setjmp will return longjmp_ret\n");
	b = 5;
	longjmp(buf, longjmp_ret);
}
