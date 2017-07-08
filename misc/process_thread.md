# 进程

## 引言

每个进程在内核中都有一个进程控制块(PCB)来维护进程相关的信息
Linux内核的进程控制块是 task_struct 结构体,其中有如下信息

- 进程 id,系统中每个进程有唯一的id,在C语言中用pid_t类型表示,其实就是一 个非负整数
- 进程的状态,有运行、挂起、停止、僵尸等状态
- 进程切换时需要保存和恢复的一些CPU寄存器
- 描述虚拟地址空间的信息
- 描述控制终端的信息
- 当前工作目录(Current Working Directory)
- umask 掩码
- 文件描述符表,包含很多指向file结构体的指针
- 和信号相关的信息
- 用户id和组id
- 控制终端、Session 和进程组
- 进程可以使用的资源上限(Resource Limit)

## 特点

- 在各自独立的地址空间中运行
- 共享数据需要mmap或者进程间通信机制

## 守护进程

概念: 没有控制终端,不能直接和用户交互,一直在运行着

### 如何创建一个守护进程

创建守护进程最关键的一步是调用setsid函数创建一个新的Session,并成为Session Leader

## 进程间通信

- 父进程通过 fork 可以将打开文件的描述符传递给子进程
- 子进程结束时,父进程调用 wait 可以得到子进程的终止信息
- 几个进程可以在文件系统中读写某个共享文件,也可以通过给文件加锁来实现进程间同步
- 进程之间互发信号,一般使用 SIGUSR1 和 SIGUSR2 实现用户自定义功能
- 管道(pipe,只能在亲属进程间)
- FIFO(有名管道,可以在不同进程间)
- mmap 函数,几个进程可以映射同一内存区
- SYSV IPC,以前的SYSV UNIX系统实现的IPC机制,包括消息队列,信号量和共享内存,现在已经基本废弃
- UNIX Domain Socket,目前最广泛使用的 IPC 机制

# 线程

线程共享以下进程资源

- 文件描述符表
- 每种信号的处理方式(SIG_IGN SIG_DFL或自定义的信号处理函数)
- 当前工作目录
- 用户id和组id

但是有些资源每个线程各有一份

- 线程id
- 上下文,包括各寄存器的值,程序计数器和栈指针
- 栈空间
- errno变量
- 信号屏蔽字
- 调度优先级

## 关于id

- 进程id的类型是pid_t,每个进程的id在整个系统中是唯一的,调用getpid可以获得当前进程的id
- 线程id的类型是thread_t,它在当前进程中保证唯一,在不同系统中thread_t有不同的实现,可能是一个整数,也可能是一个结构体,也可能是一个地址,所以不能简单的当成整数用printf打印,调用pthread_self可以获得当前线程的id

## 终止线程

只终止某个线程而不终止整个进程

- 从线程函数return(对主线程不合适)
- 一个线程可以调用pthread_cancel终止同一个进程中的另一个线程(分同步和异步)
- 线程可以调用pthread_exit终止自己

## pthread_join

	int pthrad_join(pthread_t thread, void **value_ptr);

调用该函数的线程将挂起等待,知道id为thread的线程终止
thread线程以不同的方法终止,通过pthread_join得到的终止状态是不同的

- 如果thread线程通过return返回,value_ptr所指向的单元里存放的是thread线程函数的返回值
- 如果thread线程被别的线程调用pthread_cancel异常终止掉,value_ptr所指向的单元里存放的是常数PTHREAD——CANCELED
- 如果thread线程是自己调用pthread_exit终止的,value_ptr所指向的单元存放的是传递给pthread_exit的参数

如果对thread线程的终止状态不感兴趣,可以传NULL给value_ptr参数
