#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 2

/*
 * start routines functions point array
 * contain all the start routines
 */
void *(*routines[NUM_THREADS])(void*);

void *start_routine1(void *args)
{
	int cnt;

	cnt = *(int *)args;

	while (1)
	{
		printf("***%s, (value = %d)\n", __FUNCTION__, cnt);
		sleep(cnt);

	}
}

void *start_routine2(void *args)
{
	int cnt;

	cnt = *(int *)args;

	while (1)
	{
		printf("###%s, (value = %d)\n", __FUNCTION__, cnt);
		sleep(cnt);

	}
}

int main(int argc, char *argv[])
{
	int ret, i;
	int values[NUM_THREADS] = {1, 2};

    pthread_t tids[NUM_THREADS];

	/* init the function point array */
	routines[0] = start_routine1;
	routines[1] = start_routine2;

	for (i = 0; i < NUM_THREADS; i++)
	{
		ret = pthread_create(&tids[i], NULL, routines[i], &values[i]);
		if (ret != 0)
		{
			perror("create thread error\n");
			return -1;
		}

		/*
		 * shouldn't join here
		 * or there just one child thread running not two
		 */
		//pthread_join(tids[i], NULL);
	}

	/* joint the child threads at the end */
	for (i = 0; i < NUM_THREADS; i++)
		pthread_join(tids[i], NULL);

	return 0;
}
