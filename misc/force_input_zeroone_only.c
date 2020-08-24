#include <stdio.h>

/*
 * Accept Only 0 and 1
 * 0 ==> 0
 * !0 ==> 1
 */
int main(int argc, char *argv[])
{
	int i;
	int j;

	/* only 0 and 1 can be accept */
	scanf("%d", &i);

	j = !!i;
	printf("%d\n", j);

	return 0;
}
