#include <stdio.h>
#include <stdlib.h>

struct record
{
	char name[20];
	int age;
};

int main(int argc, char *argv[])
{
	struct record array[2];
	FILE *fp;
	int i;

	fp = fopen("recfile", "r");
	if (NULL == fp)
	{
		perror("Open file error\n");
		exit(1);
	}

	fread(array, sizeof(struct record), 2, fp);


	for (i = 0; i < 2; i++)
		printf("Name %s, age %d\n", array[i].name, array[i].age);

	fclose(fp);

	return 0;
}
