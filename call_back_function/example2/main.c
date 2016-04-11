#include <stdio.h>
#include "generics.h"

typedef struct {
	const char *name;
	int score;
}student_t;

/*
 * a is big than b
 */
int cmp_student(void *a, void *b)
{
	return ((student_t *)a)->score - ((student_t *)b)->score;
}

int main(int argc, char *argv[])
{
	int i;
	student_t *pmax = NULL;

	student_t list[4] = {
		{"Tom", 8},
		{"Jerry", 72},
		{"Moby", 90},
		{"Kirby", 89}
	};

	student_t *plist[4] = {
		&list[0],
		&list[1],
		&list[2],
		&list[3]
	};


	for (i = 0; i < 4; i++)
		printf("name %s : score %d\n", list[i].name, list[i].score);

	pmax = max((void **)plist, 4, cmp_student);
	printf("pmax score is %d\n", pmax->score);

	return 0;
}
