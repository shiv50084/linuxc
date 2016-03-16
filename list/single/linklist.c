#include <stdlib.h>
#include <assert.h>
#include "linklist.h"

static struct node *head = NULL;

struct node* make_node(unsigned char item)
{
	struct node *p = NULL;
	
	p = malloc(sizeof(struct node));		
	p->item = item;
	p->next = NULL;

	return p;
}

void free_node(struct node *p)
{
	free(p);
}

struct node* search(unsigned char key)
{
	struct node* p = NULL;

	/* 隐含了对于空链表这种特殊情况的处理,如果是空链表则循环体一次都不执行,直接返回NULL */
	for (p = head; p; p = p->next)
		if (p->item == key)
			return p;

	return NULL;
}

/* 在(空)链表前面插入 */
void insert(struct node* p)
{
	p->next = head;
	head = p;
}

void delete(struct node* p)
{
	struct node *pre;

	assert(p != NULL);

	/* 要删除的是表头 */
	if (p == head)
	{
		head = p->next;
		return;
	}

	for (pre = head; pre; pre = pre->next)
	{
		if (pre->next == p)
		{
			pre->next = pre->next->next;
			return;
		}
	}
}

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

void traverse(void (*visit) (struct node*))
{
	struct node *p;

	for (p = head; p; p = p->next)
		visit(p);
}

void destroy(void)
{
	struct node *p = head;	
	struct node *q;	

	head = NULL;

	while (p)
	{
		q = p;
		p = p->next;
		free_node(q);
	}
}

void push(struct node *p)
{
	insert(p);
}

struct node* pop(void)
{
	/* 链表为空 */
	if (head == NULL)
	{
		return NULL;
	}
	else
	{
		struct node *p = head;
		head = head->next;
		return p;
	}
}
