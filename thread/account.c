#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "account.h"

Account *create_account(int code, double balance)
{
	Account *a = (Account *)malloc(sizeof(Account));
	assert(a != NULL);
	a->code = code;
	a->balance = balance;

	pthread_mutex_init(&a->mutex, NULL);
	printf("%d balance %f\n", a->code, a->balance);

	return a;
}

void destroy_account(Account *a)
{
	assert(a != NULL);
	pthread_mutex_destroy(&a->mutex);
	free(a);
}

double withdraw(Account *a, double amt)
{
	double balance;
	assert(a != NULL);

	/* 操作临界资源就开始加锁 */
	pthread_mutex_lock(&a->mutex);

	if (amt < 0 || amt > a->balance)
	{
		pthread_mutex_unlock(&a->mutex);
		return 0.0;
	}

	balance = a->balance;
	sleep(1); /* mimic query database */

	balance -= amt;
	a->balance = balance; /* update to database */

	pthread_mutex_unlock(&a->mutex);

	return amt;
}

double deposit(Account *a, double amt)
{
	double balance;

	assert(a != NULL);

	/* 操作临界资源就开始加锁 */
	pthread_mutex_lock(&a->mutex);

	if (amt < 0)
	{
		pthread_mutex_unlock(&a->mutex);
		return 0.0;
	}

	balance = a->balance;
	sleep(1); /* mimic query database */
	balance += amt;
	a->balance = balance; /* update to database */

	pthread_mutex_unlock(&a->mutex);

	return amt;
}

double get_balance(Account *a)
{
	double balance;
	assert(a != NULL);

	pthread_mutex_lock(&a->mutex);
	balance = a->balance;
	pthread_mutex_unlock(&a->mutex);

	return balance;
}
