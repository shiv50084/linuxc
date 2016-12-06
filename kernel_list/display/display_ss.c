#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "display_ss.h"

/* 将该子系统里所有模块都装入链表 */
LIST_HEAD(display_list);

struct display_module *display_get_module(const char *name)
{
	struct display_module *pModule;

	list_for_each_entry(pModule, &display_list, list)
	{
		if (!strcmp(name, pModule->name))
			return pModule;
	}

	return NULL;
}

/* 调用各个子模块的初始化函数 */
void display_modules_init(void)
{
	struct display_module *pModule;

	list_for_each_entry(pModule, &display_list, list)
	{
		if (pModule->initDevice)
			pModule->initDevice(pModule);
	}
}

/* 开放给底层具体模块的注册接口 */
int display_register(struct list_head *list)
{
	list_add(list, &display_list);
	return 0;
}

/* 开放给应用层调用 */
int display_init(void)
{
	/* 调用个模块初始化函数 */
	fb_init();
	crt_init();
}

void display_InfoShow(struct display_module *pModule)
{
	pModule->printInfo(pModule->name);
}

void display_setVar(struct display_module *pModule, int in)
{
	pModule->setVar(in);
}

void display_getVar(struct display_module *pModule, int *out)
{
	pModule->getVar(out);
}
