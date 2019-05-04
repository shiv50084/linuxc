#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void term_function_a(void)
{
	printf("termination a\n");
}

void term_function_b(void)
{
	printf("termination b\n");
}
void term_function_c(void)
{
	printf("termination c\n");
}

void print_usage(const char *name)
{
	fprintf(stderr, "Usage : %s <file> <exit | _exit | return>\n", name);
}

int main(int argc, char *argv[])
{
	FILE *fp = NULL;

	if (argc < 3)
	{
		print_usage(argv[0]);
		return -1;
	}

	/* register termination functions */
	atexit(term_function_a);
	atexit(term_function_b);
	atexit(term_function_c);

	fp = fopen(argv[1], "w");
	/* fprintf is a full cached function */
	fprintf(fp, "Process termination with %s!\n", argv[2]);

	/* fclose(fp) will flush the cache */

	/*
	 *-------------------------------------------------
	 *			  | return | exit() |  _exit()/_Exit()
	 *------------|--------|--------|------------------
	 * Flush I/O  |  Y     |  Y     |     N
	 *------------|--------|--------|------------------
	 * Call term  |        |        |
	 * function	  |  Y	   |  Y	    |    N
	 *-------------------------------------------------
	 */
	if (!strcmp(argv[2], "exit"))
		exit(1); /* c lib function api */
	else if (!strcmp(argv[2], "_exit"))
		_exit(2); /* system call */
	else if (!strcmp(argv[2], "return"))
		return 0;
	else
		print_usage(argv[0]);

	return 0;
}
