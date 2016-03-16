#include <stdlib.h>
#include <assert.h>
#include "doublylinkedlist.h"

struct node tailsentinel;
struct node headsentinel = {0, NULL, &tailsentinel};
struct node tailsentinel = {0, &headsentinel, NULL};

static struct node *head = &headsentinel;
static struct node *tail = &tailsentinel;

struct node* make_node(unsigned char item)
{
	struct node *p = NULL;
	
	p = malloc(sizeof(struct node));		
	p->item = item;
	p->prev = NULL;
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

	for (p = head->next; p != tail; p = p->next)
		if (p->item == key)
			return p;

	return NULL;
}

void insert(struct node* p)
{
	p->next = head->next;
	head->next->prev = p;
	head->next = p;
	p->prev = head;
}

void delete(struct node* p)
{
	p->prev->next = p->next;
	p->next->prev = p->prev;
}

void traverse(void (*visit) (struct node*))
{
	struct node *p;

	for (p = head->next; p != tail; p = p->next)
		visit(p);
}

void destroy(void)
{
	struct node *p = head->next;
	struct node *q;	

	head->next = tail;
	tail->prev = head;

	while (p != tail)
	{
		q = p;
		p = p->next;
		free_node(q);
	}
}

void enqueue(struct node *p)
{
	insert(p);
}

/* 尾部出列 */
struct node* dequeue(void)
{
	/* 空链表 */
	if (tail->prev == head)
		return NULL;
	else
	{
		struct node *p = tail->prev;
		delete(p);
		return p;
	}
}
