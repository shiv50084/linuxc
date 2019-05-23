#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct {
	int x;
	int y;
}Arg;

void *start_routine(void *p)
{
	Arg *arg = (Arg *)p;

	arg->x = 100;
	arg->y = 200;

	/* return (Arg *)arg */
	return (void *)arg;
}

int main(int argc, char *argv[])
{
	int err;
	pthread_t tid;
	int *result;
	Arg arg = {1, 3};

	if ((err = pthread_create(&tid, NULL, start_routine, (void *)&arg)) != 0)
	{
		perror("pthread create error\n");
		exit(1);
	}

	/* how to get child thread return value */
	pthread_join(tid, (void **)&result);
	/* (Arg *)result = (Arg *)arg */

	printf("result = %d\n", ((Arg *)result)->x + ((Arg *)result)->y);

	return 0;
}
