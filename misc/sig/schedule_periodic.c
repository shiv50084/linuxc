#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>

char *p;
char buffer[10000];

#define DEFAULT_TIMEOUT 10

void sig_handler(int signum)
{
	int fd;

	fd = open("buffer.save", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("Open failed\n");
		exit(-1);
	}

	write(fd, buffer, p - buffer);
	close(fd);

	alarm(DEFAULT_TIMEOUT);
}

/* tail -f buffer.save */
int main(int argc, char *argv[])
{
	int count;
	struct sigaction action;

	p = buffer;

	action.sa_handler = sig_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_RESTART;
	sigaction(SIGALRM, &action, NULL);
	alarm(DEFAULT_TIMEOUT);

	/* Accumulate text from stdin into buffer */
	while (count = read(STDIN_FILENO, p, 200))
		p += count;

	return 0;
}
