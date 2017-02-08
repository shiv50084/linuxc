#include <stdio.h>
#include <stdlib.h>

/*
 * print out the environment variables
 */
int main(int argc, char **argv)
{
#if PRINT_ALL
	extern char **environ;
	char *oldpwd;

	while (*environ)
		printf("%s\n", *environ++);
#else
	printf("PATH = %s\n", getenv("PATH"));
	printf("OLDPWD = %s\n", getenv("OLDPWD"));
#endif

	return 0;
}
