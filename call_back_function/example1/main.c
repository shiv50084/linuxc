#include <stdio.h>
#include "para_callback.h"

static int cnt = 0;
static int cnt2 = 0;

void say_hello(void *str)
{
	printf("Hello %s, %d times\n", (const char *)str, cnt2++);
}

void count_number(void *num)
{
	int i;

	printf("cnt = %d\n", cnt++);
	for (i = 0; i < (int)num; i++)
		printf("%d ", i);
	printf("\n");
}

int main(int argc, char *argv[])
{
	repeat_three_times(say_hello, (void *)"zeroway");
	repeat_three_times(count_number, (void *)4);
	return 0;
}
