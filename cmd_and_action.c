#include <stdio.h>
#include <string.h>

struct test {
	int age;
	char name[1024];
};

enum {
	SET_INT,
	SET_STR,
	SET_STRUCT,
	SET_UNKNOW,
};

/*
 * 根据cmd来执行不同的操作
 */
void cmd_and_action(int cmd, void *p)
{
	switch (cmd)
	{
		case SET_INT:
		{
			int *i = p;
			*i = 911;
			break;
		}
		case SET_STR:
		{
			char *str = p;
			strcpy(str, "hello");
			break;
		}
		case SET_STRUCT:
		{
			struct test *t = p;
			t->age = 23;
			strcpy(t->name, "jordan");
			break;
		}
		default:
			printf("unknow cmd\n");
			break;
	};
}

int main(int argc, char **argv)
{
	int i;
	char name[1024] = {0};
	struct test mytest;

	cmd_and_action(SET_INT, &i);
	printf("i = %d\n", i);

	cmd_and_action(SET_STR, name);
	printf("name = %s\n", name);

	cmd_and_action(SET_STRUCT, &mytest);
	printf("mytest.name = %s, age = %d\n", mytest.name, mytest.age);

	cmd_and_action(SET_UNKNOW, &mytest);

	return 0;
}
