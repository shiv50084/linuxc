#include <stdio.h>

#define NAME(n) case n: return #n

#define EMINEM 0
#define JORDAN 23
#define KOBE 24
#define SHADY 911

const char *use_index_find_string(int index)
{
	switch (index)	
	{
		NAME(EMINEM);
		NAME(JORDAN);
		NAME(KOBE);
		NAME(SHADY);
		default:
			return "unkonw names";
	}
}

int main(int arg, char **argv)
{
	int index;
	printf("input a index to find the name: ");
	scanf("%d", &index);

	printf("%s\n", use_index_find_string(index));

	return 0;
}
