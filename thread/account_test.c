#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include "account.h"

typedef struct
{
	char name[20];
	Account *account;
	double amt;
}OperArg;

void *withdraw_routine(void *arg)
{
	OperArg *oa = (OperArg *)arg;
	double amt = withdraw(oa->account, oa->amt);

	printf("%s(0x%lx) withdraw %f from account %d\n",
			oa->name, pthread_self(),
			amt, oa->account->code);

	return (void *)0;
}

void *deposit_routine(void *arg)
{
	OperArg *oa = (OperArg *)arg;
	double amt = deposit(oa->account, oa->amt);

	printf("%s(0x%lx) deposit %f from account %d\n",
			oa->name, pthread_self(),
			amt, oa->account->code);

	return (void *)0;
}

int main(int argc, char *argv[])
{
	int err;
	pthread_t boy, girl;
	OperArg o1, o2;

	/* 一张银行卡两个用户同时操作 */
	Account *a = create_account(1000001, 10000);

	strcpy(o1.name, "boy");
	o1.account = a;
	o1.amt = 10000;

	strcpy(o2.name, "girl");
	o2.account = a;
	o2.amt = 10000;

	if ((err = pthread_create(&boy, NULL,
					withdraw_routine, (void *)&o1)) != 0)
		perror("pthread create error");

	if ((err = pthread_create(&girl, NULL,
					deposit_routine, (void *)&o2)) != 0)
		perror("pthread create error");

	pthread_join(boy, NULL);
	pthread_join(girl, NULL);

	printf("Account balance: %f\n", get_balance(a));

	destroy_account(a);

	return 0;
}
