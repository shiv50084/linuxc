# Linux内核调度器的实现

调度其的任务是在程序之间共享CPU时间,创造并行执行的错觉

该任务分为两个不同的部分
- 调度策略
- 上下文切换

## 经典的调度器实现原理

对系统中的进程分别计算时间片,使进程运行直至时间片用尽,在所有进程的所有时间片都已经用尽时,则需要重新计算

## 当前内核调度前实现原理

只考虑进程的等待时间,即进程在就绪队列(run-queue)中已经等待了多长时间

所有的可运行进程都按等待时间在一个红黑树中排序,等待时间最长的进程将是调度器下一次会考虑的进程

## 调度策略受制约的点

- 进程的不同优先级(nice值)
- 进程不能切换太频繁

## 激活调度

- 直接(进程打算睡眠或是处于其它原因放弃CPU)
- 通过周期性机制,以固定的频率运行,不时检测是否有必要进行进程切换

## 调度器类

调度器类在内核中数据结构(省去部分成员)

```c
struct sched_class {
	const struct sched_class *next;

	void (*enqueue_task) (struct rq *rq, struct task_struct *p, int flags);
	void (*dequeue_task) (struct rq *rq, struct task_struct *p, int flags);
	void (*yield_task) (struct rq *rq);
	bool (*yield_to_task) (struct rq *rq, struct task_struct *p, bool preempt);

	void (*check_preempt_curr) (struct rq *rq, struct task_struct *p, int flags);

	/*
	 * It is the responsibility of the pick_next_task() method that will
	 * return the next task to call put_prev_task() on the @prev task or
	 * something equivalent.
	 *
	 * May return RETRY_TASK when it finds a higher prio class has runnable
	 * tasks.
	 */
	struct task_struct * (*pick_next_task) (struct rq *rq,
						struct task_struct *prev);
	void (*put_prev_task) (struct rq *rq, struct task_struct *p);

	void (*set_curr_task) (struct rq *rq);
	void (*task_tick) (struct rq *rq, struct task_struct *p, int queued);

};
```

- enqueue_task向就绪队列添加新进程,在进程从睡眠状态变为可运行状态时,即发生该操作
- dequeue_task将一个进程从就绪队列中去除,在进程从可运行状态切换到不可运行状态时,就会发生该操作
- 在进程想要放弃对处理器的控制权时,可以用sched_yield系统调用,这将导致内核调用yield_task
- 调用check_preempt_curr用一个新唤醒的进程来抢占当前进程
- pick_next_task用于选择下一个将要运行的进程
- task_tick在每次激活周期性调度器时,由周期性调度器调用

## 就绪队列

各个CPU都有自身的就绪队列,各个活动的进程只出现在一个就绪队列中,所以在多个CPU上同时运行一个进程是不可能的

就绪队列在内核中的数据结构(省去部分成员)

```c
struct rq {
	unsigned int nr_running;
	#define CPU_LOAD_IDX_MAX 5
	unsigned long cpu_load[CPU_LOAD_IDX_MAX];
	struct load_weight load;

	struct cfs_rq cfs;
	struct rt_rq rt;

	struct task_struct *curr, *idle, *stop;
	u64 clock;
};
```

- nr_running指定了队列上可运行的进程数目,不考虑其优先级或调度类
- load提供了就绪队列当前负荷的度量
- cpu_load用于跟踪此前的负荷状态
- cfs和rt是嵌入的子就绪队列,分别用于完全公平调度器和实时调度器
- curr指向当前运行的进程的task_struct实例
- idle指向空闲进程的task_struct实例

## 调度器增强

### SMP调度

在多处理器系统上,内核必须考虑几个额外的问题,确保良好的调度

- CPU负荷必须尽可能公平地在所有处理器上共享
- 进程和系统中某些处理器的亲和性(affinity)必须是可以设置的(将应用程序绑定到指定CPU上运行)
- 内核必须能够将进程从一个CPU迁移到另一个

### 调度域和控制组

调度器并不直接和进程交互,而是处理可调度的实体.这使得可以实现组调度,进程在不同的组中,调度器首先在这些组之间保证公平,然后在组中的所有进程间保证公平
