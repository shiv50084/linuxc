#include <stdio.h>

/* 设置大端32位 */
#define SETBE32(a, v) do { \
	((unsigned char*)&a)[3] =  v      & 0xff; \
	((unsigned char*)&a)[2] = (v>>8 ) & 0xff; \
	((unsigned char*)&a)[1] = (v>>16) & 0xff; \
	((unsigned char*)&a)[0] = (v>>24) & 0xff; \
} while(0)


int main(int argc, char *argv[])
{
	int input;
	int result;

	printf("Enter a number:");
	scanf("%d", &input);
	SETBE32(result, input);
	printf("set input to big endless ===> %d\n", result);

	return 0;
}
