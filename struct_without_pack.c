#include <stdio.h>

struct node
{
	char a;
	char b;
	short c;
	int d;
};

/*
 * +--------+
 * |	a	|
 * ----------
 * |	b	|
 * ----------
 * |	c	|
 * |		|
 * ----------
 * |	d	|
 * |		|
 * |		|
 * |		|
 * +--------+
 */

int main(int argc, char *argv[])
{
	struct node s = { 3, 5, 6, 99 };
	struct node *pt = &s;

	/* result must be 60503 */
	printf("%x\n", *(int*)pt);

	return 0;
}
