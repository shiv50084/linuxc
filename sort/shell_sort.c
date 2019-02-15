#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "common.h"

#define ELEMENT_NR 20

void shell_sort(int array[], int len)
{
	int i, j, gap;

	/*
	 * 以数组长度的一半为初始gap划分区间
	 * 不断递减步进gap = gap / 2
	 */
	for (gap = len / 2; gap > 0; gap = gap / 2)
	{
		/* 遍历每个区间的数 */
		for (i = gap; i < len; i++)
		{
			/* 对每个区间的数进行直接插入排序 */
			for (j = i - gap; j >= 0 && array[j] > array[j + gap]; j = j - gap)
			{
				swap(&array[j], &array[j + gap]);
			}
		}
	}
}

int main(int argc, char *argv[])
{
	int i;
	int array[ELEMENT_NR];
	int range = 500;
	int len;
	clock_t start;
	clock_t end;
	double time_spend;

	srand(time(NULL));

	/* generate a ELEMENT_NR elements array */
	for (i = 0; i < ELEMENT_NR; i++)
		array[i] = rand() % range + 1;

	len = ARRAY_LEN(array);

	show_array(array, len);
	start = clock();
	shell_sort(array, len);
	end = clock();
    time_spend = (double)(end - start) / CLOCKS_PER_SEC;

	show_array(array, len);

    printf("Time spent sorting: %f\n", time_spend);

	return 0;
}
