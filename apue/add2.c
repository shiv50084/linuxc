#include "apue.h"

int main(int argc, char *argv[])
{
	int bytes;
	int a, b;
	char line[MAXLINE];

	while ( (bytes = read(STDIN_FILENO, line, MAXLINE)) > 0)
	{
		/* null terminate */
		line[bytes] = 0;

		if (sscanf(line, "%d%d", &a, &b) == 2)
		{
			sprintf(line, "%d\n", a + b);
			bytes = strlen(line);

			write(STDOUT_FILENO, line, bytes);
		}
	}

	exit(0);
}
