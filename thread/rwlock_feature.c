#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

/*
 * 读写锁特性
 * 1. 读和读 : 不排斥
 * 2. 读和写 : 排斥
 * 3. 写和写 : 排斥
 */
int main(int argc, char *argv[])
{
	pthread_rwlock_t rwlock;

	if (argc < 3)
	{
		fprintf(stderr, "Usage : %s <r|w> <r|w>\n", argv[0]);
		exit(1);
	}

	pthread_rwlock_init(&rwlock, NULL);
	if (!strcmp(argv[1], "w"))
	{
		if (pthread_rwlock_wrlock(&rwlock) != 0)
			printf("1th write lock failure\n");
		else
			printf("1th write lock success\n");
	}
	else /* using read lock as default */
	{
		if (pthread_rwlock_rdlock(&rwlock) != 0)
			printf("1th read lock failure\n");
		else
			printf("1th read lock success\n");
	}

	if (!strcmp(argv[2], "w"))
	{
		if (pthread_rwlock_wrlock(&rwlock) != 0)
		{
			printf("2nd write lock failure\n");
			goto unlock_once;
		}
		else
			printf("2nd write lock success\n");
	}
	else /* using read lock as default */
	{
		if (pthread_rwlock_rdlock(&rwlock) != 0)
		{
			printf("2nd read lock failure\n");
			goto unlock_once;
		}
		else
			printf("2nd read lock success\n");
	}

	/* unlock twice */
	pthread_rwlock_unlock(&rwlock);
unlock_once:
	pthread_rwlock_unlock(&rwlock);

	/* destory the lock */
	pthread_rwlock_destroy(&rwlock);

	return 0;
}
