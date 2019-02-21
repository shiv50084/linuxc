#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "common.h"

#define ELEMENT_NR 20

int Left(int i)
{
	return i * 2;
}

int Right(int i)
{
	return i * 2 + 1;
}

/*
 * max heap :
 * 如果数组a[1,...n]满足:a[i]>a[2*i] && a[i]>a[2*i+1] && 1<=i<=n/2
 * 那么就是一个heap,而且是max-heap
 *
 * min-heap :
 * 其中min-heap的性质与上面所述相反
 * 即 a[i]<a[2*i] && a[i]<a[2*i+1]
 */
void max_heapify(int array[], int index, int heap_size)
{
	int l, r, largest;

	l = Left(index);
	r = Right(index);
	largest = index;

	if (l > heap_size || r > heap_size)
		return;

	if (l < heap_size && array[l] > array[largest])
		largest = l;
	if (r < heap_size && array[r] > array[largest])
		largest = r;

	if (largest != index)
	{
		swap(&array[largest], &array[index]);
		max_heapify(array, largest, heap_size);
	}
}

void build_max_heap(int array[], int len)
{
	int i;
	int heap_size;

	heap_size = len;
	for (i = heap_size / 2 - 1; i > -1; i--)
		max_heapify(array, i, heap_size);
}

void heap_sort(int array[], int len)
{
	int i;
	int heap_size;

	/* build a max heap first */
	build_max_heap(array, len);

	/* sort */
	for (i = len - 1; i > 0; i--)
	{
		swap(&array[0], &array[i]);
		heap_size = i;

		max_heapify(array, 0, heap_size);
	}
}

int main(int argc, char *argv[])
{
	int i;
	int array[ELEMENT_NR];
	int range = 500;

	/* generate a ELEMENT_NR elements array */
	srand(time(NULL));
	for (i = 0; i < ELEMENT_NR; i++)
		array[i] = rand() % range + 1;

	/* heap sort heap sort */
	show_array(array, ELEMENT_NR);
	heap_sort(array, ELEMENT_NR);
	show_array(array, ELEMENT_NR);

	return 0;
}
