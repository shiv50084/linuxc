#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	const char *name = "MODULE_name";

	/* 初始化各子系统 */
	SUBSYSTEM_init();

	/* 调用子系统提供的接口函数 */
	SUBSYSTEM_InfoShow(name);
	return 0;
}
