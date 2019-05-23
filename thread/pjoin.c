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

	return (void *)(arg->x + arg->y);
}

int main(int argc, char *argv[])
{
	int err;
	pthread_t tid;
	int *result;
	Arg arg = {1, 2};

	if ((err = pthread_create(&tid, NULL, start_routine, (void *)&arg)) != 0)
	{
		perror("pthread create error\n");
		exit(1);
	}

	/* how to get child thread return value */
	pthread_join(tid, (void **)&result);

	/*
	 * int *result --> [  NULL  ]
	 * &result = (void *)(arg->x + arg->y);
	 * int *result --> [ x + y ]
	 */
	printf("result = %d\n", (int)result);

	return 0;
}
