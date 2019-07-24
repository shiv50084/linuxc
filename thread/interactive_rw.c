#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#undef DEBUG
typedef struct {
	int value; /* hold the data */

	/* for reader */
	pthread_cond_t r_cond;
	pthread_mutex_t r_mutex;
	int read_ready;

	/* for writer */
	pthread_cond_t w_cond;
	pthread_mutex_t w_mutex;
	int write_ready;
}Storage;

int get_data(Storage *s)
{
	return s->value;
}

void set_data(Storage *s, int value)
{
	s->value = value;
}

void *read_routine(void *argc)
{
	int ret;
	Storage *s = (Storage *)argc;
	int i;

	for (i = 0; i < 100; i++)
	{
		/*
		 * mark ready to read data
		 * wait someone wakeup and notify to read
		 */
		pthread_mutex_lock(&s->r_mutex);
		s->read_ready = 1;
		pthread_cond_wait(&s->r_cond, &s->r_mutex);
		pthread_mutex_unlock(&s->r_mutex);

		/* wakeup, read the data */
		ret = get_data(s);
		printf("0x%lx(%-5d) <<< %d\n", pthread_self(), i, ret);

		/* 判断写线程是否能继续写入数据 */
		pthread_mutex_lock(&s->w_mutex);
		while (!s->write_ready)
		{
			pthread_mutex_unlock(&s->w_mutex);
			sleep(1);
			pthread_mutex_lock(&s->w_mutex);
		}
		s->write_ready = 0;
		pthread_mutex_unlock(&s->w_mutex);

#ifdef DEBUG
		sleep(1);
#endif
		/*
		 * 代码能运行到这里说明
		 * 写线程已经准备好再次写入数据
		 * 通知写线程继续写入数据
		 */
		pthread_cond_broadcast(&s->w_cond);
	}

	return (void *)0;
}

void *write_routine(void *argc)
{
	Storage *s = (Storage *)argc;
	int i;

	for (i = 0; i < 100; i++)
	{
		/* write data to storage */
		set_data(s, i + 100);
		printf("0x%lx(%-5d) >>> %d\n", pthread_self(), i, i + 100);

		/* is reader get ready to receive the data? */
		pthread_mutex_lock(&s->r_mutex);
		while (!s->read_ready)
		{
			pthread_mutex_unlock(&s->r_mutex);
			sleep(1);
			pthread_mutex_lock(&s->r_mutex);
		}
		s->read_ready = 0;
		pthread_mutex_unlock(&s->r_mutex);

		/*
		 * 代码能跑到这里说明读线程已经准备好读取数据
		 * 通知读线程去读取数据
		 * if runs here, means the reader is ready
		 * notify the read routine to readout data
		 */
		pthread_cond_broadcast(&s->r_cond);

#ifdef DEBUG
		sleep(1);
#endif

		/* mark ready to write again */
		pthread_mutex_lock(&s->w_mutex);
		s->write_ready = 1;
		pthread_cond_wait(&s->w_cond, &s->w_mutex);
		pthread_mutex_unlock(&s->w_mutex);
	}

	return (void *)0;
}

/*
 * 一个线程读,一个线程写
 * 写线程写完数据后通知读线程去读书据,后休眠等待再次写入数据
 * 读线程读完数据后通知写线程取写数据,后休眠等待新数据写入
 */
int main(int argc, char *argv[])
{
	int err;
	pthread_t tid_r, tid_w;
	Storage s;

	s.read_ready = 0;
	s.write_ready = 0;
	pthread_mutex_init(&s.r_mutex, NULL);
	pthread_mutex_init(&s.w_mutex, NULL);
	pthread_cond_init(&s.r_cond, NULL);
	pthread_cond_init(&s.w_cond, NULL);

	if ((err = pthread_create(&tid_r, NULL,
					read_routine, (void *)&s)) != 0)
	{
		perror("pthread create error");
	}

	if ((err = pthread_create(&tid_w, NULL,
					write_routine, (void *)&s)) != 0)
	{
		perror("pthread create error");
	}

	pthread_join(tid_r, NULL);
	pthread_join(tid_w, NULL);

	pthread_mutex_destroy(&s.w_mutex);
	pthread_mutex_destroy(&s.r_mutex);
	pthread_cond_destroy(&s.w_cond);
	pthread_cond_destroy(&s.r_cond);

	return 0;
}
