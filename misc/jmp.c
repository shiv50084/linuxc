#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

static jmp_buf buf;

/* exception mechanism in C language */
int main(int argc, char *argv[])
{
	volatile int b = 3;
	int longjmp_ret = 91;

	/* x86_64 register rax hold the return value of call function */
	if (setjmp(buf) != 0) /* using gdb check return value, (gdb) p $rax */
	{ /* set break point at this line */
		printf("==>%d\n", b);
		exit(0);
	}

	printf("let's make value b equal to 5, and longjmp\n");
	printf("after longjmp, the setjmp will return longjmp_ret\n");
	b = 5;
	longjmp(buf, longjmp_ret);
}
