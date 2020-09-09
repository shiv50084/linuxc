#include <stdio.h>
#include <string.h>

#define DIR_NAME "/usr/bin/"
#define CONCATENATE(x)	DIR_NAME#x

#define LS_FULL_PATH CONCATENATE(ls)
#define CAT_FULL_PATH CONCATENATE(cat)

int main(int argc, char *argv[])
{
	char buf[1024];
	char *tmp = LS_FULL_PATH;

	printf("%s\n", tmp);
	printf("%s\n", CAT_FULL_PATH);

	strcpy(buf, CAT_FULL_PATH);
	printf("buf = %s\n", buf);

	return 0;
}
