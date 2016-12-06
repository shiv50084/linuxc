#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern struct display_module *display_get_module(const char *name);

const char *module_name[] = {"fb_name", "crt_name"};

int main(int argc, char *argv[])
{
	int var;
	struct display_module *pModule;
	int i;

	/* 初始化各子系统及其模块 */
	display_init();
	display_modules_init();

	for (i = 0; i < sizeof(module_name) / sizeof(module_name[0]); i++)
	{
		pModule = display_get_module(module_name[i]);

		/* 调用子系统提供的接口函数 */
		display_InfoShow(pModule);

		display_getVar(pModule, &var);
		printf("var = %d\n", var);

		display_setVar(pModule, 999);
		display_getVar(pModule, &var);
		printf("var = %d\n", var);
	}

	return 0;
}
