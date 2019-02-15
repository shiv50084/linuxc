/*
 * Usage: gcc -DDEBUG inset_sort.c
 */

#include <stdio.h>
#include "common.h"

#define DEBUG
int arr[] = {53, 27, 36, 15, 69, 42};

void insert_sort(int arr[], int len)
{
	int i, j, key;

	/* 从第一个数开始遍历 */
	for (j = 1; j < len; j++)
	{
		/* 保存每次遍历的这个数,作为比较数 */
		key = arr[j];
#ifdef DEBUG
		if (j == 1)
			insert_sort_show_array(arr, len, j);
#endif

		/*
		* 从最开始取数和子序列比较(i = j - 1)
		* 如果满足条件,进行交换
		*/
		for (i = j - 1; i >= 0 && arr[i] > key; i--)
			arr[i + 1] = arr[i];

		arr[i + 1] = key;
#ifdef DEBUG
		insert_sort_show_array(arr, len, j + 1);
#endif
	}
}

int main(int argc, char **argv)
{
	int len;

	len = ARRAY_LEN(arr);
	insert_sort(arr, len);

	return 0;
}
