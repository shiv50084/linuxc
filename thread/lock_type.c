#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	pthread_mutex_t mutex;

	if (argc < 2)
	{
		fprintf(stderr, "-usage:%s <error | normal | recursive>\n", argv[0]);
		exit(0);
	}

	/* mutext attribute */
	pthread_mutexattr_t mutexattr;
	pthread_mutexattr_init(&mutexattr);

	if (!strcmp(argv[1], "error")) /* 第一次成功, 第二次出错 */
		pthread_mutexattr_settype(&mutexattr,
				PTHREAD_MUTEX_ERRORCHECK);
	else if (!strcmp(argv[1], "normal")) /* 第一次成功,第二次阻塞 */
		pthread_mutexattr_settype(&mutexattr,
				PTHREAD_MUTEX_NORMAL);
	else if (!strcmp(argv[1], "recursive")) /* 第一次成功,第二次也成功,内部计数 */
		pthread_mutexattr_settype(&mutexattr,
				PTHREAD_MUTEX_RECURSIVE);
	else
	{
		pthread_mutexattr_settype(&mutexattr,
				PTHREAD_MUTEX_NORMAL);
		printf("Lock with normal\n");
	}

	/* let's lock twice */
	pthread_mutex_init(&mutex, &mutexattr);
	if (pthread_mutex_lock(&mutex) != 0)
		printf("lock failure\n");
	else
		printf("lock success\n");

	if (pthread_mutex_lock(&mutex) != 0)
		printf("lock failure\n");
	else
		printf("lock success\n");


	/* unlock need twice too */
	pthread_mutex_unlock(&mutex);
	pthread_mutex_unlock(&mutex);

	pthread_mutexattr_destroy(&mutexattr);
	pthread_mutex_destroy(&mutex);

	return 0;
}
