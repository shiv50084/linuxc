#include <stdio.h>

void myswap(int *a, int *b)
{
	/*
	 * 这里面却存在着一个非常隐蔽的陷阱
	 * 对于arr[n]中如果arr[i] == arr[j]
	 * 在交换arr[i]和arr[j]的时候需要确保这两个数不是同一个数
	 * 否则下面的代码就变成了
	 * a ^= b
	 * a ^= b
	 * a ^= b
	 * 把同一个数异或了3次
	 */
	if (a == b)
		return;

	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

int main(int argc, char **argv)
{
	int a, b;
	printf("input number one:");
	scanf("%d", &a);
	printf("input number two:");
	scanf("%d", &b);

	printf("a = %d, b = %d\n", a, b);

	printf("swap them:\n");
	myswap(&a, &b);

	printf("a = %d, b = %d\n", a, b);

	return 0;
}
