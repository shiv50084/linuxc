#ifndef _SUBSYSTEM_H_
#define _SUBSYSTEM_H_

#include "klist.h"
struct MODULE_module {
	char name[20];
	int var;

	void (*printInfo)(void);
	void (*setVar)(int in);
	void (*getVar)(int *out);

	struct list_head list;
};
#endif
