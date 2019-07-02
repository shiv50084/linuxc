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
	pthread_mutex_init(&a->mutex, NULL);
#else
	pthread_rwlock_init(&a->lock, NULL);
#endif

	printf("%d balance %f\n", a->code, a->balance);

	return a;
}

void destroy_account(Account *a)
{
	assert(a != NULL);

#ifdef USING_MUTEX
	pthread_mutex_destroy(&a->mutex);
#else
	pthread_rwlock_destroy(&a->lock);
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
#else
	pthread_rwlock_wrlock(&a->lock);
#endif

	if (amt < 0 || amt > a->balance)
	{
#ifdef USING_MUTEX
		pthread_mutex_unlock(&a->mutex);
#else
		pthread_rwlock_unlock(&a->lock);
#endif
		return 0.0;
	}

	balance = a->balance;
	sleep(1); /* mimic query database */

	balance -= amt;
	a->balance = balance; /* update to database */

#ifdef USING_MUTEX
		pthread_mutex_unlock(&a->mutex);
#else
		pthread_rwlock_unlock(&a->lock);
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
#else
	pthread_rwlock_wrlock(&a->lock);
#endif

	if (amt < 0)
	{
#ifdef USING_MUTEX
		pthread_mutex_unlock(&a->mutex);
#else
		pthread_rwlock_unlock(&a->lock);
#endif
		return 0.0;
	}

	balance = a->balance;
	sleep(1); /* mimic query database */
	balance += amt;
	a->balance = balance; /* update to database */

#ifdef USING_MUTEX
		pthread_mutex_unlock(&a->mutex);
#else
		pthread_rwlock_unlock(&a->lock);
#endif

	return amt;
}

double get_balance(Account *a)
{
	double balance;
	assert(a != NULL);

#ifdef USING_MUTEX
	pthread_mutex_lock(&a->mutex);
	balance = a->balance;
	pthread_mutex_unlock(&a->mutex);
#else
	pthread_rwlock_rdlock(&a->lock);
	balance = a->balance;
	pthread_rwlock_unlock(&a->lock);
#endif

	return balance;
}
