#include <stdio.h>
#include "common.h"

#define ELEMENT_NR	10
void bubble_sort(int array[], int size)
{
	int i, j, need_swap = 1;

	while (need_swap)
	{
		need_swap = 0;
		for (i = (size-1) ;i >= 0 ;i--)
		{
			for (j = 1 ; j <= i && array[j - 1] > array[j]; j++)
			{
				swap(&array[j - 1], &array[j]);
				need_swap = 1;
			}
		}
	}
}

int main(int argc, char *argv[])
{
	int datas[ELEMENT_NR]={10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	int i;

	/* Invoke the bubble sort algorithm */
	bubble_sort(datas, ELEMENT_NR);

	/* Print out the final array */
	for (i = 0 ; i < ELEMENT_NR ; i++)
		printf("%d\t", datas[i]);
	printf("\n");

	return 0;
}
