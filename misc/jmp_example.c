#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

static jmp_buf buf;

/*
 * Exception handler mechanism in C language
 * the goto can only 'jump to' local module
 * jmp function can 'jump to' any where
 */
void set_jmp(void)
{
	int status;
	/*
	 * set jump point, return 0 on success
	 * if longjmp happen, the return value will be set to val
	 */
	status = setjmp(buf);
	if (status != 0)
	{
		switch (status)
		{
			case 1:
				printf("case %d\n", status);
				break;
			case 2:
				printf("case %d\n", status);
				break;
			default:
				printf("default\n");
				break;
		}
		exit(0);
	}
}

void foo(int val)
{
	/* setjmp return value will be set to val */
	longjmp(buf, val);
}

int main(int argc, char *argv[])
{
	int err_code;

	if (argc < 2)
	{
		printf("Usage %s <err_code>\n", argv[0]);
		printf("err_code should not equal to zero\n");
		exit(0);
	}

	err_code = atoi(argv[1]);

	set_jmp();

	foo(err_code);

	return 0;
}
