#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int var;
	const char *name = "MODULE_name";

	/* 初始化各子系统 */
	SUBSYSTEM_init();

	/* 调用子系统提供的接口函数 */
	SUBSYSTEM_InfoShow(name);

	SUBSYSTEM_getVar(name, &var);
	printf("var = %d\n", var);

	SUBSYSTEM_setVar(name, 999);

	SUBSYSTEM_getVar(name, &var);
	printf("var = %d\n", var);
	return 0;
}
