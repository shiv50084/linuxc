#include <stdio.h>
#include "generics.h"

/*
 * 利用cmp比较规则来比较data里的数据
 * 取出按照设定规则较大的值
 */
void *max(void *data[], int num, cmp_t cmp)
{
	int i;
	void *tmp = data[0];

	for (i = 1; i < num; i++)
		if (cmp(data[i], tmp) > 0)
			tmp = data[i];

	return tmp;
}
