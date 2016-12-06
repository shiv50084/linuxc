#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "display_ss.h"

static struct display_module bModule;

static void fb_setVar(int in)
{
	bModule.var = in;
}

static void fb_getVar(int *out)
{
	*out = bModule.var;
}

static void fb_printInfo(const char *name)
{
	printf("<%s> : %s\n", name, __FUNCTION__);
}

static struct display_module bModule = {
	.name = "fb_name",
	.var = -1,
	.printInfo = fb_printInfo,
	.setVar = fb_setVar,
	.getVar = fb_getVar,
};

int fb_init(void)
{
	/* 调用子系统提供的注册接口向子系统注册模块 */
	return fb_register(&bModule.list);
}
