#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

#define DEFAULT_TIMEOUT	5

void timeout_handler(int unused)
{
	/* Nothing to do */
}

/*
 * Using the interval timer to generate SIGALRM,
 * which a timeout can be implemented
 *
 * timeout version of system call(read)
 * timeout get number
 */
int t_getnum(int timeout)
{
	int n;
	char line[100];
	struct sigaction action;

	action.sa_handler = timeout_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0; /* important */
	sigaction(SIGALRM, &action, NULL);

	alarm(timeout);
	n = read(STDIN_FILENO, line, 100);
	/* signal will break the read block state */

	alarm(0); /* Cancel alarm */
	if (n == -1 && errno == EINTR)
		return -1;

	n = atoi(line);

	return n;
}

int main(int argc, char *argv[])
{
	int num;

	while (1)
	{
		printf("Enter a number: ");
		fflush(stdout);
		if ((num = t_getnum(DEFAULT_TIMEOUT)) == -1)
			printf("Time out\n");
		else
			printf("You entered %d\n", num);
	}

	return 0;
}
