#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "subsystem.h"

static void MODULE_printInfo(void)
{
	printf("%s, %d\n", __FUNCTION__, __LINE__);
}

static struct MODULE_module bModule = {
	.name = "MODULE_name",
	.printInfo = MODULE_printInfo,
};

int MODULE_init(void)
{
	/* 调用子系统提供的注册接口向子系统注册模块 */
	return MODULE_register(&bModule.list);
}
