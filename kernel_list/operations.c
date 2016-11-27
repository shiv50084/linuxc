#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "project_common.h"

/* add a person to the person list */
void add_person(const char *person_name, int number, int to_tail)
{
	struct person *tmp;
	tmp = malloc(sizeof(struct person));
	if (NULL == tmp)
	{
		printf("error\n");
		return;
	}

	tmp->number = number;
	strcpy(tmp->name, person_name);

	if (to_tail)
		list_add_tail(&tmp->list, &person_list);
	else
		list_add(&tmp->list, &person_list);
}

const char *players[] = {
	"jordan",
	"eminem",
	"shady"
};

void check_person_list(int reverse)
{
	struct person *ps;

	printf("----------PLAYER'S INFO--------------\n");
	if (reverse)
		list_for_each_entry_reverse(ps, &person_list, list)
			printf("%s[%d]\n", ps->name, ps->number);
	else
		list_for_each_entry(ps, &person_list, list)
			printf("%s[%d]\n", ps->name, ps->number);
	printf("----------PLAYER'S INFO--------------\n");
}

/* return zero on success and error code upon failure */
int delete_person(void)
{
	struct person *ps;
	char name[20];
	int delete_person_found = 0;

	printf("Enter Name :");
	scanf("%s", name);
	list_for_each_entry(ps, &person_list, list) {
		if (!strcmp(name, ps->name))
		{
			delete_person_found = 1;
			break;
		}
	}

	if (delete_person_found)
	{
		list_del(&ps->list);
		free(ps);
		ps = NULL;
		return 0;
	}

	printf("No this guy :(\n");
	return -1;
}

/* find out prev and next person */
int neighbour_of(void)
{
	struct person *ps;
	struct person *prev;
	struct person *next;
	char name[20];
	int mid_person_found = 0;

	printf("Enter Name :");
	scanf("%s", name);
	list_for_each_entry(ps, &person_list, list) {
		if (!strcmp(name, ps->name))
		{
			mid_person_found = 1;
			break;
		}
	}

	if (mid_person_found)
	{
		prev = container_of(ps->list.prev, struct person, list);
		next = container_of(ps->list.next, struct person, list);
		printf("Prev : %s, Next : %s\n", prev->name, next->name);
		return 0;
	}

	printf("No this guy :(\n");
	return -1;
}
