#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__
#include <pthread.h>

#undef USING_MUTEX
typedef struct
{
	int code; /* 账户号 */
	double balance; /* 余额 */

#ifdef USING_MUTEX
	/* 用来对共享资源保护 */
	/*
	 * 建议互斥锁用来锁定一个账户(共享资源)
	 * 和账户绑定在一起
	 * 尽量不要设置成全局变量,否则可能出现一把锁
	 * 去锁定多个用户导致并发性能降低
	 */
	pthread_mutex_t mutex;
#else
	/*
	 * 线程使用互斥锁缺乏读并发性
	 * 当读操作较多,写操作较少时,可以使用读写锁提高线程读并发性
	 */
	pthread_rwlock_t lock;
#endif
}Account;

extern Account *create_account(int code, double balance);
extern void destroy_account(Account *a);
extern double withdraw(Account *a, double amt);
extern double deposit(Account *a, double amt);
extern double get_balance(Account *a);

#endif
