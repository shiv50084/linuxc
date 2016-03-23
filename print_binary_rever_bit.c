/*
 * 输入指定的数,打印其二进制数
 * 给指定的位进行反转操作
 */
#include <stdio.h>

#ifdef DEBUG_PRINT
#define DBG_PRINT	printf
#else
#define DBG_PRINT
#endif

void print_binary(int var, int *result)
{
	int i;
	int tmp;

	/* bit31,bit30--->bit1,bit0 */
	for (i = 31; i >= 0; i--)
	{
		tmp = (var & (1<<i));
		DBG_PRINT("%d", tmp ? 1 : 0);
		result[i] = tmp ? 1 : 0;
	}
	DBG_PRINT("\n");
}

void wrap_result(int *var)
{
	int i;
	int index;

	for (i = 31; i >= 0; i--)
	{
		if (var[i] == 1)
		{
			index = i;
			break;
		}
	}

	for (i = index; i >= 0; i--)
		printf("%d", var[i]);

	printf("\n");
}

int main(int argc, char **argv)
{
	int input;
	int bit;
	int result[32];

	while (1)
	{
		printf("input a number:");
		scanf("%d", &input);
		print_binary(input, result);
		printf("input number binary:");
		wrap_result(result);

		printf("input the rever bit[0-31]:");
		scanf("%d", &bit);
		input = input ^ (1 << bit);
		print_binary(input, result);
		printf("input number rever bit binary:");
		wrap_result(result);
	}

	return 0;
}
