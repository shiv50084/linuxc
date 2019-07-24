#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include "account.h"

Account *create_account(int code, double balance)
{
	Account *a = (Account *)malloc(sizeof(Account));
	assert(a != NULL);
	a->code = code;
	a->balance = balance;

#ifdef USING_MUTEX
	printf("Mutex implementation\n");
	pthread_mutex_init(&a->mutex, NULL);
#endif

#ifdef USING_RWLOCK
	printf("ReadWriteLock implementation\n");
	pthread_rwlock_init(&a->lock, NULL);
#endif

#ifdef USING_SEM
	printf("Semaphore implementation\n");
	sem_init(&a->sem, 0, 1);
#endif

	printf("%d balance %f\n", a->code, a->balance);

	return a;
}

void destroy_account(Account *a)
{
	assert(a != NULL);

#ifdef USING_MUTEX
	pthread_mutex_destroy(&a->mutex);
#endif

#ifdef USING_RWLOCK
	pthread_rwlock_destroy(&a->lock);
#endif

#ifdef USING_SEM
	sem_destroy(&a->sem);
#endif

	free(a);
}

double withdraw(Account *a, double amt)
{
	double balance;
	assert(a != NULL);

	/* 操作临界资源就开始加锁 */
#ifdef USING_MUTEX
	pthread_mutex_lock(&a->mutex);
#endif

#ifdef USING_RWLOCK
	pthread_rwlock_wrlock(&a->lock);
#endif

	/*
	 * PV操作
	 * P操作递减
	 * V操作递增
	 */
#ifdef USING_SEM
	/* P(1)操作 */
	sem_wait(&a->sem);
#endif

	if (amt < 0 || amt > a->balance)
	{
#ifdef USING_MUTEX
		pthread_mutex_unlock(&a->mutex);
#endif

#ifdef USING_RWLOCK
		pthread_rwlock_unlock(&a->lock);
#endif

#ifdef USING_SEM
		/* V(1)操作 */
		sem_post(&a->sem);
#endif
		return 0.0;
	}

	balance = a->balance;
	sleep(1); /* mimic query database */

	balance -= amt;
	a->balance = balance; /* update to database */

#ifdef USING_MUTEX
		pthread_mutex_unlock(&a->mutex);
#endif

#ifdef USING_RWLOCK
		pthread_rwlock_unlock(&a->lock);
#endif

#ifdef USING_SEM
		sem_post(&a->sem);
#endif

	return amt;
}

double deposit(Account *a, double amt)
{
	double balance;

	assert(a != NULL);

	/* 操作临界资源就开始加锁 */
#ifdef USING_MUTEX
	pthread_mutex_lock(&a->mutex);
#endif

#ifdef USING_RWLOCK
	pthread_rwlock_wrlock(&a->lock);
#endif

#ifdef USING_SEM
	sem_wait(&a->sem);
#endif

	if (amt < 0)
	{
#ifdef USING_MUTEX
		pthread_mutex_unlock(&a->mutex);
#endif

#ifdef USING_RWLOCK
		pthread_rwlock_unlock(&a->lock);
#endif

#ifdef USING_SEM
		sem_post(&a->sem);
#endif

		return 0.0;
	}

	balance = a->balance;
	sleep(1); /* mimic query database */
	balance += amt;
	a->balance = balance; /* update to database */

#ifdef USING_MUTEX
		pthread_mutex_unlock(&a->mutex);
#endif

#ifdef USING_RWLOCK
		pthread_rwlock_unlock(&a->lock);
#endif

#ifdef USING_SEM
		sem_post(&a->sem);
#endif

	return amt;
}

double get_balance(Account *a)
{
	double balance = -0.0;
	assert(a != NULL);

#ifdef USING_MUTEX
	pthread_mutex_lock(&a->mutex);
	balance = a->balance;
	pthread_mutex_unlock(&a->mutex);
#endif

#ifdef USING_RWLOCK
	pthread_rwlock_rdlock(&a->lock);
	balance = a->balance;
	pthread_rwlock_unlock(&a->lock);
#endif

#ifdef USING_SEM
	sem_wait(&a->sem);
	balance = a->balance;
	sem_post(&a->sem);
#endif

	return balance;
}
