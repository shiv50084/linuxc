#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int array[256] = {0};
#define NUM_THREADS 256
char ipbase[20] = {0};
#define MAXLINE 4096

void *start_routine(void *arg)
{
	char cmd[1024];
	char line[MAXLINE];
	FILE *fpin;
	char *token;
	int i, j;

	sprintf(cmd, "ping -c 1 -w 1 %s.%d", ipbase, *(int *)arg);

	/* read the command output */
	if ((fpin = popen(cmd, "r")) == NULL)
		printf("popen error");

	/* read five lines */
	for (i = 0; i < 5; i++)
	{
		fflush(stdout);

		if (fgets(line, MAXLINE, fpin) == NULL)
			break;

		/* only care the line 4 */
		if (i == 3)
		{
			for (j = 0, token = strtok(line, ","); token != NULL;
					token = strtok(NULL, ","), j++)
			{
				/* only the unalive ipaddr will show this line */
				if (j == 2)
				{
					/* printf("[%d] %s\n", *(int *)arg, token); */
					array[*(int *)arg] = *(int *)arg;
					break;
				}
			}
		}
	}

	if (pclose(fpin) == -1)
		printf("pclose error");

	return NULL;
}

int main(int argc, char *argv[])
{
	int err;
	int i;
	pthread_t tid[NUM_THREADS];
	int values[NUM_THREADS];

	if (argc < 2)
	{
		printf("Usage : %s 172.28.107\n", argv[0]);
		return -1;
	}
	strcpy(ipbase, argv[1]);

	for (i = 0; i < NUM_THREADS; i++)
	{
		values[i] = i;
		if ((err = pthread_create(&tid[i], NULL,
						start_routine, &values[i])) != 0)
			perror("create thread failed\n");
	}

	for (i = 0; i < NUM_THREADS; i++)
		pthread_join(tid[i], NULL);

	/* print out the available ipaddress */
	for (i = 0; i < 256; i++)
	{
		if ((i % 16) == 0)
			printf("\n");

		if (0 == array[i])
			printf("%3c ", 'X');
		else
			printf("%3d ", array[i]);
	}
	printf("\n");

	return 0;
}
