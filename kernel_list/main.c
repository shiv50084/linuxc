#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern struct SUBSYSTEM_module *SUBSYSTEM_get_module(const char *name);

int main(int argc, char *argv[])
{
	int var;
	const char *name = "MODULE_name";
	struct SUBSYSTEM_module *pModule;

	/* 初始化各子系统 */
	SUBSYSTEM_init();

	pModule = SUBSYSTEM_get_module(name);

	/* 调用子系统提供的接口函数 */
	SUBSYSTEM_InfoShow(pModule);

	SUBSYSTEM_getVar(pModule, &var);
	printf("var = %d\n", var);

	SUBSYSTEM_setVar(pModule, 999);
	SUBSYSTEM_getVar(pModule, &var);
	printf("var = %d\n", var);

	return 0;
}
