#include <stdio.h>

#define LEN 10
int stack[LEN];

/* 栈顶指针,指向空数据的位置 */
int stack_top = 0;
/*
 *    +-------------+
 *    |	data1		|
 *    +-------------+
 *    |	data2		|
 *    +-------------+
 *    |				| <---stack_top
 *    +-------------+
 *    |				|
 *    +-------------+
 */

void push(int item)
{
	stack[stack_top++] = item;
}

/* 因为栈顶指针指向的是空数据的位置,所以是前减减 */
int pop(void)
{
	return stack[--stack_top];
}

int is_empty(void)
{
	return stack_top == 0;
}

int main(int argc, char **argv)
{
	push(1);
	push(3);
	push(4);

	while (!is_empty())
		printf("%d\n", pop());

	return 0;
}
