#ifndef _display_H_
#define _display_H_

#include "klist.h"

struct display_module {
	/* variables */
	char name[20];
	int var;

	/* functions */
	void (*printInfo)(const char *name);
	void (*setVar)(int in);
	void (*getVar)(int *out);
	void (*initDevice)(struct display_module *p);

	struct list_head list;
};

#endif
