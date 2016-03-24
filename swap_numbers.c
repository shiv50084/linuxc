#include <stdio.h>

int main(int argc, char **argv)
{
	int a, b;
	printf("input number one:");
	scanf("%d", &a);
	printf("input number two:");
	scanf("%d", &b);

	printf("a = %d, b = %d\n", a, b);

	printf("swap them:");
	/*
	 * this is how to swap two number without use tmp var
	 */
	a = a ^ b;
	b = b ^ a;
	a = a ^ b;

	printf("a = %d, b = %d\n", a, b);

	return 0;
}
