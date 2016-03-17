#内核如何实现信号的捕捉
如果信号的处理动作是用户自定义函数,在信号递达时就调用这个函数,这称为捕捉信号.  
由于信号处理函数的代码是在用户空间的,处理过程比较复杂,举例如下:  

1. 用户程序注册了 SIGQUIT 信号的处理函数 sighandler.  
2. 当前正在执行 main 函数,这时发生中断或异常切换到内核态.  
3. 在中断处理完毕后要返回用户态的 main 函数之前检查到有信号 SIGQUIT 递达.  
4. 内核决定返回用户态后不是恢复 main 函数的上下文继续执行,而是执行 sighandler 函数,sighandler 和 main 函数使用不同的堆栈空间,它们之间不存在调用和被调用的关系,是两个独立的控制流程。  
5. sighandler 函数返回后自动执行特殊的系统调用 sigreturn 再次进入内核态。  
6. 如果没有新的信号要递达,这次再返回用户态就是恢复 main 函数的上下文继续执行了。  

如下图所示:

![kernel catch signal](./pngs/signal.png)


#使用二级指针巧妙删除链表节点
```c
/*
 * delete 的优化版本
 * 不需要对是否是删除头部特殊判断
 * 这里巧用了二级指针操作
 * 一个指向当前节点的二级指针就是其上一节点
 */
void delete_plus(struct node *p)
{
	struct node **pnext;

	for (pnext = &head; *pnext; pnext = &(*pnext)->next)
	{
		if (*pnext == p)
		{
			*pnext = p->next;
			return;
		}
	}
}
```

![delete](./pngs/delete.png)
