#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
#if 0
	while (1)
	{
		printf(".");
		/*
		 * stdout is buffered
		 * data written to stdout is not send to the console
		 * until the buffer fills
		 */
		fflush(stdout);
		sleep(1);
	}
#else
	while (1)
	{
		/* stderr is not buffered */
		fprintf(stderr, ".");
		sleep(1);
	}
#endif
	return 0;
}
