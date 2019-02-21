#include <stdio.h>
#include <stdlib.h>

struct Person {
	int age;
	char name[20];
};

void print_info(struct Person *p)
{
	printf("%s:%d\n", p->name, p->age);
}

int main(int argc, char *argv[])
{
	int i;

	/*
	 * (gdb) b main
	 * (gdb) r
	 * (gdb) set $p = (struct Person *)malloc(sizeof(struct Person))
	 * (gdb) set $p->age = 911
	 * (gdb) set $p->name = "anonymous"
	 * (gdb) call print_info($p)
	 * anonymous:911
	 * (gdb)
	 */
	for (i = 0; i < 10; i++)
		printf("%s, %d\n", __FUNCTION__, __LINE__);

	return 0;
}
