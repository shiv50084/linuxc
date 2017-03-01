#include <stdio.h>

#define NUMBERS 10

int array[NUMBERS] = {[0 ... NUMBERS - 1] = -1};

int main(int argc, char *argv[])
{
	int i;
	for (i = 0; i < NUMBERS; i++)
		printf("array[%d] = %d\n", i, array[i]);
	return 0;
}
