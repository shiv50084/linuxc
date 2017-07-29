#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

struct msg {
	struct msg *next;
	int num;
};

static struct msg *head = NULL;
pthread_cond_t has_product = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *consumer(void *p)
{
	struct msg *tmp;

	/*
	 * fetch from list head if there is a msg there
	 * other wise wait the condition to be true
	 */
	for (;;)
	{
		/* get mutext first */
		pthread_mutex_lock(&lock);

		/*
		 * if the condition false
		 * pthread_cond_wait will do the follow
		 * 1. release mutex
		 * 2. block and wait condition to be ture
		 * 3. get the mutext when wakeup by others
		 */
		while (head == NULL)
			pthread_cond_wait(&has_product, &lock);

		/* condition is true, get the msg from list head */
		tmp = head;
		head = tmp->next;

		/* releas the mutex */
		pthread_mutex_unlock(&lock);

		printf("Consumer <== %d\n", tmp->num);
		free(tmp);
		sleep(2);
	}
}

void *producer(void *p)
{
	struct msg *tmp;

	/* produce a msg to the list head */
	for (;;)
	{
		tmp = malloc(sizeof(struct msg));
		tmp->num = rand() % 1000 + 1;
		printf("Produce ==> %d\n", tmp->num);

		pthread_mutex_lock(&lock);
		tmp->next = head;
		head = tmp;
		pthread_mutex_unlock(&lock);

		/* wakeup consumer */
		pthread_cond_signal(&has_product);
		sleep(2);
	}
}

int main(int argc, char *argv[])
{
	/* producer and consumer thread id */
	pthread_t p_pid, c_pid;

	srand(time(NULL));

	/* create two threads */
	pthread_create(&p_pid, NULL, producer, NULL);
	pthread_create(&c_pid, NULL, consumer, NULL);

	/* wait for threads exit */
	pthread_join(p_pid, NULL);
	pthread_join(c_pid, NULL);

	return 0;
}
