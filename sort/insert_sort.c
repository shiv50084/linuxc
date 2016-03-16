/*
 * Usage: gcc -DDEBUG inset_sort.c
 */

#include <stdio.h>

#define LEN 5
int arr[LEN] = {100, 5, 2, 32, 22};

void insert_sort(int arr[], int len)
{
	int i, j, key;

	/* 从第一个数开始遍历 */
	for (j = 1; j < len; j++)
	{
#ifdef DEBUG
		printf("%d, %d, %d, %d, %d\n", arr[0], arr[1], arr[2], arr[3], arr[4]);
#endif
		/* 保存每次遍历的这个数,作为比较数 */
		key = arr[j];

		/* 从最开始取数和子序列比较 */
		i = j - 1;

		/* 如果满足条件,进行交换 */
		while (i >= 0 && arr[i] > key)
		{
			arr[i + 1] = arr[i];	
			i--;
		}

		arr[i + 1] = key;
#ifdef DEBUG
		printf("%d, %d, %d, %d, %d\n", arr[0], arr[1], arr[2], arr[3], arr[4]);
#endif
	}
}

int main(int argc, char **argv)
{
	
	insert_sort(arr, LEN);
	return 0;
}
