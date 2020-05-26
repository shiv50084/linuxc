#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_THREADS 256

#undef THE_ERROR_ONE

#define LEN 256
int array[LEN] = {0};

void *start_routine(void *args)
{
	printf("%s, %d, %d\n", __FUNCTION__, __LINE__, *(int *)args);

	array[*(int *)args] = *(int *)args;

	return 0;
}

int main(int argc, char *argv[])
{
	int ret, i;
    pthread_t tids[NUM_THREADS];
	int values[NUM_THREADS];

	for (i = 0; i < NUM_THREADS; i++)
	{
#ifdef THE_ERROR_ONE
		/*
		 * why this cause error ?
		 * when the new thread spawn a little bit late
		 * which just after i++ finished, this will cause BUG
		 * 因为新线程的启动是操作系统支配的,不确定什么时刻执行新线程
		 * 若执行新线程在i++之后,则会出现异常情况
		 */
		printf("%d ", i);
		ret = pthread_create(&tids[i], NULL, start_routine, &i);
#else
		values[i] = i; /* why must this */
		ret = pthread_create(&tids[i], NULL, start_routine, &values[i]);
#endif
		if (ret != 0)
		{
			perror("create thread error\n");
			return -1;
		}
	}

	/* joint the child threads at the end */
	for (i = 0; i < NUM_THREADS; i++)
		pthread_join(tids[i], NULL);

	for (i = 0; i < LEN; i++)
	{
		if ( (i % 16) == 0)
			printf("\n");

		printf("%3d ", array[i]);
	}

	printf("\n");

	return 0;
}
