#include <stdio.h>
#include "binarytree.h"

void print_item(struct node *p)
{
	printf("%d", p->item);
}

int main(int argc, char **argv)
{
	/* 根据前序和中序遍历结果构造二叉树 */
	unsigned char pre_seq[] = { 4, 2, 1, 3, 6, 5, 7 };
	unsigned char in_seq[] = { 1, 2, 3, 4, 5, 6, 7 };

	struct node * root = init(pre_seq, in_seq, 7);

	printf("pre:\n");
	pre_order(root, print_item);
	putchar('\n');

	printf("in:\n");
	in_order(root, print_item);
	putchar('\n');

	printf("post:\n");
	post_order(root, print_item);
	putchar('\n');

	printf("count=%d depth=%d\n", count(root), depth(root));

	destroy(root);

	return 0;
}
