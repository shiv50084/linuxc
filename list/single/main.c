#include <stdio.h>
#include "linklist.h"

void print_item(struct node *p)
{
	printf("%d ", p->item);
}

int main(int argc, char **argv)
{
	struct node *p;
	int i;
	int raw_data[] = {10, 5, 90};
	int raw_data2[] = {100, 200, 250};

	/* make node and insert to list */
	for (i = 0; i < sizeof(raw_data) / sizeof(raw_data[0]); i++)
	{
		p = make_node(raw_data[i]);
		printf("Insert %d to list head\n", raw_data[i]);
		insert(p);
	}

	/* print list */
	printf("List: ");
	traverse(print_item);
	printf("\n");

	/* delete one */
	printf("Delete %d\n", 90);
	p = search(90);
	delete(p);
	free_node(p);

	/* print list */
	printf("List: ");
	traverse(print_item);
	printf("\n");
	destroy();

	/* make node and insert to list */
	for (i = 0; i < sizeof(raw_data2) / sizeof(raw_data2[0]); i++)
	{
		p = make_node(raw_data2[i]);
		push(p);
	}

	while ( (p = pop()) )
	{
		print_item(p);
		free_node(p);
	}
	printf("\n");

	return 0;
}
