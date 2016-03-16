#include <stdlib.h>
#include "binarytree.h" 

static struct node* make_node(unsigned char item)
{
	struct node *p = NULL;

	p = malloc(sizeof(struct node));
	p->item = item;
	p->l = NULL;
	p->r = NULL;

	return p;
}

static void free_node(struct node *p)
{
	free(p);
}

struct node* init(unsigned char VLR[], unsigned char LVR[], int n)
{
	struct node *t;
	int k;

	if (n <= 0)
		return NULL;

	for (k = 0; VLR[0] != LVR[k]; k++);

	t = make_node(VLR[0]);
	t->l = init(VLR + 1, LVR, k);
	t->r = init(VLR + 1 + k, LVR + 1 + k, n - k - 1);

	return t;
}

void pre_order(struct node *t, void(*visit)(struct node *))
{
	if (!t)
		return;

	visit(t);
	pre_order(t->l, visit);
	pre_order(t->r, visit);
}

void in_order(struct node *t, void(*visit)(struct node *))
{
	if (!t)
		return;

	pre_order(t->l, visit);
	visit(t);
	pre_order(t->r, visit);
}

void post_order(struct node *t, void(*visit)(struct node *))
{
	if (!t)
		return;

	pre_order(t->l, visit);
	pre_order(t->r, visit);
	visit(t);
}

int count(struct node *t)
{
	if (!t)
		return 0;

	return 1 + count(t->l) + count(t->r);

}

int depth(struct node *t)
{
	/*
	 * dl:depth of left child
	 * dr:depth of right child
	 */
	int dl, dr;

	if (!t)
		return 0;

	dl = depth(t->l);
	dr = depth(t->r);

	/* 深度去左右子树大的 */
	return 1 + (dl > dr ? dl : dr);
}

void destroy(struct node *t)
{
	post_order(t, free_node);
}
