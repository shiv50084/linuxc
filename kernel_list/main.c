#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern struct display_module *display_get_module(const char *name);

int main(int argc, char *argv[])
{
	int var;
	const char *name = "fb_name";
	struct display_module *pModule;

	/* 初始化各子系统 */
	display_init();

	pModule = display_get_module(name);

	/* 调用子系统提供的接口函数 */
	display_InfoShow(pModule);

	display_getVar(pModule, &var);
	printf("var = %d\n", var);

	display_setVar(pModule, 999);
	display_getVar(pModule, &var);
	printf("var = %d\n", var);

	return 0;
}
