#include <stdio.h>
#include <stdlib.h>

struct record
{
	char name[20];
	int age;
};

int main(int argc, char *argv[])
{
	struct record array[2] = { {"jordan", 23}, {"eminem", 28} };
	FILE *fp;

	fp = fopen("recfile", "w");
	if (NULL == fp)
	{
		perror("Open file error\n");
		exit(1);
	}

	fwrite(array, sizeof(struct record), 2, fp);
	fclose(fp);

	return 0;
}
