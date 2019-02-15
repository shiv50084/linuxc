#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "common.h"

#define ELEMENT_NR 20

/*
 * 每一次从待排序的数组中选取最小(或最大)的数
 * 依次存放到已排序的数组中
 */
void select_sort(int array[], int len)
{
	int i, j;
	int min_index;

	for (i = 0; i < len; i++)
	{
		min_index = i;
		for (j = i + 1; j < len; j++)
		{
			if (array[min_index] > array[j])
				min_index = j;
		}

		swap(&array[min_index], &array[i]);
	}
}

int main(int argc, char *argv[])
{
	int i;
	int array[ELEMENT_NR];
	int range = 500;
	clock_t start;
	clock_t end;
	double time_spend;

	/* generate a ELEMENT_NR elements array */
	srand(time(NULL));
	for (i = 0; i < ELEMENT_NR; i++)
		array[i] = rand() % range + 1;

	show_array(array, ELEMENT_NR);
	start = clock();
	select_sort(array, ELEMENT_NR);
	end = clock();
	time_spend = (double)(end - start) / CLOCKS_PER_SEC;
	show_array(array, ELEMENT_NR);

	printf("Time spent sorting: %f\n", time_spend);

	return 0;
}
