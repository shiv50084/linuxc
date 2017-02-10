#include <ctype.h>
#include "apue.h"

int main(int argc, char *argv[])
{
	int c;

	while ( (c = getchar()) != EOF )
	{
		if (isupper(c))
			c = tolower(c);
		if (putchar(c) == EOF)
			err_sys("output error");
		if (c == '\n')
			fflush(stdout);
	}

	exit(0);
}
