#include <stdio.h>

/*
 * ++b的步长实际上是3个int,也就是++b运算以后,b指向{4,5,6}这个数组的开始
 * 而b[1]就是{7,8,9}, b[1][1]实际上就是8这个值也就是main函数中的a[2][1]
 */
void foo(int[][3]);

int main(void)
{
	int a[3][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };

	printf("%d\n", a[2][1]);
	foo(a);
	printf("%d\n", a[2][1]);

	return 0;
}

void foo(int b[][3])
{
	++b;
	b[1][1] = 9;
}
