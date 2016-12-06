#ifndef _SUBSYSTEM_H_
#define _SUBSYSTEM_H_

#include "klist.h"
struct MODULE_module {
	char name[20];
	void (*printInfo)(void);
	struct list_head list;
};
#endif
