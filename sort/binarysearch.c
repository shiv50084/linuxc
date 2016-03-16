#include <stdio.h>

#define LEN 11
int arr[LEN] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

/* 对排好序的序列进行折半查找,返回要查找数的索引 */
int binarysearch(int arr[], int len, int key)
{
	/* 序列的索引 */
	int start, mid, end;

	start = 0;
	end = len - 1;

	while (start <= end)
	{
		mid = (start + end) / 2;

		if (arr[mid] < key)
			start = mid + 1;//因为key > arr[mid],所以这里mid + 1
		else if (arr[mid] > key)
			end = mid - 1;//因为key < arr[mid],所以这里mid - 1
		else
			return mid;
	}

	return -1;
}

int main(int argc, char **argv)
{
	int ret;

	ret = binarysearch(arr, LEN, 6);
	printf("arr[%d] = %d\n", ret, arr[ret]);

	return 0;
}
