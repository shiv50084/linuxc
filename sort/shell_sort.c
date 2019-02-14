#include <stdlib.h>
#include <time.h>
#include <stdio.h>

void shell_sort(int array[], int len)
{
	int d;
	int i, j, tmp;

	/*
	 * 以数组长度的一半为初始d划分区间
	 * 不断递减步进d = d / 2
	 */
	for (d = len / 2; d > 0; d = d / 2)
	{
		/* 遍历每个区间的数 */
		for (i = d; i < len; i++)
		{
			/* 对每个区间的数进行直接插入排序 */
			for (j = i - d; j >= 0; j = j - d)
			{
				if (array[j + d] >= array[j])
					break;
				else
				{
					tmp = array[j];
					array[j] = array[j + d];
					array[j + d] = tmp;
				}
			}
		}
	}
}

void show_data(int arr[], int len)
{
	int i;

	for (i = 0; i < len; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

int main(int argc, char *argv[])
{
	int i;
	int array[20];
	int range = 500;
	int len;
	clock_t start;
	clock_t end;
	double time_spend;

	srand(time(NULL));

	/* generate a 20 elements array */
	for (i = 0; i < 20; i++)
		array[i] = rand() % range + 1;

	len = sizeof(array) / sizeof(array[0]);

	show_data(array, len);
	start = clock();
	shell_sort(array, len);
	end = clock();
    time_spend = (double)(end - start) / CLOCKS_PER_SEC;

	show_data(array, len);

    printf("Time spent sorting: %f\n", time_spend);

	return 0;
}
