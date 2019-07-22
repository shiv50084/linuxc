#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

/* 一个线程负责计算结果, 多个线程负责获取结果 */
typedef struct
{
	int res; /* hold the result */
	int counter; /* number user of the result receiver */

	pthread_mutex_t mutex;
	pthread_cond_t cond;
} Result;

/* do calculate */
void *calc_routine(void *argc)
{
	Result *r = (Result *)argc;
	int i, sum = 0;

	for (i = 0; i < 101; i++)
		sum += i;
	r->res = sum; /* prepare the result */

	/* is get routine ready for the result? */
	pthread_mutex_lock(&r->mutex);
	while (r->counter < 2) /* 判断至少有2个接收线程已经就绪 */
	{
		pthread_mutex_unlock(&r->mutex);
		usleep(100);
		pthread_mutex_lock(&r->mutex);
	}
	pthread_mutex_unlock(&r->mutex);

	/*
	 * 接收线程已经准备好,正等待接收结果
	 * 唤醒接收线程
	 */
	pthread_cond_broadcast(&r->cond);

	return (void *)0;
}

/* get result */
void *get_routine(void *argc)
{
	Result *r = (Result *)argc;

	/*
	 * 对两个线程共享的判断条件进行保护(加锁)
	 * mutex 同时保护了counter和等待队列
	 */
	pthread_mutex_lock(&r->mutex); /* 和pthread_cond_wait里的第一个unlock配对 */
	r->counter++;	/* increase the counter */

	/*
	 * 条件变量内部执行的操作
	 * what happend inside the pthread_cond_wait
	 * 1. unlock(&mutex) // 和前面代码的lock配对
	 * 2. lock(&mutex)
	 * 3. 将线程本身插入到条件变量的等待队列中
	 * 4. unlock(&mutex)
	 * 5. 当前等待的线程阻塞(等待其它线程通知唤醒该线程)
	 * 6. 唤醒后,lock(&mutex) // 和后面代码的unlock配对
	 * 7. 从等待队列中删除线程本身
	 *
	 * 也就是为什么条件变量一般会和互斥锁一起配合使用
	 */
	pthread_cond_wait(&r->cond, &r->mutex); /* 这里为什么放在unlock前 */

	pthread_mutex_unlock(&r->mutex); /* 和pthread_cond_wait里的唤醒后的lock配对 */

	printf("0x%lx get result %d\n", pthread_self(), r->res);

	return (void *)0;
}

int main(int argc, char *argv[])
{
	int err;
	pthread_t tid_calc, tid_get0, tid_get1;

	Result r;
	r.counter = 0;
	pthread_cond_init(&r.cond, NULL);
	pthread_mutex_init(&r.mutex, NULL);

	if ((err = pthread_create(&tid_get0, NULL,
					get_routine, (void *)&r)) != 0)
	{
		perror("pthread create error");
	}

	if ((err = pthread_create(&tid_get1, NULL,
					get_routine, (void *)&r)) != 0)
	{
		perror("pthread create error");
	}

	if ((err = pthread_create(&tid_calc, NULL,
					calc_routine, (void *)&r)) != 0)
	{
		perror("pthread create error");
	}

	pthread_join(tid_calc, NULL);
	pthread_join(tid_get0, NULL);
	pthread_join(tid_get1, NULL);

	pthread_cond_destroy(&r.cond);
	pthread_mutex_destroy(&r.mutex);

	return 0;
}
