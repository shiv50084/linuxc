#include <stdio.h>
#include "linklist.h"

void print_item(struct node *p)
{
	printf("%d ", p->item);
}

int main(int argc, char **argv)
{
	struct node *p = make_node(10);
	insert(p);

	p = make_node(5);
	insert(p);

	p = make_node(90);
	insert(p);

	/* print list */
	traverse(print_item);
	printf("\n");

	/* delete one */
	p = search(90);
	//delete(p);
	delete_plus(p);
	free_node(p);

	traverse(print_item);
	printf("\n");
	destroy();

	p = make_node(100);
	push(p);
	p = make_node(200);
	push(p);
	p = make_node(250);
	push(p);

	while (p = pop())
	{
		print_item(p);
		free_node(p);
	}
	printf("\n");

	return 0;
}
